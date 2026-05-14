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
- **`matrix/`** — LED 矩阵服务，双缓冲架构（back/front buffer）。写入接口只修改 back_buffer，需手动调用 `matrix_write_async()` 提交帧。支持 progressive 和 snake（蛇形走线）两种拓扑。CLI 命令前缀 `mtrx_*`
- **`flip/`** — FLIP (Fluid-Implicit-Particle) 二维流体仿真核心，管理粒子系统、速度场、压力场和密度场
- **`imu/`** — IMU 服务，抽象传感器接口（`imu_sensor_t`），内部使用 Madgwick AHRS 滤波器计算欧拉角
- **`cli/`** — letter shell v3.2.4 移植，通过 UART 交互。使用 `SHELL_EXPORT_CMD()` 宏在链接段 `.shellCommand` 中注册命令
- **`cli/log/`** — 日志工具，支持 ERROR/WARNING/INFO/DEBUG/VERBOSE 五级，通过 `logError()`, `logInfo()` 等宏使用
- **`tools/`** — 通用工具：`common_def.h`（`exit_code_t` 返回码、类型别名）、`vec_math.h`（2D/3D 向量数学库）

### `src/bsp/` — 板级支持包
- **`ws2812b/`** — WS2812B 驱动（LibDriver 移植），通过 SPI DMA 发送编码数据。`driver_ws2812b_interface.c` 是硬件适配层
- **`imu963ra/`** — IMU963RA 传感器驱动
- **`mpu6500/`** — MPU6500 传感器驱动
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
- 写入操作（`matrix_set_pixel`, `matrix_fill`, `matrix_write_buffer`）只修改 back_buffer，不自动刷新
- 必须调用 `matrix_write_async()` 才会将帧提交到 LED
- `spi_temp` 缓冲区位于 `.dma_buffer` 段（D2 SRAM `0x30000000`），配置为 non-cacheable 以保证 DMA 一致性

### FreeRTOS
- 使用 `pdMS_TO_TICKS()` 和 `pdTICKS_TO_MS()` 进行 tick 转换
- 内存分配使用 `pvPortMalloc` / `vPortFree`

## Dependencies (managed_components)

- `espressif/esp-dsp` — DSP 加速库
- `espressif/led_strip` — LED 灯带组件
- `espressif/button` — 按键组件

## IDE Setup

- clangd 路径：`C:\Espressif\tools\esp-clang\esp-19.1.2_20250312\esp-clang\bin\clangd.exe`
- compile_commands.json 位于 `build/` 目录
- `.clangd` 配置移除了 `-f*` 和 `-m*` 编译标志以兼容 clangd
