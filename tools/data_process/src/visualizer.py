"""IMU FFT 结果可视化"""

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from pathlib import Path

from .fft_processor import (
    SP_FFT_SIZE, SP_HOP_SIZE, SP_SAMPLE_RATE, SP_FREQ_RES, SP_FREQ_BINS,
)

# 中文字体支持 (Windows: Microsoft YaHei)
matplotlib.rcParams["font.sans-serif"] = ["Microsoft YaHei", "SimHei", "DejaVu Sans"]
matplotlib.rcParams["axes.unicode_minus"] = False


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
        fontsize=13,
    )

    for col, (key, label) in enumerate(zip(keys, axis_labels)):
        times, spec = result[key]

        # 行 0: 时域波形
        if raw_signals and key in raw_signals:
            axes[0, col].plot(time_axis, raw_signals[key], linewidth=0.3, color="C0")
        axes[0, col].set_title(f"{label} 轴 时域波形")
        axes[0, col].set_xlabel("时间 (s)")
        axes[0, col].set_ylabel("加速度 (g)")
        axes[0, col].grid(True, alpha=0.3)

        # 行 1: 频谱图
        spec_db = 20 * np.log10(spec + 1e-10)
        im = axes[1, col].pcolormesh(
            times, freqs, spec_db.T, shading="auto", cmap="inferno",
        )
        axes[1, col].set_title(f"{label} 轴 频谱图")
        axes[1, col].set_xlabel("时间 (s)")
        axes[1, col].set_ylabel("频率 (Hz)")
        axes[1, col].set_ylim(0, sr / 2)
        plt.colorbar(im, ax=axes[1, col], label="幅度 (dB)")

        # 行 2: 最后一帧频谱 (全频段)
        last_spec = spec[-1]
        axes[2, col].plot(freqs, last_spec, linewidth=0.8, color="C1")
        axes[2, col].set_title(f"{label} 轴 最后一帧频谱 (全频段)")
        axes[2, col].set_xlabel("频率 (Hz)")
        axes[2, col].set_ylabel("幅度")
        axes[2, col].grid(True, alpha=0.3)

        # 行 3: 最后一帧频谱 (0-500Hz)
        mask = freqs <= 500
        axes[3, col].plot(freqs[mask], last_spec[mask], linewidth=1.0, color="C2")
        axes[3, col].set_title(f"{label} 轴 最后一帧频谱 (0-500Hz)")
        axes[3, col].set_xlabel("频率 (Hz)")
        axes[3, col].set_ylabel("幅度")
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
    fig.suptitle("IMU 加速度 时域波形", fontsize=13)

    for i, (sig, label) in enumerate(zip([ax, ay, az], ["X", "Y", "Z"])):
        axes[i].plot(t, sig, linewidth=0.3, color=f"C{i}")
        axes[i].set_ylabel(f"{label} (g)")
        axes[i].grid(True, alpha=0.3)

    axes[-1].set_xlabel("时间 (s)")
    plt.tight_layout()

    if save_path:
        fig.savefig(str(save_path), dpi=150)
        print(f"时域图已保存: {save_path}")

    plt.show()
