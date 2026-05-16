# ESP32-S3 LED 矩阵流体面板

基于 ESP32-S3 的 LED 矩阵面板，在 WS2812B 灯板上实时运行 FLIP 流体仿真，通过 IMU 传感器检测倾斜角度控制重力方向。

## 功能

- **FLIP 流体仿真** — 二维粒子 + 网格混合流体求解器，支持可调求解质量和时间步长
- **LED 矩阵渲染** — 双缓冲架构，SPI DMA 异步发送，支持 progressive 和 snake 两种走线拓扑
- **IMU 倾斜控制** — Madgwick AHRS 滤波器计算欧拉角，实时改变流体重力方向
- **CLI 调试** — letter shell 串口交互，运行时调节仿真参数

## 硬件

| 组件 | 型号/规格 |
|------|-----------|
| MCU | ESP32-S3 |
| LED 矩阵 | WS2812B（默认 16x16，最大 256 LED） |
| IMU 传感器 | IMU963RA / MPU6500 |
| 通信接口 | SPI（LED 驱动）、UART（CLI 调试） |

## 项目结构

```
├── src/
│   ├── app/                    # 应用层
│   │   ├── app_water_sim.c/h   # 水仿真应用任务
│   │   └── app_water_sim_cmd.c # CLI 命令
│   ├── service/                # 服务层
│   │   ├── flip/               # FLIP 流体仿真引擎
│   │   ├── matrix/             # LED 矩阵双缓冲服务
│   │   ├── imu/                # IMU 服务 + Madgwick AHRS
│   │   ├── cli/                # letter shell 移植 + 日志
│   │   └── tools/              # 通用工具（返回码、向量数学）
│   └── bsp/                    # 板级驱动
│       ├── ws2812b/            # WS2812B SPI DMA 驱动
│       ├── imu963ra/           # IMU963RA 传感器驱动
│       └── uart/               # UART 异步收发驱动
├── main/                       # ESP-IDF 入口
├── managed_components/         # ESP-IDF 组件管理器依赖
└── CMakeLists.txt
```

依赖方向：`app → service → bsp`

## 构建与烧写

需要先安装 [ESP-IDF v5.5.4](https://docs.espressif.com/projects/esp-idf/en/v5.5.4/esp32s3/get-started/) 并配置好环境。

```bash
# 激活 ESP-IDF 环境（每次新终端需要）
. $IDF_PATH/export.sh        # Linux / macOS
# Windows: 运行 ESP-IDF PowerShell 或 CMD 快捷方式

# 构建
idf.py build

# 烧写 + 监控（默认串口 COM21）
idf.py -p COM21 flash monitor

# 仅烧写
idf.py -p COM21 flash

# 仅监控
idf.py -p COM21 monitor

# 清理构建产物
idf.py fullclean
```

## CLI 命令

通过串口终端（波特率 115200）输入以下命令实时调试：

| 命令 | 说明 | 示例 |
|------|------|------|
| `wsim_gravity <scale>` | 设置重力缩放系数 | `wsim_gravity 1.5` |
| `wsim_solver <push> <pressure> <flip>` | 设置求解质量参数 | `wsim_solver 5 20 0.9` |
| `wsim_color <0\|1\|2>` | 切换颜色方案（0=蓝色渐变 1=彩虹 2=灰度） | `wsim_color 1` |
| `wsim_dt <seconds>` | 设置仿真时间步长 | `wsim_dt 0.02` |
| `wsim_status` | 显示当前仿真参数 | `wsim_status` |
| `mtrx_*` | LED 矩阵相关命令 | 参见 `matrix_cmd.c` |

## 依赖组件

| 组件 | 用途 |
|------|------|
| `espressif/esp-dsp` | DSP 加速库 |
| `espressif/led_strip` | LED 灯带组件 |
| `espressif/button` | 按键组件 |

## License

FLIP 流体仿真核心算法移植自 [Matthias Müller - Ten Minute Physics](https://www.youtube.com/c/TenMinutePhysics)，原代码基于 MIT License。
