# Matrix LED Service

基于 WS2812B 的 LED 矩阵服务，使用 ESP-IDF `led_strip` 组件（RMT 驱动），负责拓扑映射和像素管理。

## 架构

```
用户任务
  │
  ├── matrix_write_buffer()
  ├── matrix_set_pixel()
  ├── matrix_fill()
  └── matrix_clear()
        │
        ▼
  led_strip_set_pixel()   ← 写入内部缓冲
        │
        │ matrix_write_async()
        ▼
  led_strip_refresh()     ← RMT DMA 发送到 LED
```

写入接口（`matrix_set_pixel`, `matrix_fill`, `matrix_write_buffer`）只修改 `led_strip` 内部缓冲，不会自动刷新显示。需要显示新内容时，调用 `matrix_write_async()` 手动提交一帧。

## API

```c
typedef enum {
  MATRIX_TOPO_PROGRESSIVE = 0,
  MATRIX_TOPO_SNAKE      = 1
} matrix_topo_t;

typedef struct {
  uint32_t rows;
  uint32_t cols;
  int gpio_num;
  matrix_topo_t topology;
} matrix_config_t;
```

### 生命周期

| 函数 | 说明 |
|------|------|
| `matrix_init(config)` | 初始化 led_strip RMT 设备和互斥锁 |
| `matrix_deinit()` | 删除 led_strip 设备，释放互斥锁 |

### 写入

| 函数 | 说明 |
|------|------|
| `matrix_write_buffer(data, len)` | 批量写入逻辑坐标帧数据，内部自动拓扑映射，不刷新 |
| `matrix_set_pixel(row, col, rgb)` | 写入单个逻辑像素，内部自动拓扑映射，不刷新 |
| `matrix_fill(rgb)` | 填充全部 LED，不刷新 |
| `matrix_clear()` | 清空全部 LED，不刷新 |

`matrix_write_buffer()` 的 `data` 按逻辑行列顺序排列：`data[row * cols + col]`。蛇形走线时，模块会自动转换为物理 LED 序号。

### 显示控制

| 函数 | 说明 |
|------|------|
| `matrix_write_async()` | 调用 `led_strip_refresh()` 将缓冲区数据通过 RMT DMA 发送到 LED |

### 查询

| 函数 | 说明 |
|------|------|
| `matrix_pixel_count()` | 返回 LED 总数 |
| `matrix_rows()` | 返回行数 |
| `matrix_cols()` | 返回列数 |

### 颜色工具

| 函数 | 说明 |
|------|------|
| `matrix_rgb(r, g, b)` | 将 R/G/B 合成为 0xRRGGBB 格式的 uint32_t |
| `matrix_hsv2rgb(h, s, v)` | HSV 转 RGB（h: 0-359, s/v: 0-255），返回 0xRRGGBB |

## 使用示例

```c
matrix_config_t cfg = {
  .rows = 16,
  .cols = 16,
  .gpio_num = 48,
  .topology = MATRIX_TOPO_SNAKE,
};

matrix_init(&cfg);

compute_frame(frame_data);
matrix_write_buffer(frame_data, matrix_pixel_count());
matrix_write_async();

matrix_set_pixel(0, 0, matrix_rgb(255, 0, 0));
matrix_set_pixel(0, 1, matrix_hsv2rgb(120, 255, 255));
matrix_write_async();

matrix_deinit();
```

## 拓扑映射

```c
static uint32_t map_snake(uint32_t row, uint32_t col, uint32_t cols)
{
  if (row & 1) {
    col = cols - 1 - col;
  }
  return row * cols + col;
}
```

`matrix_write_buffer()` 和 `matrix_set_pixel()` 使用逻辑坐标并经过拓扑映射。`matrix_fill()` / `matrix_clear()` 是全量写入，不需要坐标映射。

## 内存

编译常量 `MATRIX_MAX_LEDS` 默认 256，可通过 CMake 编译定义覆盖。实际 LED 缓冲由 `led_strip` 组件内部管理。

## 线程安全

所有写入操作和 `matrix_write_async()` 都通过 `matrix_mutex` 保护。不要从 ISR 调用 `matrix_*` API。

## 依赖

- `espressif/led_strip` — LED 灯带组件（RMT 驱动）
- FreeRTOS mutex
