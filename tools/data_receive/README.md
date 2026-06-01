# IMU 数据 TCP 接收器

通过 TCP 连接 ESP32，接收 IMU 加速度数据并保存为 CSV 格式。

## 数据协议

对应固件: `src/service/signal_process/imu_data_process.c`

| 字段 | 大小 | 说明 |
|------|------|------|
| acc_x | 4 bytes | float32, 小端序 |
| acc_y | 4 bytes | float32, 小端序 |
| acc_z | 4 bytes | float32, 小端序 |
| footer | 4 bytes | 0xFFFFFFFF, 帧尾标记 |

- 每个采样点: 12 字节 (3 × float32)
- 采样率: 6667 Hz
- 帧分隔符: `0xFFFFFFFF` (NaN 作为帧尾标记)

## 使用方法

### 基本用法

```bash
# 默认连接 192.168.4.1:8080
python tcp_receiver.py

# 自定义 IP
python tcp_receiver.py --ip 192.168.1.100

# 自定义 IP 和端口
python tcp_receiver.py --ip 192.168.1.100 --port 9090
```

### 指定输出文件

```bash
# 指定输出文件名
python tcp_receiver.py --output my_data.csv

# 输出到特定目录
python tcp_receiver.py --output ./data/test.csv
```

### 定时录制

```bash
# 录制 10 秒后自动停止
python tcp_receiver.py --duration 10

# 录制 5 秒，保存到指定文件
python tcp_receiver.py -d 5 -o test_5s.csv
```

### 持续录制

不指定 `--duration` 参数，按 `Ctrl+C` 停止录制。

## 输出格式

CSV 文件包含以下列:

| 列名 | 类型 | 说明 |
|------|------|------|
| timestamp_us | int | 微秒级 Unix 时间戳 |
| datetime | string | 可读时间格式 (YYYY-MM-DD HH:MM:SS.ffffff) |
| acc_x | float | X 轴加速度 (g) |
| acc_y | float | Y 轴加速度 (g) |
| acc_z | float | Z 轴加速度 (g) |

示例:
```csv
timestamp_us,datetime,acc_x,acc_y,acc_z
1717234567890123,2026-06-01 12:34:56.789012,0.012345,-0.023456,1.001234
```

## 实时显示

录制过程中会实时显示:
- 采样点总数
- 帧数
- 估算采样率 (Hz)
- 已录制时长

## 依赖

- Python 3.7+
- 标准库 (socket, struct, csv 等，无需额外安装)
