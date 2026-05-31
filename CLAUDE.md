# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

ESP32-S3 LED 矩阵面板项目，基于 ESP-IDF v5.5.4。核心功能是运行 FLIP 流体仿真，并将结果实时渲染到 WS2812B LED 矩阵上，同时利用 IMU 传感器实现倾斜控制重力方向。

## Build Commands

```bash
# 设置 ESP-IDF 环境（每次新终端需要）
. $IDF_PATH/export.sh   # Linux/macOS
# Windows: 运行 ESP-IDF PowerShell 或 CMD 快捷方式

# 构建
idf.py build

# 烧写（通过 JTAG，端口 COM21）
idf.py -p COM21 flash

# 监控串口终端
idf.py -p COM21 monitor

# 构建 + 烧写 + 监控
idf.py -p COM21 flash monitor

# 清理构建
idf.py fullclean

# 配置菜单
idf.py menuconfig
```

## Architecture

项目分为三层，依赖方向为 `app → service → bsp`：

### `src/app/` — 应用层
- `app_water_sim.c/.h` — 水仿真应用，创建 FreeRTOS 任务驱动仿真循环：读取 IMU 加速度 → 执行 FLIP 步进 → 密度场映射颜色 → 提交 LED 矩阵
- `app_water_sim_cmd.c` — 对应的 CLI 命令（`wsim_gravity`, `wsim_solver`, `wsim_color`, `wsim_dt`, `wsim_status`）

### `src/service/` — 服务层
- **`event_bus/`** — 发布/订阅事件总线，基于 FreeRTOS 队列。支持按 `module_id` + `event_id` 匹配订阅者，`EVENTBUS_EVENT_ID_ALL` 通配。各模块通过 `eventbus_allocate_module_id()` 获取唯一模块 ID
- **`matrix/`** — LED 矩阵服务，基于 `led_strip` RMT 驱动。写入接口修改内部缓冲，需手动调用 `matrix_write_async()` 刷新。支持 progressive 和 snake（蛇形走线）两种拓扑。CLI 命令前缀 `mtrx_*`
- **`flip/`** — FLIP (Fluid-Implicit-Particle) 二维流体仿真核心，管理粒子系统、速度场、压力场和密度场
- **`imu/`** — IMU 服务，抽象传感器接口（`imu_sensor_t`），内部使用 Madgwick AHRS 滤波器计算欧拉角。包含状态机（IDLE/ACTIVE/SHAKING/FALLING/ROTATING/SLEEP），通过事件总线发布 IMU 事件（TAP/FLIP/SHAKE/FALLING/ROTATING/SLEEP/WAKE_UP）
- **`cli/`** — letter shell v3.2.4 移植，通过 UART 交互。使用 `SHELL_EXPORT_CMD()` 宏在链接段 `.shellCommand` 中注册命令
- **`cli/log/`** — 日志工具，支持 ERROR/WARNING/INFO/DEBUG/VERBOSE 五级，通过 `logError()`, `logInfo()` 等宏使用
- **`tools/`** — 通用工具：`common_def.h`（`exit_code_t` 返回码、类型别名）、`vec_math.h`（2D/3D 向量数学库）

### `src/bsp/` — 板级支持包
- **`imu963ra/`** — IMU963RA 传感器驱动
- **`mpu6500/`** — MPU6500 传感器驱动（备用）
- **`uart/`** — UART 异步收发驱动

## Key Conventions

### 返回码
所有 API 使用 `exit_code_t`（定义在 `service/tools/common_def.h`），成功返回 `EXIT_OK (0)`，失败返回负值。不要使用 `ESP_ERROR_CHECK`，改用 `exit_code_t` 传递错误。

### Shell 命令注册
使用 letter shell 的导出宏注册 CLI 命令：
```c
SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN)|SHELL_CMD_DISABLE_RETURN,
    cmd_name, cmd_function, description\r\nusage);
```
命令函数签名为 `int func(int argc, char *argv[])`。注意描述中的 `\r\n` 用于分隔帮助文本。

### LED 矩阵
- 写入操作（`matrix_set_pixel`, `matrix_fill`, `matrix_write_buffer`）只修改 led_strip 内部缓冲，不自动刷新
- 必须调用 `matrix_write_async()` 才会通过 RMT DMA 将帧提交到 LED
- 底层使用 `espressif/led_strip` 组件的 RMT 驱动，配置 `gpio_num` 和 `MATRIX_MAX_LEDS`

### FreeRTOS
- 使用 `pdMS_TO_TICKS()` 和 `pdTICKS_TO_MS()` 进行 tick 转换
- 内存分配使用 `pvPortMalloc` / `vPortFree`

### 事件总线
- 所有模块间通信通过 `event_bus` 发布/订阅，不直接调用其他模块的回调
- 模块通过 `eventbus_allocate_module_id()` 获取唯一 ID，事件通过 `eventbus_publish()` 发布
- 订阅时可用 `EVENTBUS_EVENT_ID_ALL` 通配某个模块的所有事件
- 事件负载为堆分配的变长结构（`eventbus_event_t.payload[]`），回调中只读，由事件总线负责释放

### 启动流程
1. `app_main()`（core 0）：初始化事件总线 → 初始化 UART → 创建 `start_flip_task`（core 1）
2. `start_flip_task()`（core 1）：初始化 shell → 初始化 IMU 服务 → 初始化水仿真应用 → 启动仿真任务

## Dependencies (managed_components)

- `espressif/esp-dsp` — DSP 加速库
- `espressif/led_strip` — LED 灯带组件
- `espressif/button` — 按键组件

## 联网工具限制

内置的 `WebSearch` 和 `WebFetch` 工具在此环境下不可用。所有联网搜索必须使用 MCP 工具：
- GitHub 搜索/操作：`mcp__dashscope-github__*`（search_code, search_repositories, get_file_contents 等）
- 网页搜索：`mcp__tavily__tavily_search`
- 网页内容提取：`mcp__tavily__tavily_extract`
- 库文档查询：`mcp__plugin_context7_context7__*`

## IDE Setup

- clangd 路径：`C:\Espressif\tools\esp-clang\esp-19.1.2_20250312\esp-clang\bin\clangd.exe`
- compile_commands.json 位于 `build/` 目录
- `.clangd` 配置移除了 `-f*` 和 `-m*` 编译标志以兼容 clangd
