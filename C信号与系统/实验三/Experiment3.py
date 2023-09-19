import numpy
import numpy as np
import matplotlib.pyplot as plt


def h(w):
    """
    原函数的傅里叶变换
    :param w : omega
    :return: omega 变换后的傅里叶变换
    """
    return np.sin(np.pi * w) / (w * (1 - w ** 2))


def f(t: np.arange):
    """
    返回参数为t的原函数
    """
    return 0.5 * (1 + np.cos(t)) * (np.heaviside(t + np.pi, 0) - np.heaviside(t - np.pi, 0))


def expr1_1_1():
    t = np.arange(-np.pi, np.pi, 0.01)
    f0 = f(t)
    # f = 0.5 * (1 + np.cos(t)) * (np.heaviside(t + np.pi, 0) - np.heaviside(t - np.pi, 0))
    plt.plot(t, f0)
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f(t)")
    plt.title("Figure 1.1.1: Origin Function Time Domain Diagram")
    plt.show()

    w = np.linspace(-20, 20, 1000)
    F = h(w)




# expr1_1_1()


def expr1_1_2():
    # 绘制f(t)的频谱

    w = np.linspace(-20, 20, 1000)
    h0 = h(w)

    # 幅度谱
    plt.plot(w, abs(h0))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("amplitude")
    plt.title("Figure 1.1.2: Origin Function Amplitude Spectrum")
    plt.show()

    # 相位谱
    plt.plot(w, numpy.angle(h0))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("phase")
    plt.title("Figure 1.1.3: Origin Function Phase Spectrum")
    plt.show()


# expr1_1_2()

def expr1_2_1():
    # 0.5s为间隔
    t = np.arange(-np.pi, np.pi, 0.5)  # 取样间隔设置为0.5
    f0 = f(t)
    # 时域波形
    plt.stem(t, f0)
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f(t)")
    plt.title("Figure 1.2.1: Sampling Function(0.5s) Time Domain Diagram")
    plt.show()

    w = np.linspace(-20, 20, 1000)
    F = h(w)
    for i in range(1, 3):
        F += h(w + i * 4 * np.pi)
        F += h(w - i * 4 * np.pi)

    # 幅度谱
    plt.plot(w, abs(F * 2))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Amplitude")
    plt.title("Figure 1.2.2: Sampling Function(0.5s) Amplitude Spectrum")
    plt.show()

    # 相位谱
    plt.plot(w, np.angle(F * 2))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("phase")
    plt.title("Figure 1.2.3: Sampling Function(0.5s) Phase Spectrum")
    plt.show()


expr1_2_1()

def expr1_2_2():
    # 1s为间隔
    t = np.arange(-np.pi, np.pi, 1)
    f0 = f(t)
    plt.stem(t, f0)
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f(t)")
    plt.title("Figure 1.2.4: Sampling Function(1s) Time Domain Diagram")
    plt.show()

    w = np.linspace(-20, 20, 1000)
    F = h(w)
    for i in range(1, 5):
        F += h(w + i * 2 * np.pi)
        F += h(w - i * 2 * np.pi)

    # 幅度谱
    plt.plot(w, abs(F))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Amplitude")
    plt.title("Figure 1.2.5: Sampling Function(1s) Amplitude Spectrum")
    plt.show()

    # 相位谱
    plt.plot(w, np.angle(F))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Phase")
    plt.title("Figure 1.2.6: Sampling Function(1s) Phase Spectrum")
    plt.show()


# expr1_2_2()


def expr1_2_3():
    # 2s为间隔
    t = np.arange(-np.pi, np.pi, 2)
    f0 = f(t)
    plt.stem(t, f0)
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f(t)")
    plt.title("Figure 1.2.7: Sampling Function(2s) Time Domain Diagram")
    plt.show()

    w = np.linspace(-20, 20, 1000)
    F = h(w)
    for i in range(1, 10):
        F += h(w + i * np.pi)
        F += h(w - i * np.pi)

    # 幅度谱
    plt.plot(w, abs(F / 2))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Amplitude")
    plt.title("Figure 1.2.8: Sampling Function(2s) Amplitude Spectrum")
    plt.show()

    # 相位谱
    plt.plot(w, np.angle(F / 2))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Phase")
    plt.title("Figure 1.2.9: Sampling Function(2s) Phase Spectrum")
    plt.show()


# expr1_2_3()


def expr1_3():
    # 截取前三个周期
    t = np.arange(-np.pi, np.pi, 0.01)
    f1 = f(t)
    # h1 = h()
    w = np.linspace(-20, 20, 1000)
    # F0 = h(w)   # F0为0.5s抽样函数的频谱，初始赋值为原函数的傅里叶变换
    F1 = h(w)   # F1为1s抽样函数的频谱，初始赋值为原函数的傅里叶变换
    # F2 = h(w)

    # for i in range(1, 3):
    #     F0 += h(w + i * 4 * np.pi)
    #     F0 += h(w - i * 4 * np.pi)

    for i in range(1, 5):
        F1 += h(w + i * 2 * np.pi)
        F1 += h(w - i * 2 * np.pi)

    # for i in range(1, 10):  # omega从1递增到3叠加
    #     F2 += h(w + i * np.pi)
    #     F2 += h(w - i * np.pi)

    plt.plot(t, f1)
    # plt.plot(w, abs(F0 * 2))
    plt.plot(w, abs(F1))
    # plt.plot(w, abs(F2 / 2))
    plt.grid()
    plt.xlabel("w")
    plt.ylabel("Amplitude")
    plt.title("Figure 1.3: Sampling Function(0.5s,1s,2s) Amplitude Spectrum")
    plt.show()


# expr1_3()


def expr2_1():
    # 取样间隔为0.5s
    t0 = np.arange(-np.pi, np.pi, 0.5)  # 自变量取值范围，间隔0.5
    F0 = f(0) * np.sinc(2.4 * t0)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F0 += f(i * 0.5) * np.sinc(2.4 * (t0 - i * 0.5))
        F0 += f(i * 0.5) * np.sinc(2.4 * (t0 + i * 0.5))

    plt.stem(t0, f(t0), label='Origin', markerfmt='gD')  # 原函数
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.1: Sampling Function(0.5s) Origin")
    plt.legend()
    plt.show()

    # 取样间隔为1s
    t1 = np.arange(-np.pi, np.pi, 1)  # 自变量取值范围，间隔1
    F1 = f(0) * np.sinc(2.4 * t1)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F1 += f(i * 1) * np.sinc(2.4 * (t1 - i * 1))
        F1 += f(i * 1) * np.sinc(2.4 * (t1 + i * 1))
    plt.stem(t1, f(t1), label='Origin', markerfmt='gD')  # 原函数
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.2: Sampling Function(1s) Origin")
    plt.legend()
    plt.show()

    # 取样间隔为2s
    t2 = np.arange(-np.pi, np.pi, 2)  # 自变量取值范围，间隔1
    F2 = f(0) * np.sinc(2.4 * t2)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F2 += f(i * 2) * np.sinc(2.4 * (t2 - i * 2))
        F2 += f(i * 2) * np.sinc(2.4 * (t2 + i * 2))
    plt.stem(t2, f(t2), label='Origin', markerfmt='gD')  # 原函数
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.3: Sampling Function(1s) Origin")
    plt.legend()
    plt.show()


# expr2_1()


def expr2_2():
    # 取样间隔为0.5s
    t0 = np.arange(-np.pi, np.pi, 0.5)  # 自变量取值范围，间隔0.5
    F0 = f(0) * np.sinc(2.4 * t0)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F0 += f(i * 0.5) * np.sinc(2.4 * (t0 - i * 0.5))
        F0 += f(i * 0.5) * np.sinc(2.4 * (t0 + i * 0.5))

    plt.stem(t0, F0 * 2.4 * 0.5 / np.pi, label='Reconstruction', markerfmt='rD')  # 重建函数
    plt.stem(t0, f(t0), label='Origin', markerfmt='gD')  # 原函数
    plt.plot(t0, abs(F0 * 2.4 * 0.5 / np.pi - f(t0)), label='Difference', color='orange')  # 差值的绝对值
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.1: Sampling Function(0.5s) Reconstruction")
    plt.legend()
    plt.show()

    # 取样间隔为1s
    t1 = np.arange(-np.pi, np.pi, 1)  # 自变量取值范围，间隔1
    F1 = f(0) * np.sinc(2.4 * t1)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F1 += f(i * 1) * np.sinc(2.4 * (t1 - i * 1))
        F1 += f(i * 1) * np.sinc(2.4 * (t1 + i * 1))

    plt.stem(t1, F1 * 2.4 * 1 / np.pi, label='Reconstruction', markerfmt='rD')  # 重建函数
    plt.stem(t1, f(t1), label='Origin', markerfmt='gD')  # 原函数
    plt.plot(t1, abs(F1 * 2.4 * 1 / np.pi - f(t1)), label='Difference', color='orange')  # 差值的绝对值
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.2: Sampling Function(1s) Reconstruction")
    plt.legend()
    plt.show()

    # 取样间隔为2s
    t2 = np.arange(-np.pi, np.pi, 2)  # 自变量取值范围，间隔1
    F2 = f(0) * np.sinc(2.4 * t2)  # 重建信号初始值
    for i in range(1, 10):  # K从1递增到10叠加
        F2 += f(i * 2) * np.sinc(2.4 * (t2 - i * 2))
        F2 += f(i * 2) * np.sinc(2.4 * (t2 + i * 2))

    plt.stem(t2, F2 * 2.4 * 2 / np.pi, label='Reconstruction', markerfmt='rD')  # 重建函数
    plt.stem(t2, f(t2), label='Origin', markerfmt='gD')  # 原函数
    plt.plot(t2, abs(F2 * 2.4 * 2 / np.pi - f(t2)), label='Difference', color='orange')  # 差值的绝对值
    plt.grid()
    plt.xlabel("time[s]")
    plt.ylabel("f")
    plt.title("Figure 2.1.3: Sampling Function(1s) Reconstruction")
    plt.legend()
    plt.show()


# expr2_2()

