"""
ESP32 IMU 数据实时推理上位机

通过 TCP 连接 ESP32，接收 IMU 加速度数据，
实时进行 FFT 频谱分析，用 ONNX 模型进行分类推理。

数据协议:
  - 每个采样点: 12 字节 (3 × float32, 小端序): acc_x, acc_y, acc_z
  - 帧分隔符: 4 字节 0xFFFFFFFF (NaN 作为帧尾标记)
  - 采样率: 6667 Hz

处理流程:
  1. TCP 接收 IMU 数据
  2. 环形缓冲区累积采样点
  3. 滑动窗口 FFT (1024点, hop=256)
  4. 每 16 帧 FFT 结果组成一个 CNN 样本
  5. ONNX 模型推理分类

用法:
  python realtime_inference.py                          # 默认 192.168.4.1:8080
  python realtime_inference.py --ip 192.168.1.100       # 自定义 IP
  python realtime_inference.py --model models/model.onnx  # 指定模型
"""

import socket
import struct
import argparse
import time
import signal
import sys
import json
from pathlib import Path
from collections import deque
from threading import Thread, Lock

import numpy as np
from scipy.signal import windows as sig_windows

# 尝试导入 onnxruntime
try:
    import onnxruntime as ort
except ImportError:
    print("请安装 onnxruntime: pip install onnxruntime")
    sys.exit(1)

# ══════════════════════════════════════════════════════════════════════
# 常量 — 与训练代码保持一致
# ══════════════════════════════════════════════════════════════════════

# TCP 协议
VEC3F_SIZE = 12          # 3 × float32 = 12 字节
FOOTER_MAGIC = 0xFFFFFFFF  # 帧尾标记
DEFAULT_IP = "192.168.137.200"
DEFAULT_PORT = 8080
RECV_BUFFER_SIZE = 4096  # 接收缓冲区大小

# FFT 参数 — 与训练代码对齐
SP_FFT_SIZE = 1024       # FFT 点数
SP_HOP_SIZE = 256        # 跳步大小 (75% 重叠)
SP_FREQ_BINS = 512       # 频率 bin 数 (FFT_SIZE / 2)
SP_SAMPLE_RATE = 6667.0  # 采样率 (Hz)
SP_FREQ_RES = SP_SAMPLE_RATE / SP_FFT_SIZE  # 频率分辨率 ≈ 6.51 Hz

# CNN 输入
CNN_SAMPLE_FRAMES = 16   # 每个样本包含的帧数

# 类别名称
CLASS_NAMES = ["idle", "normal", "loose", "imbalance"]

# ══════════════════════════════════════════════════════════════════════
# 全局状态
# ══════════════════════════════════════════════════════════════════════

running = True


def signal_handler(sig, frame):
    """Ctrl+C 优雅退出"""
    global running
    running = False
    print("\n正在停止...")


# ══════════════════════════════════════════════════════════════════════
# FFT 处理
# ══════════════════════════════════════════════════════════════════════

def make_hann_window() -> np.ndarray:
    """生成 Hann 窗, float32"""
    return sig_windows.hann(SP_FFT_SIZE, sym=False).astype(np.float32)


def process_frame(frame: np.ndarray, hann: np.ndarray) -> np.ndarray:
    """
    单帧 FFT 处理 (对应训练代码的 process_frame):
      1. 去直流偏移
      2. 去线性趋势
      3. Hann 窗
      4. FFT
      5. 提取幅度谱 (前 FREQ_BINS 个 bin), 转 dB

    Args:
        frame: shape=(FFT_SIZE,), float32
        hann: shape=(FFT_SIZE,), float32

    Returns:
        shape=(FREQ_BINS,), float32 — 幅度谱 (dB)
    """
    buf = frame.astype(np.float32).copy()

    # 去直流偏移
    buf -= buf.mean()

    # 去线性趋势
    slope = (buf[-1] - buf[0]) / (len(buf) - 1)
    buf -= slope * np.arange(len(buf), dtype=np.float32)

    # 应用 Hann 窗
    buf *= hann

    # FFT
    spectrum = np.fft.rfft(buf, n=SP_FFT_SIZE)

    # 提取幅度谱，转 dB
    mag = np.abs(spectrum[:SP_FREQ_BINS])
    return 20 * np.log10(mag + 1e-10)


# ══════════════════════════════════════════════════════════════════════
# 数据解析
# ══════════════════════════════════════════════════════════════════════

def parse_buffer(buffer: bytes) -> tuple:
    """
    解析接收缓冲区，提取采样点

    返回: (剩余未处理的字节, 新增采样点列表 [(x, y, z), ...])
    """
    new_samples = []
    offset = 0

    while offset < len(buffer):
        remaining = len(buffer) - offset

        if remaining >= 4:
            # 先 peek 4 字节，检查是否是 footer
            potential_footer = struct.unpack_from('<I', buffer, offset)[0]

            if potential_footer == FOOTER_MAGIC:
                # 是帧尾标记，跳过
                offset += 4
                continue

        if remaining >= VEC3F_SIZE:
            # 解析 vec3f (3 个 float32)
            x, y, z = struct.unpack_from('<fff', buffer, offset)
            new_samples.append((x, y, z))
            offset += VEC3F_SIZE
        else:
            # 数据不足，等待更多数据
            break

    return buffer[offset:], new_samples


# ══════════════════════════════════════════════════════════════════════
# 实时推理器
# ══════════════════════════════════════════════════════════════════════

class RealtimeInference:
    """实时推理器 — 接收数据、FFT 处理、模型推理"""

    def __init__(self, model_path: str, norm_stats: dict, calibrate_seconds: float = 5.0):
        """
        初始化推理器

        Args:
            model_path: ONNX 模型路径
            norm_stats: 归一化参数 {"mean": [x, y, z], "std": [x, y, z]}
            calibrate_seconds: 校准时长（秒），采集静态数据计算直流偏移
        """
        # 加载 ONNX 模型
        print(f"加载模型: {model_path}")
        self.session = ort.InferenceSession(model_path)
        self.input_name = self.session.get_inputs()[0].name

        # 归一化参数
        self.mean = np.array(norm_stats["mean"]).reshape(1, 1, 1, 3).astype(np.float32)
        self.std = np.array(norm_stats["std"]).reshape(1, 1, 1, 3).astype(np.float32)

        # FFT 窗函数
        self.hann = make_hann_window()

        # 数据缓冲区 (3 轴独立)
        self.buffer_x = deque(maxlen=SP_FFT_SIZE)
        self.buffer_y = deque(maxlen=SP_FFT_SIZE)
        self.buffer_z = deque(maxlen=SP_FFT_SIZE)

        # FFT 帧缓冲区 (用于组成 CNN 样本)
        self.fft_frames_x = deque(maxlen=CNN_SAMPLE_FRAMES)
        self.fft_frames_y = deque(maxlen=CNN_SAMPLE_FRAMES)
        self.fft_frames_z = deque(maxlen=CNN_SAMPLE_FRAMES)

        # 采样计数
        self.sample_count = 0
        self.fft_frame_count = 0
        self.inference_count = 0

        # 上一次推理结果
        self.last_prediction = None
        self.last_probs = None

        # 统计
        self.total_samples = 0
        self.total_inferences = 0
        self.inference_times = []

        # 校准相关
        self.calibrate_seconds = calibrate_seconds
        self.calibrating = True
        self.calibrate_samples_x = []
        self.calibrate_samples_y = []
        self.calibrate_samples_z = []
        self.dc_offset_x = 0.0
        self.dc_offset_y = 0.0
        self.dc_offset_z = 0.0

        # 锁 (线程安全)
        self.lock = Lock()

    def add_samples(self, samples: list):
        """
        添加新的采样点

        Args:
            samples: [(x, y, z), ...] 列表
        """
        with self.lock:
            for x, y, z in samples:
                # 校准模式：收集静态数据
                if self.calibrating:
                    self.calibrate_samples_x.append(x)
                    self.calibrate_samples_y.append(y)
                    self.calibrate_samples_z.append(z)
                    self.total_samples += 1

                    # 检查是否收集够校准数据
                    target_samples = int(self.calibrate_seconds * SP_SAMPLE_RATE)
                    if len(self.calibrate_samples_x) >= target_samples:
                        self._finish_calibration()
                    continue

                # 正常模式：减去直流偏移后送入缓冲区
                self.buffer_x.append(x - self.dc_offset_x)
                self.buffer_y.append(y - self.dc_offset_y)
                self.buffer_z.append(z - self.dc_offset_z)
                self.sample_count += 1
                self.total_samples += 1

                # 每收到 SP_HOP_SIZE 个新样本，做一次 FFT
                if self.sample_count >= SP_HOP_SIZE:
                    self.sample_count = 0
                    self._do_fft()

    def _finish_calibration(self):
        """完成校准，计算直流偏移"""
        self.dc_offset_x = np.mean(self.calibrate_samples_x)
        self.dc_offset_y = np.mean(self.calibrate_samples_y)
        self.dc_offset_z = np.mean(self.calibrate_samples_z)
        self.calibrating = False

        # 释放校准数据
        n = len(self.calibrate_samples_x)
        self.calibrate_samples_x.clear()
        self.calibrate_samples_y.clear()
        self.calibrate_samples_z.clear()

        print(f"\n校准完成 ({n} 个样本)")
        print(f"  直流偏移: X={self.dc_offset_x:.6f}, Y={self.dc_offset_y:.6f}, Z={self.dc_offset_z:.6f}")
        print(f"开始推理...\n")

    def get_calibrate_progress(self) -> tuple:
        """获取校准进度"""
        if not self.calibrating:
            return 1.0, 0
        target = int(self.calibrate_seconds * SP_SAMPLE_RATE)
        progress = len(self.calibrate_samples_x) / target if target > 0 else 0
        remaining = len(self.calibrate_samples_x)
        return min(progress, 1.0), remaining

    def _do_fft(self):
        """执行 FFT 处理，需要至少 FFT_SIZE 个样本"""
        if len(self.buffer_x) < SP_FFT_SIZE:
            return

        # 提取最近的 FFT_SIZE 个样本
        frame_x = np.array(list(self.buffer_x)[-SP_FFT_SIZE:])
        frame_y = np.array(list(self.buffer_y)[-SP_FFT_SIZE:])
        frame_z = np.array(list(self.buffer_z)[-SP_FFT_SIZE:])

        # FFT 处理
        spec_x = process_frame(frame_x, self.hann)
        spec_y = process_frame(frame_y, self.hann)
        spec_z = process_frame(frame_z, self.hann)

        # 添加到帧缓冲区
        self.fft_frames_x.append(spec_x)
        self.fft_frames_y.append(spec_y)
        self.fft_frames_z.append(spec_z)

        self.fft_frame_count += 1

        # 检查是否可以做推理
        if len(self.fft_frames_x) >= CNN_SAMPLE_FRAMES:
            self._do_inference()

    def _do_inference(self):
        """执行 CNN 推理"""
        start_time = time.time()

        # 组织输入数据: (1, 16, 512, 3) channels_last
        sample = np.stack([
            np.array(list(self.fft_frames_x)),
            np.array(list(self.fft_frames_y)),
            np.array(list(self.fft_frames_z)),
        ], axis=-1).astype(np.float32)  # (16, 512, 3)

        # 添加 batch 维度
        sample = sample.reshape(1, CNN_SAMPLE_FRAMES, SP_FREQ_BINS, 3)

        # 归一化
        sample_norm = (sample - self.mean) / self.std

        # ONNX 推理
        probs = self.session.run(None, {self.input_name: sample_norm})[0]

        # 解析结果
        probs = probs[0]  # (num_classes,)
        pred_idx = np.argmax(probs)
        confidence = probs[pred_idx]

        # 更新结果
        self.last_prediction = CLASS_NAMES[pred_idx]
        self.last_probs = probs
        self.inference_count += 1
        self.total_inferences += 1

        # 记录推理时间
        inference_time = time.time() - start_time
        self.inference_times.append(inference_time)
        if len(self.inference_times) > 100:
            self.inference_times.pop(0)

    def get_status(self) -> dict:
        """获取当前状态"""
        with self.lock:
            avg_inference_time = 0
            if self.inference_times:
                avg_inference_time = np.mean(self.inference_times) * 1000  # ms

            return {
                "total_samples": self.total_samples,
                "total_inferences": self.total_inferences,
                "buffer_fill": len(self.buffer_x),
                "fft_frames": len(self.fft_frames_x),
                "last_prediction": self.last_prediction,
                "last_probs": self.last_probs.tolist() if self.last_probs is not None else None,
                "avg_inference_ms": avg_inference_time,
            }


# ══════════════════════════════════════════════════════════════════════
# TCP 接收
# ══════════════════════════════════════════════════════════════════════

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


def tcp_receiver_thread(sock: socket.socket, inference: RealtimeInference):
    """TCP 接收线程"""
    global running

    buffer = b''
    sample_timestamps = deque(maxlen=1000)

    while running:
        try:
            data = sock.recv(RECV_BUFFER_SIZE)
            if not data:
                print("\n连接已断开")
                running = False
                break
        except socket.timeout:
            continue
        except ConnectionResetError:
            print("\n连接被重置")
            running = False
            break

        # 拼接到缓冲区
        buffer += data

        # 解析数据
        buffer, new_samples = parse_buffer(buffer)

        if new_samples:
            # 记录时间戳
            ts = time.time()
            sample_timestamps.append(ts)

            # 送入推理器
            inference.add_samples(new_samples)

        # 估算采样率
        if len(sample_timestamps) >= 2:
            ts_list = list(sample_timestamps)
            dt = ts_list[-1] - ts_list[0]
            if dt > 0:
                rate = (len(ts_list) - 1) / dt
            else:
                rate = 0
        else:
            rate = 0

        # 实时显示
        if inference.calibrating:
            progress, count = inference.get_calibrate_progress()
            bar_len = 30
            filled = int(bar_len * progress)
            bar = '█' * filled + '░' * (bar_len - filled)
            print(f"\r校准中: [{bar}] {progress*100:.0f}% ({count} 样本)",
                  end='', flush=True)
        else:
            status = inference.get_status()
            pred = status["last_prediction"] or "---"
            conf = ""
            if status["last_probs"]:
                probs = status["last_probs"]
                conf = f" [{probs[0]:.2f} {probs[1]:.2f} {probs[2]:.2f} {probs[3]:.2f}]"

            print(f"\r采样: {status['total_samples']:>8d} | "
                  f"FFT帧: {status['fft_frames']:>4d} | "
                  f"推理: {status['total_inferences']:>4d} | "
                  f"采样率: {rate:>7.1f} Hz | "
                  f"推理耗时: {status['avg_inference_ms']:>5.1f}ms | "
                  f"预测: {pred:>10s}{conf}",
                  end='', flush=True)

    sock.close()


# ══════════════════════════════════════════════════════════════════════
# 主函数
# ══════════════════════════════════════════════════════════════════════

def load_meta(model_path: Path) -> dict:
    """加载模型元数据"""
    meta_path = model_path.parent / "meta.json"
    if not meta_path.exists():
        print(f"警告: 元数据文件不存在: {meta_path}")
        print("使用默认归一化参数 (可能影响推理精度)")
        return {
            "norm_stats": {
                "mean": [0.0, 0.0, 0.0],
                "std": [1.0, 1.0, 1.0],
            },
            "class_names": CLASS_NAMES,
        }

    with open(meta_path) as f:
        return json.load(f)


def main():
    parser = argparse.ArgumentParser(
        description='ESP32 IMU 数据实时推理上位机',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  python realtime_inference.py                           # 默认连接 192.168.4.1:8080
  python realtime_inference.py --ip 192.168.1.100        # 自定义 IP
  python realtime_inference.py --model models/model.onnx # 指定模型
  python realtime_inference.py --calibrate 3             # 校准 3 秒
  python realtime_inference.py --calibrate 0             # 跳过校准
        """)

    parser.add_argument('--ip', default=DEFAULT_IP,
                        help=f'ESP32 IP 地址 (默认: {DEFAULT_IP})')
    parser.add_argument('--port', type=int, default=DEFAULT_PORT,
                        help=f'TCP 端口 (默认: {DEFAULT_PORT})')
    parser.add_argument('--model', '-m', default=None,
                        help='ONNX 模型路径 (默认: models/model.onnx)')
    parser.add_argument('--calibrate', '-c', type=float, default=5.0,
                        help='校准时长（秒），采集静态数据计算直流偏移 (默认: 5.0)')

    args = parser.parse_args()

    # 确定模型路径
    if args.model:
        model_path = Path(args.model)
    else:
        model_path = Path(__file__).parent / "models" / "model.onnx"

    if not model_path.exists():
        print(f"错误: 模型文件不存在: {model_path}")
        print("请先训练并导出模型: python -m src.cnn.train && python -m src.cnn.export")
        sys.exit(1)

    # 加载元数据
    meta = load_meta(model_path)
    print(f"类别: {meta['class_names']}")
    print(f"归一化参数: mean={meta['norm_stats']['mean']}, std={meta['norm_stats']['std']}")

    # 初始化推理器
    inference = RealtimeInference(str(model_path), meta["norm_stats"], args.calibrate)

    # 注册信号处理
    signal.signal(signal.SIGINT, signal_handler)

    # 连接 ESP32
    sock = connect_to_server(args.ip, args.port)

    # 启动接收线程
    receiver = Thread(target=tcp_receiver_thread, args=(sock, inference), daemon=True)
    receiver.start()

    print("\n按 Ctrl+C 停止\n")

    # 等待结束
    while running:
        time.sleep(0.1)

    # 显示最终统计
    status = inference.get_status()
    print(f"\n\n{'='*60}")
    print(f"推理完成")
    print(f"  总采样点: {status['total_samples']}")
    print(f"  总推理次数: {status['total_inferences']}")
    if status['avg_inference_ms'] > 0:
        print(f"  平均推理耗时: {status['avg_inference_ms']:.1f} ms")
    print(f"{'='*60}")


if __name__ == "__main__":
    main()
