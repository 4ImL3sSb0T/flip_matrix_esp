"""
IMU 加速度数据 FFT 频谱分析
对应固件: src/service/signal_process/imu_data_process.c
"""

from pathlib import Path

from src.data_loader import load_xlsx, find_xlsx, remove_dc_offset
from src.fft_processor import process_3axis
from src.visualizer import plot_fft_analysis, plot_time_domain


def main():
    data_dir = Path(__file__).parent / "data"
    xlsx_path = find_xlsx(data_dir)
    if not xlsx_path:
        print("data/ 目录下没有找到 xlsx 文件")
        return

    # 1. 加载原始数据
    print(f"读取: {xlsx_path.name}")
    ax_raw, ay_raw, az_raw = load_xlsx(xlsx_path)
    print(f"总采样数: {len(ax_raw)}")

    # 2. 用前 10000 行静态数据去除直流偏移, 只保留交流分量
    ax, ay, az = remove_dc_offset(ax_raw, ay_raw, az_raw, static_n=10000)

    # 3. FFT 处理 (交流分量)
    result = process_3axis(ax, ay, az)

    # 4. 可视化
    out_dir = Path(__file__).parent
    raw_signals = {"x": ax, "y": ay, "z": az}
    plot_fft_analysis(
        result, raw_signals=raw_signals,
        save_path=out_dir / "fft_analysis.png",
    )


if __name__ == "__main__":
    main()
