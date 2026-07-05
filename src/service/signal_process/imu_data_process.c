#include "imu_data_process.h"
#include "service/imu/imu_service.h"
#include "service/tools/vec_math.h"
#include "esp_dsp.h"
#include "esp_log.h"
#include <math.h>
#include <string.h>
#include "service/tcp/tcp_server.h"

#define TAG "IMU_DSP"

// ── 内部状态 ──────────────────────────────────────────────────────────────────

// 3 轴滑动窗口（环形缓冲）
static float s_win_x[SP_FFT_SIZE];
static float s_win_y[SP_FFT_SIZE];
static float s_win_z[SP_FFT_SIZE];
static uint32_t s_write_pos = 0;   // 环形写指针
static uint32_t s_hop_count = 0;   // 当前 hop 内已累积的采样数

// Hann 窗系数（SIMD 对齐）
static float __attribute__((aligned(16))) s_hann[SP_FFT_SIZE];

// FFT 工作缓冲（实虚交替，ESP-DSP SIMD 要求 16 字节对齐）
static float __attribute__((aligned(16))) s_fft_buf[SP_FFT_SIZE * 2];

// 最新频谱结果
static sp_fft_result_t s_latest;
static volatile bool s_has_result = false;

// ── 内部函数 ──────────────────────────────────────────────────────────────────

// 向环形窗口追加一个采样点（3 轴）
static void window_push(float ax, float ay, float az)
{
    s_win_x[s_write_pos] = ax;
    s_win_y[s_write_pos] = ay;
    s_win_z[s_write_pos] = az;
    s_write_pos = (s_write_pos + 1) % SP_FFT_SIZE;
}

// 对单轴执行完整的预处理 + FFT + 幅度提取
// 输入: ring_buf — 环形缓冲（从最旧到最新重排后的数据）
// 输出: out[FREQ_BINS] — 幅度谱
static void process_axis(const float *ring_buf, float *out)
{
    // 1. 拷贝（避免修改原始环形缓冲）
    memcpy(s_fft_buf, ring_buf, SP_FFT_SIZE * sizeof(float));

    // 2. 去直流偏移
    float sum = 0;
    for (int i = 0; i < SP_FFT_SIZE; i++) sum += s_fft_buf[i];
    float mean = sum / SP_FFT_SIZE;
    for (int i = 0; i < SP_FFT_SIZE; i++) s_fft_buf[i] -= mean;

    // 3. 去线性趋势
    float slope = (s_fft_buf[SP_FFT_SIZE - 1] - s_fft_buf[0]) / (float)(SP_FFT_SIZE - 1);
    for (int i = 0; i < SP_FFT_SIZE; i++) s_fft_buf[i] -= slope * i;

    // 4. Hann 窗
    dsps_mul_f32(s_fft_buf, s_hann, s_fft_buf, SP_FFT_SIZE, 1, 1, 1);

    // 5. 转为复数格式（实虚交替），原地扩展
    //    从后往前写，避免覆盖
    for (int i = SP_FFT_SIZE - 1; i >= 0; i--) {
        s_fft_buf[2 * i]     = s_fft_buf[i];   // 实部
        s_fft_buf[2 * i + 1] = 0.0f;           // 虚部
    }

    // 6. FFT
    dsps_fft2r_fc32(s_fft_buf, SP_FFT_SIZE);
    dsps_bit_rev_fc32(s_fft_buf, SP_FFT_SIZE);

    // 7. 提取幅度
    for (int i = 0; i < SP_FREQ_BINS; i++) {
        float re = s_fft_buf[2 * i];
        float im = s_fft_buf[2 * i + 1];
        out[i] = sqrtf(re * re + im * im);
    }
}

// 从环形缓冲中提取当前窗口（从最旧到最新），然后执行 FFT
static void compute_fft(void)
{
    // 把环形数据重排为线性：最旧 → 最新
    // 写指针指向下一个写入位置，即最旧数据的位置
    static float linear[SP_FFT_SIZE];

    // X 轴
    for (int i = 0; i < SP_FFT_SIZE; i++)
        linear[i] = s_win_x[(s_write_pos + i) % SP_FFT_SIZE];
    process_axis(linear, s_latest.acc_x);

    // Y 轴
    for (int i = 0; i < SP_FFT_SIZE; i++)
        linear[i] = s_win_y[(s_write_pos + i) % SP_FFT_SIZE];
    process_axis(linear, s_latest.acc_y);

    // Z 轴
    for (int i = 0; i < SP_FFT_SIZE; i++)
        linear[i] = s_win_z[(s_write_pos + i) % SP_FFT_SIZE];
    process_axis(linear, s_latest.acc_z);

    s_has_result = true;
}

// ── 公共 API ──────────────────────────────────────────────────────────────────

exit_code_t sp_process_init(void)
{
    // 生成 Hann 窗
    dsps_wind_hann_f32(s_hann, SP_FFT_SIZE);

    // 初始化 FFT 表（twiddle factors，必须用 CONFIG_DSP_MAX_FFT_SIZE）
    esp_err_t ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "FFT init failed: %s", esp_err_to_name(ret));
        return EXIT_FAIL;
    }

    // 清零缓冲
    memset(s_win_x, 0, sizeof(s_win_x));
    memset(s_win_y, 0, sizeof(s_win_y));
    memset(s_win_z, 0, sizeof(s_win_z));
    s_write_pos = 0;
    s_hop_count = 0;
    s_has_result = false;

    ESP_LOGI(TAG, "init: FFT=%d, hop=%d, bins=%d, df=%.1fHz",
             SP_FFT_SIZE, SP_HOP_SIZE, SP_FREQ_BINS, SP_FREQ_RES);
    return EXIT_OK;
}

void sp_process_task(void *arg)
{
    sp_process_init();

    static MessageBufferHandle_t acc_buf;
    acc_buf = imu_service_get_acc_buffer();
    if (!acc_buf) {
        ESP_LOGE(TAG, "acc ring buffer not initialized");
        vTaskDelete(NULL);
        return;
    }

    static vec3f batch[256];

    while (1) {
        size_t bytes = xMessageBufferReceive(acc_buf, batch, sizeof(batch), portMAX_DELAY);
        size_t count = bytes / sizeof(vec3f);

        for (size_t i = 0; i < count; i++) {
            // 推入滑动窗口
            window_push(batch[i].x, batch[i].y, batch[i].z);
            s_hop_count++;

            // 调试
            static const uint32_t footer = 0xFFFFFFFF;  // NaN，帧尾
            if (imu_service_is_ok()) {
                tcp_server_broadcast(batch, bytes);
                tcp_server_broadcast(&footer, sizeof(footer));
            }

            // 累积够一个 hop，执行 FFT
            if (s_hop_count >= SP_HOP_SIZE) {
                s_hop_count = 0;
                compute_fft();
            }
        }
    }
}

sp_fft_result_t *sp_process_get_latest(void)
{
    return s_has_result ? &s_latest : NULL;
}
