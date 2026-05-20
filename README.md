# ESP32-S3 LED 矩阵流体面板

基于 ESP32-S3 的 LED 矩阵面板，在 WS2812B 灯板上实时运行 FLIP 流体仿真，通过 IMU 传感器检测倾斜角度控制重力方向。

## 功能

- **FLIP 流体仿真** — 二维粒子 + 网格混合流体求解器，支持可调求解质量和时间步长
- **LED 矩阵渲染** — 基于 `led_strip` RMT 驱动，支持 progressive 和 snake 两种走线拓扑
- **IMU 倾斜控制** — Madgwick AHRS 滤波器计算欧拉角，实时改变流体重力方向。内置状态机检测敲击、翻转、摇晃、跌落等动作，通过事件总线发布
- **事件总线** — 发布/订阅架构，模块间解耦通信，支持通配订阅和变长事件负载
- **亮度控制** — 敲击传感器切换亮度（0.1 步进循环）
- **CLI 调试** — letter shell 串口交互，运行时调节仿真参数

## 硬件

| 组件 | 型号/规格 |
|------|-----------|
| MCU | ESP32-S3 |
| LED 矩阵 | WS2812B（默认 16x16，最大 256 LED） |
| IMU 传感器 | IMU963RA |
| 通信接口 | RMT（LED 驱动）、UART（CLI 调试） |

## 项目结构

```
├── src/
│   ├── app/                    # 应用层
│   │   ├── app_water_sim.c/h   # 水仿真应用任务
│   │   └── app_water_sim_cmd.c # CLI 命令
│   ├── service/                # 服务层
│   │   ├── event_bus/          # 发布/订阅事件总线
│   │   ├── flip/               # FLIP 流体仿真引擎
│   │   ├── matrix/             # LED 矩阵服务（led_strip RMT）
│   │   ├── imu/                # IMU 服务 + 状态机 + Madgwick AHRS
│   │   ├── cli/                # letter shell 移植 + 日志
│   │   └── tools/              # 通用工具（返回码、向量数学）
│   └── bsp/                    # 板级驱动
│       ├── imu963ra/           # IMU963RA 传感器驱动
│       ├── mpu6500/            # MPU6500 传感器驱动（备用）
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

### 水仿真命令

| 命令 | 说明 | 示例 |
|------|------|------|
| `wsim_gravity <scale>` | 设置重力缩放系数 | `wsim_gravity 1.5` |
| `wsim_solver <push> <pressure> <flip>` | 设置求解质量参数 | `wsim_solver 5 20 0.9` |
| `wsim_color <0\|1\|2>` | 切换颜色方案（0=蓝色渐变 1=彩虹 2=灰度） | `wsim_color 1` |
| `wsim_dt <seconds>` | 设置仿真时间步长 | `wsim_dt 0.02` |
| `wsim_status` | 显示当前仿真参数 | `wsim_status` |

### 矩阵命令

| 命令 | 说明 | 示例 |
|------|------|------|
| `mtrx_init <rows> <cols> <gpio> [topo]` | 初始化矩阵（topo: 0=progressive, 1=snake） | `mtrx_init 16 16 48 0` |
| `mtrx_deinit` | 反初始化矩阵 | `mtrx_deinit` |
| `mtrx_set <row> <col> <r> <g> <b>` | 设置单个像素颜色 | `mtrx_set 0 0 255 0 0` |
| `mtrx_fill <r> <g> <b>` | 填充全部像素 | `mtrx_fill 0 0 255` |
| `mtrx_clear` | 清除全部像素 | `mtrx_clear` |
| `mtrx_show` | 将缓冲区刷新到 LED | `mtrx_show` |
| `mtrx_info` | 显示矩阵信息 | `mtrx_info` |

### 系统命令

| 命令 | 说明 |
|------|------|
| `cpu` | 显示任务 CPU 占用 |
| `help [cmd]` | 显示命令帮助 |

## 启动流程

1. `app_main()`（core 0）：初始化事件总线 → 初始化 UART → 创建启动任务（core 1）
2. 启动任务（core 1）：初始化 CLI shell → 初始化 IMU 服务 → 初始化水仿真应用 → 启动仿真任务

仿真任务以配置的 `dt` 间隔循环运行：读取 IMU 加速度 → FLIP 步进 → 密度场映射颜色 → 提交 LED 矩阵。

## IMU 事件

IMU 服务内置状态机，检测以下动作并通过事件总线发布：

| 事件 | 触发条件 | 当前响应 |
|------|----------|----------|
| TAP | 高通加速度 + jerk 超阈值（200ms 冷却） | 循环切换亮度 |
| FLIP | 翻转角 > 120°（1000ms 冷却） | 日志记录 |
| SHAKE | 高通加速度 > 0.6 | 日志记录 |
| FALLING | 加速度 < 0.25g | 日志记录 |
| ROTATING | 角速度 > 120°/s | 日志记录 |
| SLEEP | 静止超过 10 秒 | 日志记录 |
| WAKE_UP | 从 SLEEP 恢复运动 | 日志记录 |

## 颜色方案

| 编号 | 名称 | 效果 |
|------|------|------|
| 0 | 蓝色渐变 | 亮度映射到蓝色通道 |
| 1 | 彩虹 | 亮度映射到色相（蓝→红，0-240） |
| 2 | 灰度 | 亮度映射到等值 R/G/B |

## 依赖组件

| 组件 | 用途 |
|------|------|
| `espressif/esp-dsp` | DSP 加速库 |
| `espressif/led_strip` | LED 灯带组件 |
| `espressif/button` | 按键组件 |

## License

FLIP 流体仿真核心算法移植自 [Matthias Müller - Ten Minute Physics](https://www.youtube.com/c/TenMinutePhysics)，原代码基于 MIT License。
