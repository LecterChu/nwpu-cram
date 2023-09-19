# -*- coding: utf-8 -*-

import cv2
import numpy as np
from matplotlib import pyplot as plt


# Harris角点检测
def myHarris(img, ksize, sigma, k, threshold, NMS=False):
    """
    自己实现Harris角点检测
    """

    # 1.使用Sobel计算像素点在x,y方向的梯度
    h, w = img.shape[:2]
    grad = np.zeros((h, w, 2), dtype=np.float32)
    # 使用Sobel函数求完导数后会有负值以及大于255的值。所以要用16位有符号的数据类型
    # x方向求导
    grad[:, :, 0] = cv2.Sobel(img, cv2.CV_16S, 1, 0, ksize=3)
    # y方向求导
    grad[:, :, 1] = cv2.Sobel(img, cv2.CV_16S, 0, 1, ksize=3)

    # print(grad)

    # 2.计算Ix^2,Iy^2,Ix*Iy
    m = np.zeros((h, w, 3), dtype=np.float32)
    m[:, :, 0] = grad[:, :, 0] ** 2
    m[:, :, 1] = grad[:, :, 1] ** 2
    m[:, :, 2] = grad[:, :, 0] * grad[:, :, 1]
    # print(m)
    # print()

    # 3.高斯滤波
    m[:, :, 0] = cv2.GaussianBlur(m[:, :, 0], ksize=(ksize, ksize), sigmaX=sigma)
    m[:, :, 1] = cv2.GaussianBlur(m[:, :, 1], ksize=(ksize, ksize), sigmaX=sigma)
    m[:, :, 2] = cv2.GaussianBlur(m[:, :, 2], ksize=(ksize, ksize), sigmaX=sigma)
    m = [np.array([[m[i, j, 0], m[i, j, 2]], [m[i, j, 2], m[i, j, 1]]]) for i in range(h) for j in range(w)]
    # print(m)

    # 4.计算局部特征结果矩阵M的特征值和相应函数R（i，j）=det（M）-k（trace（M））^ 2  0.04 <= k <= 0.06
    D, T = list(map(np.linalg.det, m)), list(map(np.trace, m))
    R = np.array([d - k * t ** 2 for d, t in zip(D, T)])

    # 5.将计算出的响应函数R进行非极大值抑制NMS，除去一些不是角点的点，同时要满足大于设定的阈值
    # 获取最大的R值
    R_max = np.max(R)
    R = R.reshape(h, w)
    corner = np.zeros_like(R, dtype=np.uint8)
    for i in range(h):
        for j in range(w):
            if NMS:
                if R[i, j] > R_max * threshold and R[i, j] == np.max(
                        R[max(0, i - 1):min(i + 2, h - 1), max(0, j - 1):min(j + 2, w - 1)]):
                    corner[i, j] = 255
            else:
                if R[i, j] > R_max * threshold:
                    corner[i, j] = 255

    return corner


def harris_cv2(img, blockSize, ksize, k, threshold):
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img_gray = np.float32(img_gray)
    img_corner = cv2.cornerHarris(img_gray, blockSize, ksize, k)
    img[img_corner > threshold * img_corner.max()] = [0, 0, 255]
    return img


def doHarris_withDifferentKsize(img_path):

    img = cv2.imread(img_path)
    img = cv2.resize(img, dsize=(512, 512), interpolation=cv2.INTER_CUBIC)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    result_myHarrisWithoutNMS = []
    result_myHarrisWithNMS = []
    result_cv2Harris = []

    for i in range(3, 10, 2):
        myHarrisWithoutNMS = myHarris(gray, ksize=i, sigma=2, k=0.05, threshold=0.01, NMS=False)
        myHarrisWithNMS = myHarris(gray, ksize=i, sigma=2, k=0.05, threshold=0.01, NMS=True)

        max_WithoutNMS = myHarrisWithoutNMS.max()
        result_rgb = img.copy()
        result_rgb[myHarrisWithoutNMS == max_WithoutNMS] = [0, 0, 255]
        result_myHarrisWithoutNMS.append(result_rgb)

        max_WithNMS = myHarrisWithNMS.max()
        result_rgb_NMS = img.copy()
        result_rgb_NMS[myHarrisWithNMS == max_WithNMS] = [0, 0, 255]
        result_myHarrisWithNMS.append(result_rgb_NMS)

        result_rgb_cv2 = img.copy()
        cv2Harris = harris_cv2(result_rgb_cv2, i, 3, 0.05, 0.01)
        result_cv2Harris.append(cv2Harris)

    plt.figure(figsize=(15, 8))
    for i in range(4):
        plt.subplot(4, 3, i * 3 + 1)
        plt.imshow(cv2.cvtColor(result_myHarrisWithoutNMS[i], cv2.COLOR_BGR2RGB))
        plt.title(f'Check with myHarris without NMS, ksize = {2*(i+1)+1}')
        plt.subplot(4, 3, i * 3 + 2)
        plt.imshow(cv2.cvtColor(result_myHarrisWithNMS[i], cv2.COLOR_BGR2RGB))
        plt.title(f'Check with myHarris with NMS, ksize = {2*(i+1)+1}')
        plt.subplot(4, 3, i * 3 + 3)
        plt.imshow(cv2.cvtColor(result_cv2Harris[i], cv2.COLOR_BGR2RGB))
        plt.title(f'Check with cv2Harris with NMS, ksize = {2*(i+1)+1}')
    plt.tight_layout()
    plt.show()


def doHarris_withDifferentThreshold(img_path):
    img = cv2.imread(img_path)
    img = cv2.resize(img, dsize=(512, 512), interpolation=cv2.INTER_CUBIC)
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

    result_myHarrisWithoutNMS = []
    result_myHarrisWithNMS = []
    result_cv2Harris = []

    for i in range(1, 5, 1):
        threshold = i * 0.05
        myHarrisWithoutNMS = myHarris(gray, 5, 2, 0.05, threshold, NMS=False)
        myHarrisWithNMS = myHarris(gray, 5, 2, 0.05, threshold, NMS=True)

        max_WithoutNMS = myHarrisWithoutNMS.max()
        result_rgb = img.copy()
        result_rgb[myHarrisWithoutNMS == max_WithoutNMS] = [0, 0, 255]
        result_myHarrisWithoutNMS.append(result_rgb)

        max_WithNMS = myHarrisWithNMS.max()
        result_rgb_NMS = img.copy()
        result_rgb_NMS[myHarrisWithNMS == max_WithNMS] = [0, 0, 255]
        result_myHarrisWithNMS.append(result_rgb_NMS)

        result_rgb_cv2 = img.copy()
        cv2Harris = harris_cv2(result_rgb_cv2, 5, 3, 0.05, threshold)
        result_cv2Harris.append(cv2Harris)

    plt.figure(figsize=(15, 8))
    for i in range(4):
        plt.subplot(4, 3, i * 3 + 1)
        plt.imshow(cv2.cvtColor(result_myHarrisWithoutNMS[i], cv2.COLOR_BGR2RGB))
        plt.title(f'My Harris without NMS-Threshold:{(i + 1) * 0.05}')
        plt.subplot(4, 3, i * 3 + 2)
        plt.imshow(cv2.cvtColor(result_myHarrisWithNMS[i], cv2.COLOR_BGR2RGB))
        plt.title(f'My Harris with NMS-Threshold:{(i + 1) * 0.05}')
        plt.subplot(4, 3, i * 3 + 3)
        plt.imshow(cv2.cvtColor(result_cv2Harris[i], cv2.COLOR_BGR2RGB))
        plt.title(f'OpenCV Harris-Threshold:{(i + 1) * 0.05}')
    plt.tight_layout()
    plt.show()


def NMSshow(img, ksize, sigma, k, threshold, NMS=False):
    result = myHarris(img, ksize, sigma, k, threshold, True)
    plt.imshow(cv2.cvtColor(result, cv2.COLOR_BGR2RGB))
    plt.show()


if __name__ == '__main__':
    img = cv2.imread('../dataset/check_board.png')
    img = cv2.resize(img, dsize=(512, 512))
    # # 转换为灰度图像
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # dst = myHarris(gray, ksize=3, sigma=2, k=0.04, threshold=0.01, NMS=True)
    # print(dst.shape)  # (400, 600)
    # print(dst)
    #
    # img[dst == dst.max()] = [0, 0, 255]
    # cv2.imshow('', img)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    # doHarris_withDifferentKsize("../dataset/check_board.png")
    # doHarris_withDifferentThreshold("../dataset/check_board.png")
    NMSshow(gray, 3, 2, 0.05, 0.01, True)


