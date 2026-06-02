"""
ESP32 IMU 数据 TCP 接收器
对应固件: src/service/signal_process/imu_data_process.c

数据协议:
  - 每个采样点: 12 字节 (3 × float32, 小端序): acc_x, acc_y, acc_z
  - 帧分隔符: 4 字节 0xFFFFFFFF (NaN 作为帧尾标记)
  - 采样率: 6667 Hz

用法:
  python tcp_receiver.py                          # 默认 192.168.4.1:8080
  python tcp_receiver.py --ip 192.168.1.100       # 自定义 IP
  python tcp_receiver.py --ip 192.168.1.100 --port 9090  # 自定义 IP 和端口
  python tcp_receiver.py --output data.csv        # 指定输出文件名
  python tcp_receiver.py --duration 10            # 录制 10 秒后自动停止

标签功能 (Windows):
  按 1/2/3/4 标记时间段 (开始/结束切换):
    1 = idle
    2 = normal
    3 = loose
    4 = imbalance
"""

import socket
import struct
import argparse
import csv
import json
import time
import signal
import sys
import threading
from pathlib import Path
from datetime import datetime
from collections import deque

# ── 常量 ──────────────────────────────────────────────────────────────────────

VEC3F_SIZE = 12          # 3 × float32 = 12 字节
FOOTER_MAGIC = 0xFFFFFFFF  # 帧尾标记
DEFAULT_IP = "192.168.4.1"
DEFAULT_PORT = 8080
RECV_BUFFER_SIZE = 4096  # 接收缓冲区大小

# 类别名称 (与训练代码一致)
CLASS_NAMES = ["idle", "normal", "loose", "imbalance"]

# ── 标签管理器 ────────────────────────────────────────────────────────────────

class LabelManager:
    """时间段标签管理器 — 支持按键切换开始/结束标记"""

    def __init__(self):
        self.labels = []           # 已完成的标签列表
        self.active = {}           # 正在标记的类别 {class_name: start_time}
        self.start_time = None     # 录制开始时间
        self.lock = threading.Lock()

    def set_start_time(self, t: float):
        """设置录制开始时间"""
        self.start_time = t

    def toggle(self, class_name: str, current_time: float):
        """切换标记状态：如果未标记则开始，如果已标记则结束"""
        with self.lock:
            if class_name in self.active:
                # 结束标记
                start = self.active.pop(class_name)
                # 时间是相对于录制开始的秒数
                rel_start = start - self.start_time
                rel_end = current_time - self.start_time
                self.labels.append({
                    "start": round(rel_start, 3),
                    "end": round(rel_end, 3),
                    "class": class_name,
                })
                print(f"\n  ✓ {class_name}: {rel_start:.2f}s ~ {rel_end:.2f}s")
            else:
                # 开始标记
                self.active[class_name] = current_time
                rel_time = current_time - self.start_time
                print(f"\n  ● {class_name}: 开始于 {rel_time:.2f}s (再按一次结束)")

    def get_status(self) -> str:
        """获取当前标记状态"""
        with self.lock:
            if not self.active:
                return ""
            parts = []
            for cls, t in self.active.items():
                rel = t - self.start_time
                parts.append(f"{cls}({rel:.1f}s~)")
            return " | ".join(parts)

    def save_json(self, json_path: Path):
        """保存标签到 JSON 文件"""
        with self.lock:
            # 结束所有未完成的标记
            if self.start_time and self.active:
                current = time.time()
                for cls, start in self.active.items():
                    rel_start = start - self.start_time
                    rel_end = current - self.start_time
                    self.labels.append({
                        "start": round(rel_start, 3),
                        "end": round(rel_end, 3),
                        "class": cls,
                    })
                self.active.clear()

            # 按开始时间排序
            self.labels.sort(key=lambda x: x["start"])

            # 构建 JSON
            data = {
                "default_class": "other",
                "labels": self.labels,
            }

            json_path.parent.mkdir(parents=True, exist_ok=True)
            with open(json_path, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)

            print(f"\n标签已保存: {json_path}")
            print(f"  共 {len(self.labels)} 个时间段")
            for label in self.labels:
                print(f"    [{label['start']:.2f}s ~ {label['end']:.2f}s] {label['class']}")


# ── 全局状态 ──────────────────────────────────────────────────────────────────

running = True
label_manager = LabelManager()


def signal_handler(sig, frame):
    """Ctrl+C 优雅退出"""
    global running
    running = False
    print("\n正在停止...")


def keyboard_listener():
    """键盘监听线程 — Windows 使用 msvcrt"""
    global running

    try:
        import msvcrt
    except ImportError:
        print("警告: 键盘监听仅支持 Windows (msvcrt)")
        return

    # 按键映射
    key_map = {
        b'1': 'idle',
        b'2': 'normal',
        b'3': 'loose',
        b'4': 'imbalance',
    }

    while running:
        if msvcrt.kbhit():
            key = msvcrt.getch()
            if key in key_map:
                class_name = key_map[key]
                current_time = time.time()
                label_manager.toggle(class_name, current_time)
            elif key == b'\x03':  # Ctrl+C
                running = False
                break
        time.sleep(0.05)  # 50ms 轮询


def get_timestamp_us() -> int:
    """获取微秒级时间戳 (Unix timestamp in microseconds)"""
    return int(time.time() * 1_000_000)


def format_timestamp(us: int) -> str:
    """将微秒时间戳格式化为可读字符串"""
    sec = us / 1_000_000
    dt = datetime.fromtimestamp(sec)
    return dt.strftime("%Y-%m-%d %H:%M:%S.") + f"{us % 1_000_000:06d}"


def connect_to_server(ip: str, port: int) -> socket.socket:
    """连接到 ESP32 TCP 服务器"""
    print(f"正在连接 {ip}:{port}...")
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5.0)
    try:
        sock.connect((ip, port))
        print(f"已连接到 {ip}:{port}")
        return sock
    except socket.timeout:
        print(f"连接超时: {ip}:{port}")
        sys.exit(1)
    except ConnectionRefusedError:
        print(f"连接被拒绝: {ip}:{port}，请检查 ESP32 是否已启动 TCP 服务器")
        sys.exit(1)


def is_valid_sample(x: float, y: float, z: float) -> bool:
    """检查采样点是否有效 (非 NaN, 非 Inf)"""
    import math
    return not (math.isnan(x) or math.isnan(y) or math.isnan(z) or
                math.isinf(x) or math.isinf(y) or math.isinf(z))


def parse_buffer(buffer: bytes, samples: list, frame_count: int) -> tuple:
    """
    解析接收缓冲区，提取采样点和帧信息

    返回: (剩余未处理的字节, 新增采样点列表, 帧计数增量, 无效采样数)
    """
    new_samples = []
    frames_detected = 0
    invalid_count = 0
    offset = 0

    while offset < len(buffer):
        # 检查是否有足够的字节读取一个 vec3f 或 footer
        remaining = len(buffer) - offset

        if remaining >= 4:
            # 先 peek 4 字节，检查是否是 footer
            potential_footer = struct.unpack_from('<I', buffer, offset)[0]

            if potential_footer == FOOTER_MAGIC:
                # 是帧尾标记
                frames_detected += 1
                offset += 4
                continue

        if remaining >= VEC3F_SIZE:
            # 解析 vec3f (3 个 float32)
            x, y, z = struct.unpack_from('<fff', buffer, offset)

            # 检查是否为有效数据 (过滤 NaN/Inf)
            if is_valid_sample(x, y, z):
                timestamp_us = get_timestamp_us()
                new_samples.append((timestamp_us, x, y, z))
            else:
                invalid_count += 1

            offset += VEC3F_SIZE
        else:
            # 数据不足，等待更多数据
            break

    return buffer[offset:], new_samples, frames_detected, invalid_count


def run_receiver(ip: str, port: int, output_path: Path, duration: float = None):
    """主接收循环"""
    global running

    sock = connect_to_server(ip, port)
    sock.settimeout(1.0)

    # 打开 CSV 文件
    output_path.parent.mkdir(parents=True, exist_ok=True)
    csv_file = open(output_path, 'w', newline='', encoding='utf-8')
    writer = csv.writer(csv_file)
    writer.writerow(['timestamp_us', 'datetime', 'acc_x', 'acc_y', 'acc_z'])

    # 统计
    total_samples = 0
    total_frames = 0
    total_invalid = 0
    buffer = b''
    start_time = time.time()

    # 采样率估算
    sample_timestamps = deque(maxlen=1000)

    # 初始化标签管理器
    label_manager.set_start_time(start_time)

    # 启动键盘监听线程
    kb_thread = threading.Thread(target=keyboard_listener, daemon=True)
    kb_thread.start()

    print(f"开始录制到: {output_path}")
    if duration:
        print(f"录制时长: {duration} 秒")
    print("按 Ctrl+C 停止录制")
    print("\n标签快捷键: 1=idle 2=normal 3=loose 4=imbalance (开始/结束切换)\n")

    try:
        while running:
            # 检查录制时长
            if duration and (time.time() - start_time) >= duration:
                print(f"\n录制时长 {duration} 秒已到")
                break

            try:
                data = sock.recv(RECV_BUFFER_SIZE)
                if not data:
                    print("\n连接已断开")
                    break
            except socket.timeout:
                continue
            except ConnectionResetError:
                print("\n连接被重置")
                break

            # 拼接到缓冲区
            buffer += data

            # 解析数据
            buffer, new_samples, new_frames, invalid_count = parse_buffer(buffer, [], 0)

            # 写入 CSV
            for sample in new_samples:
                ts_us, x, y, z = sample
                writer.writerow([ts_us, format_timestamp(ts_us),
                                 f"{x:.6f}", f"{y:.6f}", f"{z:.6f}"])
                sample_timestamps.append(ts_us)

            total_samples += len(new_samples)
            total_frames += new_frames
            total_invalid += invalid_count

            # 实时显示统计
            elapsed = time.time() - start_time
            if elapsed > 0 and total_samples > 0:
                # 估算采样率
                if len(sample_timestamps) >= 2:
                    ts_list = list(sample_timestamps)
                    dt_us = ts_list[-1] - ts_list[0]
                    if dt_us > 0:
                        rate = (len(ts_list) - 1) / (dt_us / 1_000_000)
                    else:
                        rate = 0
                else:
                    rate = total_samples / elapsed

                # 标签状态
                label_status = label_manager.get_status()
                label_str = f" | 标记: {label_status}" if label_status else ""
                invalid_str = f" | 无效: {total_invalid}" if total_invalid > 0 else ""

                print(f"\r采样点: {total_samples:>8d} | "
                      f"帧数: {total_frames:>6d} | "
                      f"采样率: {rate:>8.1f} Hz | "
                      f"已录制: {elapsed:>6.1f}s{invalid_str}{label_str}",
                      end='', flush=True)

    except KeyboardInterrupt:
        pass
    finally:
        # 刷新剩余数据
        if buffer:
            remaining_samples = []
            offset = 0
            while offset + VEC3F_SIZE <= len(buffer):
                x, y, z = struct.unpack_from('<fff', buffer, offset)
                timestamp_us = get_timestamp_us()
                remaining_samples.append((timestamp_us, x, y, z))
                offset += VEC3F_SIZE

            for sample in remaining_samples:
                ts_us, x, y, z = sample
                writer.writerow([ts_us, format_timestamp(ts_us),
                                 f"{x:.6f}", f"{y:.6f}", f"{z:.6f}"])
            total_samples += len(remaining_samples)

        csv_file.close()
        sock.close()

        # 保存标签 JSON
        json_path = output_path.with_suffix('.json')
        label_manager.save_json(json_path)

        # 显示最终统计
        elapsed = time.time() - start_time
        print(f"\n{'='*60}")
        print(f"录制完成")
        print(f"  文件: {output_path}")
        print(f"  采样点: {total_samples}")
        print(f"  帧数: {total_frames}")
        if total_invalid > 0:
            print(f"  无效采样: {total_invalid} (已过滤 NaN/Inf)")
        print(f"  时长: {elapsed:.2f} 秒")
        if elapsed > 0:
            print(f"  平均采样率: {total_samples/elapsed:.1f} Hz")
        print(f"  文件大小: {output_path.stat().st_size / 1024:.1f} KB")
        print(f"{'='*60}")


def main():
    parser = argparse.ArgumentParser(
        description='ESP32 IMU 数据 TCP 接收器',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  python tcp_receiver.py                           # 默认连接 192.168.4.1:8080
  python tcp_receiver.py --ip 192.168.1.100        # 自定义 IP
  python tcp_receiver.py --duration 5 --output test.csv  # 录制 5 秒
        """)

    parser.add_argument('--ip', default=DEFAULT_IP,
                        help=f'ESP32 IP 地址 (默认: {DEFAULT_IP})')
    parser.add_argument('--port', type=int, default=DEFAULT_PORT,
                        help=f'TCP 端口 (默认: {DEFAULT_PORT})')
    parser.add_argument('--output', '-o', default=None,
                        help='输出 CSV 文件路径 (默认: data/imu_YYYYMMDD_HHMMSS.csv)')
    parser.add_argument('--duration', '-d', type=float, default=None,
                        help='录制时长（秒），不指定则持续录制直到 Ctrl+C')

    args = parser.parse_args()

    # 生成默认文件名
    if args.output is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_dir = Path(__file__).parent / "data"
        output_path = output_dir / f"imu_{timestamp}.csv"
    else:
        output_path = Path(args.output)

    # 注册信号处理
    signal.signal(signal.SIGINT, signal_handler)

    run_receiver(args.ip, args.port, output_path, args.duration)


if __name__ == "__main__":
    main()
