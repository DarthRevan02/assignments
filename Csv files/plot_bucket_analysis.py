r"""Plot AvgTime vs SizeOfArray from ANALYSIS_Bucket.csv with a quadratic fit and R^2.

Saves 'ANALYSIS_Bucket_quadratic_fit.png' in the same folder.
"""
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def main():
    csv_path = os.path.join(os.path.dirname(__file__), 'ANALYSIS_Bucket.csv')
    if not os.path.exists(csv_path):
        raise FileNotFoundError(f"CSV not found: {csv_path}")

    df = pd.read_csv(csv_path)
    x = df['SizeOfArray'].values.astype(float)
    y = df['AvgTime'].values.astype(float)

    coeffs = np.polyfit(x, y, 2)
    p = np.poly1d(coeffs)
    y_pred = p(x)
    ss_res = np.sum((y - y_pred) ** 2)
    ss_tot = np.sum((y - np.mean(y)) ** 2)
    r2 = 1 - ss_res / ss_tot if ss_tot != 0 else float('nan')

    x_smooth = np.linspace(x.min(), x.max(), 500)
    y_smooth = p(x_smooth)

    try:
        plt.style.use('seaborn-darkgrid')
    except OSError:
        plt.style.use('ggplot')
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.scatter(x, y, color='tab:blue', label='AvgTime (data)')
    ax.plot(x_smooth, y_smooth, color='tab:orange', lw=2, label='Quadratic fit')
    ax.set_xlabel('Array size')
    ax.set_ylabel('Avg time (seconds)')
    ax.set_title('Bucket Sort: Avg Time vs Array Size (Quadratic fit)')

    a, b, c = coeffs
    eqn = f"y = {a:.3e} x^2 + {b:.3e} x + {c:.3e}\nR^2 = {r2:.5f}"
    ax.text(0.02, 0.98, eqn, transform=ax.transAxes, fontsize=9,
            verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))

    ax.legend()
    out_path = os.path.join(os.path.dirname(__file__), 'ANALYSIS_Bucket_quadratic_fit.png')
    fig.tight_layout()
    fig.savefig(out_path, dpi=200)
    print(f"Saved plot to: {out_path}")
    print(f"Quadratic coefficients (a,b,c): {a}, {b}, {c}")
    print(f"R^2 = {r2:.6f}")


if __name__ == '__main__':
    main()
