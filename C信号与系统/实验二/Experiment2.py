import numpy as np
import matplotlib.pyplot as plt
# import scipy.signal as sgn
import sympy as 

# 非周期信号的FT实验
def ex1_1():
    # 生成时间序列，区间-10到10，步长0.01
    t = np.arange(-10, 10, 0.01)
    f = np.exp(-t) * np.heaviside(t, 1)

    # plt.plot(t, f)
    # plt.grid()
    # plt.xlabel("time[s]")
    # plt.ylabel("value")
    # plt.title("Figure 1.1.1 : Waveform")
    # plt.show()

    # 在-10到10范围内生成序列，共1000个点，所以步长为20/1000 = 0.02
    w = np.linspace(-10, 10, 1000)
    H = 1 / (1j * w + 1)

    # 相位谱
    plt.plot(w, np.angle(H))
    plt.grid()
    plt.xlabel("frequency")
    plt.ylabel("phase")
    plt.title("Figure1.1.2 : Phase Spectrum")
    plt.show()

    # 幅度谱
    plt.plot(w, abs(H))
    plt.grid()
    plt.xlabel("frequency")
    plt.ylabel("amplitude")
    plt.title("Figure 1.1.3 : Amplitude Spectrum")
    plt.show()

ex1_1()

def test():
    t = np.linspace(-0.999, 1.001, 2000)
    # t = np.arange(-0.99, 1.01, 0.01)
    f = np.heaviside(t, 1)

    plt.plot(t, f)
    plt.show()

# test()

def ex1_2():
