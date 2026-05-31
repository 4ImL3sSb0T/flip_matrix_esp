"""IMU FFT 结果可视化"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.font_manager as fm
from pathlib import Path

from .fft_processor import (
    SP_FFT_SIZE, SP_HOP_SIZE, SP_SAMPLE_RATE, SP_FREQ_RES, SP_FREQ_BINS,
)

# 中文字体 — 用 FontProperties 显式指定，避免 tkinter 后端回退到 DejaVu Sans
_CN_FONT = None
for _name in ["Microsoft YaHei", "SimHei", "NSimSun"]:
    _matches = [f for f in fm.fontManager.ttflist if f.name == _name]
    if _matches:
        _CN_FONT = fm.FontProperties(fname=_matches[0].fname)
        break

if _CN_FONT is None:
    # fallback: 让 rcParams 尝试
    matplotlib.rcParams["font.sans-serif"] = ["Microsoft YaHei", "SimHei", "DejaVu Sans"]
    matplotlib.rcParams["axes.unicode_minus"] = False
    _CN_FONT = fm.FontProperties(family="sans-serif")


CNN_SAMPLE_FRAMES = 64


class CNNSampleViewer:
    """CNN 样本可视化器 — 64帧滑动窗口，显示 3 通道频谱"""

    def __init__(self, sample_len: int = CNN_SAMPLE_FRAMES):
        self.sample_len = sample_len
        self.fig = None
        self.axes = None
        self.specs = {}       # key -> ndarray (n_frames, FREQ_BINS)
        self.n_frames = 0
        self.current_start = 0
        self._updating = False

    def load_data(self, result: dict):
        for key in ["x", "y", "z"]:
            _, spec = result[key]
            self.specs[key] = spec
        self.n_frames = self.specs["x"].shape[0]

    def setup(self):
        # 布局:
        # 行 0: 全局频谱概览 (X/Y/Z 并排)，高亮当前窗口
        # 行 1: CNN 样本 3 通道热力图 (64×512)
        # 行 2: CNN 样本合成 RGB 图 (R=X G=Y B=Z)
        self.fig = plt.figure(figsize=(16, 10))
        gs = self.fig.add_gridspec(
            3, 4, height_ratios=[1.5, 2, 2],
            hspace=0.4, left=0.06, right=0.97, top=0.92, wspace=0.35,
        )

        # 行 0: 概览
        self.ax_overview = [self.fig.add_subplot(gs[0, i]) for i in range(3)]

        # 行 1: 3 通道
        self.ax_ch = [self.fig.add_subplot(gs[1, i]) for i in range(3)]

        # 行 2: 合成图 + 当前样本信息
        self.ax_rgb = self.fig.add_subplot(gs[2, 0:2])
        self.ax_info = self.fig.add_subplot(gs[2, 2:4])
        self.ax_info.axis("off")

        self.fig.suptitle(
            f"CNN Input Sample  |  shape=({3}, {self.sample_len}, {SP_FREQ_BINS})  "
            f"FFT={SP_FFT_SIZE}  HOP={SP_HOP_SIZE}  fs={SP_SAMPLE_RATE}Hz  "
            f"frames={self.n_frames}",
            fontsize=11, fontproperties=_CN_FONT,
        )

        # 概览标题
        for ax, label in zip(self.ax_overview, ["X", "Y", "Z"]):
            ax.set_title(f"{label}", fontproperties=_CN_FONT, fontsize=10)

        # 通道标题
        for ax, label in zip(self.ax_ch, ["Ch0: X", "Ch1: Y", "Ch2: Z"]):
            ax.set_title(label, fontproperties=_CN_FONT, fontsize=10)

        self.ax_rgb.set_title("RGB Composite (R=X G=Y B=Z)", fontproperties=_CN_FONT, fontsize=10)

        # 滑块
        from matplotlib.widgets import Slider
        max_start = max(self.n_frames - self.sample_len, 0)
        ax_slider = self.fig.add_axes([0.12, 0.02, 0.76, 0.02])
        self.slider = Slider(
            ax_slider, "Start Frame", 0, max_start,
            valinit=0, valstep=1, valfmt="%d",
        )
        self.slider.on_changed(self._on_slider)

        self._draw_sample(0)

    def _draw_sample(self, start: int):
        if self._updating:
            return
        self._updating = True
        try:
            max_start = self.n_frames - self.sample_len
            start = max(0, min(start, max_start))
            self.current_start = start
            end = start + self.sample_len

            freqs = np.arange(SP_FREQ_BINS) * SP_FREQ_RES
            freq_mask = freqs <= 500
            freqs_500 = freqs[freq_mask]

            # ── 行 0: 概览（全时间线 + 绿色窗口高亮）──
            for ax, key in zip(self.ax_overview, ["x", "y", "z"]):
                ax.clear()
                spec = self.specs[key]
                times = np.arange(self.n_frames) * (SP_HOP_SIZE / SP_SAMPLE_RATE)
                ax.pcolormesh(times, freqs, spec.T, shading="auto", cmap="inferno")
                # 高亮窗口
                t0 = start * SP_HOP_SIZE / SP_SAMPLE_RATE
                t1 = end * SP_HOP_SIZE / SP_SAMPLE_RATE
                ax.axvspan(t0, t1, alpha=0.3, color="lime")
                ax.axvline(t0, color="lime", linewidth=0.8)
                ax.axvline(t1, color="lime", linewidth=0.8)
                ax.set_ylim(0, SP_SAMPLE_RATE / 2)
                ax.set_ylabel("Hz", fontproperties=_CN_FONT, fontsize=8)

            self.ax_overview[0].set_title(
                f"Overview  |  frames [{start}:{end}] / {self.n_frames}",
                fontproperties=_CN_FONT, fontsize=10,
            )

            # ── 行 1: 3 通道热力图 (64×512) ──
            sample = {}
            for ax, key in zip(self.ax_ch, ["x", "y", "z"]):
                ax.clear()
                ch_data = self.specs[key][start:end]  # (64, 512)
                sample[key] = ch_data
                # 数据已经是 log10 幅度，直接显示
                im = ax.imshow(
                    ch_data.T, aspect="auto", cmap="inferno",
                    origin="lower", interpolation="nearest",
                    extent=[0, self.sample_len, 0, SP_SAMPLE_RATE / 2],
                )
                ax.set_ylabel("Hz", fontproperties=_CN_FONT, fontsize=8)
                ax.set_xlabel("Frame", fontproperties=_CN_FONT, fontsize=8)

            # ── 行 2 左: 合成 RGB ──
            self.ax_rgb.clear()
            # 数据已是 log10 幅度，percentile clip 归一化到 0-1
            def norm(arr):
                t = arr.T  # (512, 64) 频率×帧
                lo, hi = np.percentile(t, [2, 98])
                return np.clip((t - lo) / (hi - lo + 1e-10), 0, 1)

            rgb = np.stack([
                norm(sample["x"]),
                norm(sample["y"]),
                norm(sample["z"]),
            ], axis=-1)  # (512, 64, 3)  纵轴=频率, 横轴=帧
            self.ax_rgb.imshow(
                rgb, aspect="auto", origin="lower",
                extent=[0, self.sample_len, 0, SP_SAMPLE_RATE / 2],
            )
            self.ax_rgb.set_title("RGB Composite", fontproperties=_CN_FONT, fontsize=10)
            self.ax_rgb.set_ylabel("Hz", fontproperties=_CN_FONT, fontsize=8)
            self.ax_rgb.set_xlabel("Frame", fontproperties=_CN_FONT, fontsize=8)

            # ── 行 2 右: 样本信息 ──
            self.ax_info.clear()
            self.ax_info.axis("off")
            info_lines = [
                f"Sample Shape: ({3}, {self.sample_len}, {SP_FREQ_BINS})",
                f"Data Type: float32",
                f"Time Span: {self.sample_len * SP_HOP_SIZE / SP_SAMPLE_RATE:.3f}s",
                f"Freq Range: 0 ~ {SP_SAMPLE_RATE/2:.0f} Hz",
                f"Freq Res: {SP_FREQ_RES:.2f} Hz/bin",
                f"Start Frame: {start}  ({start * SP_HOP_SIZE / SP_SAMPLE_RATE:.3f}s)",
                f"End Frame: {end}  ({end * SP_HOP_SIZE / SP_SAMPLE_RATE:.3f}s)",
                "",
                "Channel Mapping:",
                "  Ch0 = X axis acceleration",
                "  Ch1 = Y axis acceleration",
                "  Ch2 = Z axis acceleration",
            ]
            self.ax_info.text(
                0.05, 0.95, "\n".join(info_lines),
                transform=self.ax_info.transAxes,
                fontsize=9, verticalalignment="top",
                fontfamily="monospace",
                bbox=dict(boxstyle="round,pad=0.5", facecolor="#f0f0f0", alpha=0.8),
            )

            self.slider.set_val(start)
            self.fig.canvas.draw_idle()
        finally:
            self._updating = False

    def _on_slider(self, val):
        self._draw_sample(int(val))

    def get_current_sample(self) -> np.ndarray:
        """返回当前窗口的 CNN 输入: shape=(3, sample_len, FREQ_BINS), float32"""
        start = self.current_start
        end = start + self.sample_len
        return np.stack([
            self.specs["x"][start:end],
            self.specs["y"][start:end],
            self.specs["z"][start:end],
        ], axis=0).astype(np.float32)

    def show(self):
        plt.show()


def plot_fft_analysis(
    result: dict,
    raw_signals: dict | None = None,
    save_path: str | Path | None = None,
):
    """
    绘制完整的 FFT 分析图:
      行 0: 3 轴时域波形
      行 1: 3 轴频谱图 (时间-频率 热力图)
      行 2: 最后一帧频谱 (全频段)
      行 3: 最后一帧频谱 (0-500Hz 放大)

    raw_signals: {"x": ndarray, "y": ndarray, "z": ndarray} 原始时域信号
    """
    freqs = result["freqs"]
    sr = result["sample_rate"]
    n_samples = result["n_samples"]
    time_axis = np.arange(n_samples) / sr

    axis_labels = ["X", "Y", "Z"]
    keys = ["x", "y", "z"]

    fig, axes = plt.subplots(4, 3, figsize=(18, 14))
    fig.suptitle(
        f"IMU 加速度 FFT 分析  |  FFT={SP_FFT_SIZE}  HOP={SP_HOP_SIZE}  "
        f"fs={sr}Hz  df={SP_FREQ_RES:.2f}Hz  samples={n_samples}",
        fontsize=13, fontproperties=_CN_FONT,
    )

    for col, (key, label) in enumerate(zip(keys, axis_labels)):
        times, spec = result[key]

        # 行 0: 时域波形
        if raw_signals and key in raw_signals:
            axes[0, col].plot(time_axis, raw_signals[key], linewidth=0.3, color="C0")
        axes[0, col].set_title(f"{label} 轴 时域波形", fontproperties=_CN_FONT)
        axes[0, col].set_xlabel("时间 (s)", fontproperties=_CN_FONT)
        axes[0, col].set_ylabel("加速度 (g)", fontproperties=_CN_FONT)
        axes[0, col].grid(True, alpha=0.3)

        # 行 1: 频谱图（数据已是 log10 幅度）
        im = axes[1, col].pcolormesh(
            times, freqs, spec.T, shading="auto", cmap="inferno",
        )
        axes[1, col].set_title(f"{label} 轴 频谱图", fontproperties=_CN_FONT)
        axes[1, col].set_xlabel("时间 (s)", fontproperties=_CN_FONT)
        axes[1, col].set_ylabel("频率 (Hz)", fontproperties=_CN_FONT)
        axes[1, col].set_ylim(0, sr / 2)
        plt.colorbar(im, ax=axes[1, col], label="幅度 (dB)")

        # 行 2: 最后一帧频谱 (全频段)
        last_spec = spec[-1]
        axes[2, col].plot(freqs, last_spec, linewidth=0.8, color="C1")
        axes[2, col].set_title(f"{label} 轴 最后一帧频谱 (全频段)", fontproperties=_CN_FONT)
        axes[2, col].set_xlabel("频率 (Hz)", fontproperties=_CN_FONT)
        axes[2, col].set_ylabel("幅度", fontproperties=_CN_FONT)
        axes[2, col].grid(True, alpha=0.3)

        # 行 3: 最后一帧频谱 (0-500Hz)
        mask = freqs <= 500
        axes[3, col].plot(freqs[mask], last_spec[mask], linewidth=1.0, color="C2")
        axes[3, col].set_title(f"{label} 轴 最后一帧频谱 (0-500Hz)", fontproperties=_CN_FONT)
        axes[3, col].set_xlabel("频率 (Hz)", fontproperties=_CN_FONT)
        axes[3, col].set_ylabel("幅度", fontproperties=_CN_FONT)
        axes[3, col].grid(True, alpha=0.3)

    plt.tight_layout()

    if save_path:
        fig.savefig(str(save_path), dpi=150)
        print(f"图表已保存: {save_path}")

    plt.show()


def plot_time_domain(
    ax: np.ndarray, ay: np.ndarray, az: np.ndarray,
    sample_rate: float, save_path: str | Path | None = None,
):
    """绘制 3 轴时域波形"""
    n = len(ax)
    t = np.arange(n) / sample_rate

    fig, axes = plt.subplots(3, 1, figsize=(14, 8), sharex=True)
    fig.suptitle("IMU 加速度 时域波形", fontsize=13, fontproperties=_CN_FONT)

    for i, (sig, label) in enumerate(zip([ax, ay, az], ["X", "Y", "Z"])):
        axes[i].plot(t, sig, linewidth=0.3, color=f"C{i}")
        axes[i].set_ylabel(f"{label} (g)", fontproperties=_CN_FONT)
        axes[i].grid(True, alpha=0.3)

    axes[-1].set_xlabel("时间 (s)", fontproperties=_CN_FONT)
    plt.tight_layout()

    if save_path:
        fig.savefig(str(save_path), dpi=150)
        print(f"时域图已保存: {save_path}")

    plt.show()
