# IMU 数据实时推理上位机

通过 TCP 连接 ESP32，接收 IMU 加速度数据，实时进行 FFT 频谱分析，用 ONNX 模型进行分类推理。

## 功能

- TCP 连接 ESP32 接收 IMU 数据
- 实时 FFT 频谱分析 (1024点, 75%重叠)
- ONNX 模型实时推理分类
- 显示推理结果和置信度

## 数据处理流程

```
ESP32 IMU 数据 (TCP)
    ↓
环形缓冲区 (3轴独立)
    ↓ 每 256 个新样本
滑动窗口 FFT (1024点, Hann窗)
    ↓ 每 16 帧
CNN 样本 (16, 512, 3)
    ↓ 归一化
ONNX 模型推理
    ↓
分类结果 (idle/normal/loose/imbalance)
```

## 依赖

```bash
pip install numpy scipy onnxruntime
```

## 使用方法

### 基本用法

```bash
# 默认连接 192.168.4.1:8080，使用 models/model.onnx
python realtime_inference.py

# 自定义 IP
python realtime_inference.py --ip 192.168.1.100

# 自定义 IP 和端口
python realtime_inference.py --ip 192.168.1.100 --port 9090

# 指定模型路径
python realtime_inference.py --model models/model.onnx
```

### 实时显示

推理过程中会实时显示:
- 采样点总数
- FFT 帧数
- 推理次数
- 估算采样率 (Hz)
- 平均推理耗时 (ms)
- 预测类别和各类别概率

示例输出:
```
采样:    12345 | FFT帧:   48 | 推理:   32 | 采样率: 6650.2 Hz | 推理耗时:   2.3ms | 预测:     normal [0.05 0.90 0.03 0.02]
```

## 模型说明

- 模型格式: ONNX (从 Keras 导出)
- 输入形状: (1, 16, 512, 3) — batch×帧×频率bin×通道
- 输出形状: (1, 4) — 4个类别的概率
- 类别: idle, normal, loose, imbalance

## 参数说明

| 参数 | 值 | 含义 |
|---|---|---|
| 采样率 | 6667 Hz | IMU 每秒采样数 |
| FFT 窗口 | 1024 点 (0.15s) | 单次 FFT 的采样长度 |
| FFT 跳步 | 256 点 (0.038s) | 相邻帧间距, 75% 重叠 |
| 频率分辨率 | 6.51 Hz/bin | 每个频率 bin 的跨度 |
| CNN 窗口 | 16 帧 (0.61s) | 每个样本覆盖的时间 |

## 与训练代码的对应关系

| 本程序 | 训练代码 | 说明 |
|---|---|---|
| `process_frame()` | `src/data/fft_processor.py:process_frame()` | 单帧 FFT 处理 |
| `CNN_SAMPLE_FRAMES` | `src/config.py:CNN_SAMPLE_FRAMES` | CNN 样本帧数 |
| `SP_FFT_SIZE` | `src/config.py:SP_FFT_SIZE` | FFT 点数 |
| `SP_HOP_SIZE` | `src/config.py:SP_HOP_SIZE` | 跳步大小 |
| `CLASS_NAMES` | `src/config.py:CLASS_NAMES` | 类别名称 |

## 注意事项

1. 归一化参数从 `models/meta.json` 加载，必须与训练时一致
2. 数据缓冲区使用环形缓冲区，只保留最近的 FFT_SIZE 个样本
3. 推理在 TCP 接收线程中同步执行，可能影响采样率显示
4. 按 Ctrl+C 优雅退出
