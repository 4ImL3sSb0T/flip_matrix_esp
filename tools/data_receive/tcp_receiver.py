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
"""

import socket
import struct
import argparse
import csv
import time
import signal
import sys
from pathlib import Path
from datetime import datetime
from collections import deque

# ── 常量 ──────────────────────────────────────────────────────────────────────

VEC3F_SIZE = 12          # 3 × float32 = 12 字节
FOOTER_MAGIC = 0xFFFFFFFF  # 帧尾标记
DEFAULT_IP = "192.168.4.1"
DEFAULT_PORT = 8080
RECV_BUFFER_SIZE = 4096  # 接收缓冲区大小

# ── 全局状态 ──────────────────────────────────────────────────────────────────

running = True


def signal_handler(sig, frame):
    """Ctrl+C 优雅退出"""
    global running
    running = False
    print("\n正在停止...")


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


def parse_buffer(buffer: bytes, samples: list, frame_count: int) -> tuple:
    """
    解析接收缓冲区，提取采样点和帧信息

    返回: (剩余未处理的字节, 新增采样点列表, 帧计数增量)
    """
    new_samples = []
    frames_detected = 0
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
            timestamp_us = get_timestamp_us()
            new_samples.append((timestamp_us, x, y, z))
            offset += VEC3F_SIZE
        else:
            # 数据不足，等待更多数据
            break

    return buffer[offset:], new_samples, frames_detected


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
    buffer = b''
    start_time = time.time()

    # 采样率估算
    sample_timestamps = deque(maxlen=1000)

    print(f"开始录制到: {output_path}")
    if duration:
        print(f"录制时长: {duration} 秒")
    print("按 Ctrl+C 停止录制\n")

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
            buffer, new_samples, new_frames = parse_buffer(buffer, [], 0)

            # 写入 CSV
            for sample in new_samples:
                ts_us, x, y, z = sample
                writer.writerow([ts_us, format_timestamp(ts_us),
                                 f"{x:.6f}", f"{y:.6f}", f"{z:.6f}"])
                sample_timestamps.append(ts_us)

            total_samples += len(new_samples)
            total_frames += new_frames

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

                print(f"\r采样点: {total_samples:>8d} | "
                      f"帧数: {total_frames:>6d} | "
                      f"采样率: {rate:>8.1f} Hz | "
                      f"已录制: {elapsed:>6.1f}s", end='', flush=True)

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

        # 显示最终统计
        elapsed = time.time() - start_time
        print(f"\n\n{'='*60}")
        print(f"录制完成")
        print(f"  文件: {output_path}")
        print(f"  采样点: {total_samples}")
        print(f"  帧数: {total_frames}")
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
