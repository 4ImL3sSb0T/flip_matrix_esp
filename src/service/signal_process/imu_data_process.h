#ifndef __IMU_DATA_PROCESS_H
#define __IMU_DATA_PROCESS_H

#include "service/tools/common_def.h"
#include "freertos/FreeRTOS.h"
#include "freertos/message_buffer.h"

#define SP_FFT_SIZE      1024
#define SP_HOP_SIZE      256
#define SP_FREQ_BINS     (SP_FFT_SIZE / 2)
#define SP_SAMPLE_RATE   6667.0f
#define SP_FREQ_RES      (SP_SAMPLE_RATE / SP_FFT_SIZE)

typedef struct {
    float acc_x[SP_FREQ_BINS];  // acc X 轴频谱幅度
    float acc_y[SP_FREQ_BINS];  // acc Y 轴频谱幅度
    float acc_z[SP_FREQ_BINS];  // acc Z 轴频谱幅度
    float gyro_x[SP_FREQ_BINS]; // gyro X 轴频谱幅度
    float gyro_y[SP_FREQ_BINS]; // gyro Y 轴频谱幅度
    float gyro_z[SP_FREQ_BINS]; // gyro Z 轴频谱幅度
} sp_fft_result_t;

exit_code_t sp_process_init(void);
void sp_process_task(void *arg);
sp_fft_result_t *sp_process_get_latest(void);

#endif
