# from tkinter import Y
# from turtle import color
# from matplotlib.ft2font import FAST_GLYPHS
from turtle import color
import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sgn


def ex1_1():
    t = np.arange(-1, 5, 0.01)
    func_x = np.sin(2 * np.pi * t) * (np.heaviside(t, 1) - np.heaviside(t - 3, 1))
    plt.plot(t, func_x)
    plt.xlabel("t[s]")
    plt.ylabel("x(t)")
    plt.title("Figure 1.1: x(t)")
    plt.show()

# ex1_1()

def ex1_2():
    t = np.arange(-10, 10, 0.01)
    func_h = np.exp(-t) * np.heaviside(t, 1) - np.exp(-2 * t) * np.heaviside(t, 1)
    plt.plot(t, func_h)
    plt.xlabel("t[s]")
    plt.ylabel("h(t)")
    plt.title("Figure 1.2: h(t)")
    plt.show()

# ex1_2()

def ex1_3():
    t = np.arange(-4, 4, 0.01)
    func_G1 = np.heaviside(t + 1, 1)  - np.heaviside(t - 1, 1)
    func_y = 2 * func_G1
    plt.plot(t, func_y)
    plt.xlabel("t[s]")
    plt.ylabel("h(t)")
    plt.title("Figure 1.3: h(t)")
    plt.show()

ex1_3()

def ex2_1():
    t = np.arange(-3, 3, 0.01)
    func_G = np.heaviside(t + 0.5, 1)  - np.heaviside(t - 0.5, 1)
    func_y1 = np.heaviside(2 * t + 0.5, 1)  - np.heaviside(2 * t - 0.5, 1)
    func_y2 = np.heaviside(t / 2 + 0.5, 1)  - np.heaviside(t / 2 - 0.5, 1)
    func_y3 = np.heaviside((1 - 2 * t) + 0.5, 1)  - np.heaviside((1 - 2 * t) - 0.5, 1)
    plt.subplot(3, 1, 1)
    plt.plot(t, func_G)
    plt.plot(t, func_y1, color = 'red')
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.legend(['y(t)','y(2t)'])
    plt.title("Figure2.1: y(t) y(2t) y(t/2) y(1-2t)")

    plt.subplot(3, 1, 2)
    plt.plot(t, func_G)
    plt.plot(t, func_y2, color = 'red')
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.legend(['y(t)','y(t/2)'])

    plt.subplot(3, 1, 3)
    plt.plot(t, func_G)
    plt.plot(t, func_y3, color = 'red')
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.legend(['y(t)','y(1-2t)'])

    plt.show()

# ex2_1()

def ex2_2():
    t = np.arange(-100, 100, 0.01)
    func_y = np.cos(t) + np.cos(np.pi * t / 4)
    plt.plot(t, func_y)
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.title("Figure2.2: y(t) = cos(t) + cos(pi * t / 4)")
    plt.grid()
    plt.plot()
    plt.show()

# ex2_2()

# def ex2():
#     t = np.arange(-100, 100, 0.01)
#     y = np.sin(t) + np.sin(np.pi * t / 4)
  
#     plt.plot(t, y)
#     plt.xlabel("t[s]")
#     plt.ylabel("y(t)")
#     plt.title("Figure 2.2: y(t)=sin(t)+sin(pi*t/4)")
#     plt.grid()
#     plt.plot()
#     plt.show()

# ex2()

def ex2_3():
    t = np.arange(-6, 6, 0.01)
    func_y = np.cos(np.pi * t) + np.cos(2 * np.pi * t)
    plt.plot(t, func_y)
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.title("Figure2.3: y(t) = cos(pi * t) + cos(2 * pi *t)")
    plt.grid()
    plt.show()

# ex2_3()

def ex3_2():
    t = np.arange(0, 5, 0.01)
    func_y1 = np.exp(-2 * t) * np.heaviside(t, 0)
    func_y2 = np.exp(-3 * t) * np.heaviside(t, 0)
    func_y = sgn.convolve(func_y1, func_y2) * 0.01

    plt.subplot(3, 1, 1)
    plt.plot(np.arange(0, 9.99, 0.01), func_y, label = "simulate")
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.legend()
    plt.title("Figure3.2: Convolution")
   

    t_theory = np.arange(0, 10, 0.01)
    y_theory = (np.exp(-2 * t_theory) - np.exp(-3 * t_theory)) * np.heaviside(t_theory, 0)

    plt.subplot(3, 1, 2)
    plt.plot(t_theory, y_theory, color = 'red',label = "theory")
    plt.xlabel("t[s]")
    plt.ylabel("y(t)")
    plt.legend()

    plt.subplot(3, 1, 3)
    plt.plot(np.arange(0, 9.99, 0.01), func_y)
    plt.plot(t_theory, y_theory, color = 'red')
    plt.ylabel("y(t)")
    plt.xlabel("t[s]")
    plt.legend

    plt.show()

# ex3_2()


def ex4_2():
    system = sgn.lti([1], [1, 3, 2])
    t = np.arange(0, 10, 0.01)
    func = np.exp(-2 * t) * np.heaviside(t, 0)
    theory = np.exp(-1 * t) - (1 + t) * np.exp(-2 * t)
    plt.subplot(3 ,1 , 1)
    plt.plot(t, theory)
    plt.ylabel("r_ZS")
    plt.title("Figure 4: Zero-State Response")

    tout, yout, xout = sgn.lsim(system, func, t)

    plt.subplot(3, 1, 2)
    plt.plot(tout, yout, color = "red", label = "simulate")
    plt.xlabel("t[s]")
    plt.ylabel("r_ZS")

    plt.subplot(3, 1, 3)
    plt.plot(t, theory, label = "theory")
    plt.plot(tout, yout, color = "red", label = "simulate")
    plt.xlabel("t[s]")
    plt.ylabel("r_ZS")
    plt.legend()
    plt.show()

# ex4_2()


# import numpy as np
# import matplotlib.pyplot as plt
# import scipy.signal as sgn

# def ex4():
#     # 线性时不变系统
#     system = sgn.lti([1], [1, 3, 2])
#     # 自变量取值
#     t = np.arange(0, 10, 0.01)
#     # f(t)
#     f = np.exp(-2 * t) * np.heaviside(t, 0)
#     # 理论值
#     y = np.exp(-t)-(1+t) * np.exp(-2*t)
#     plt.subplot(2, 1, 1) #指定图像位置
#     plt.plot(t,y) #作图理论值
#     plt.ylabel("r_ZS")
#     plt.title('Figure 4: Zero-State Response')
#     #用lsim函数获取系统零状态响应
#     tout, yout, xout = sgn.lsim(system, f, t)
#     plt.subplot(2, 1, 2)
#     plt.plot(t, y ,label='theory')
#     plt.plot(tout, yout, label='simulate') #python仿真值
#     plt.xlabel("t[s]")
#     plt.ylabel("r_ZS")
#     plt.legend()
#     plt.show()
  
# ex4()

def ex5_1():
    t = np.linspace(-5, 5, 500, endpoint = False)
    plt.plot(t, 1 + sgn.square(np.pi * (t + 0.5)))
    plt.grid()
    plt.show()

# ex5_1()


def SumOf_firstNitems(n : int, t : np.arange) -> np.arange:
    sum : np.ndarray = np.ones(np.size(t),dtype=complex)
    if (n == 1):
        return sum;
    elif (n > 1):
        n = int( 2 * n - 2 )
        for i in range(1, n):
            sum += (4 * np.sin(np.pi * i / 2) * np.cos(np.pi * i * t) / np.pi / i)
        return sum
    else :
        print("invalid input")

def ex5_2():
    t = np.arange(-7, 7, 0.01)
    y = sgn.square(np.pi * (t + 0.5)) + 1

    # y = scipy.signal

    # 前3项之和
    # y1 = 1 + 4 * np.cos(np.pi * t) / np.pi - 4 * np.cos(3 * np.pi * t) / np.pi / 3
    y1 = SumOf_firstNitems(3, t)

    # 前5项之和
    # y2 = 1 + 4 * np.cos(np.pi * t) / np.pi - 4 * np.cos(3 * np.pi * t) / np.pi / 3 + 4 * np.cos(5 * np.pi * t) / np.pi / 5 - 2 * np.cos(7 * np.pi *t) / np.pi / 7
    y2 = SumOf_firstNitems(5, t)

    y3 = SumOf_firstNitems(20, t)
    plt.subplot(3, 1, 1)
    plt.plot(t, y)
    plt.plot(t, y1, color = "red")
    plt.ylabel("f(t)")
    plt.legend(["origen", "first 3 items"])
    plt.title("Figure 5.2 : first 3 (and 5) items")

    plt.subplot(3, 1, 2)
    plt.plot(t, y)
    plt.plot(t, y2, color = "red")
    plt.xlabel("t[s]")
    plt.ylabel("f(t)")
    plt.legend(["origen", "first 5 items"])

    plt.subplot(3, 1, 3)
    plt.plot(t, y)
    plt.plot(t, y3, color = "red")
    plt.xlabel("t[s]")
    plt.ylabel("f(t)")
    plt.legend(["origen", "first 20 items"])

    plt.show()

# ex5_2()

def sumOf_firstNitems(n : int , t : np.arange) -> np.arange:
    sum : np.ndarray = np.ones(np.size(t),dtype=complex)

    if n == 1:
        return sum
    elif n > 1:
        n = int(n / 2) + 1
        flag : int = 1
        for i in range(1, n):
            sum += flag * 2.0 * (np.exp(1j * np.pi * t * (2 * i - 1)) + np.exp(-1j * np.pi * t * (2 * i - 1))) / (np.pi * (2 * i - 1))
            flag = -flag
        return sum
    
    else:
        print("invalid input")

def ex5_3():
    t = np.arange(-7, 7, 0.01)
    y = sgn.square(np.pi * (t + 0.5)) + 1

    # 前3项和
    # y3 = 1 + np.exp(1j * np.pi * t) * 2 / np.pi + np.exp(-1j * np.pi * t) * 2 / np.pi
    y3 = sumOf_firstNitems(3, t)

    # 前5项和
    # y5 = 1 + np.exp(1j * np.pi * t) * 2 / np.pi + np.exp(-1j * np.pi * t) * 2 / np.pi - np.exp(3j * np.pi * t) * 2 / np.pi / 3 - np.exp(-3j * np.pi * t) * 2 / np.pi / 3
    y5 = sumOf_firstNitems(5, t)

    # 前21项和
    y21 = sumOf_firstNitems(21, t)


    plt.subplot(3, 1, 1)
    plt.plot(t, y)
    plt.plot(t, y3.real, color = 'red')
    plt.ylabel("f(t)")
    plt.legend(["origen", "first 3 items"])
    plt.subplot(3, 1, 2)

    plt.plot(t, y)
    plt.plot(t, y5.real, color = 'red')
    plt.ylabel("f(t))")
    plt.legend(["origen", "first 5 items"])
    plt.subplot(3, 1, 3)

    plt.plot(t, y)
    plt.plot(t, y21.real, color = 'red')
    plt.xlabel("t[s]")
    plt.ylabel("f(t))")
    plt.legend(["origen", "first 21 items"])
    plt.show()

# ex5_3()



