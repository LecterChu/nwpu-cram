import cv2
import numpy as np


def blend(src_img, warp_img):
    """
    图像融合
    :param src_img: 图1
    :param warp_img:  图2
    :return:  融合图像
    """

    rows, cols = src_img.shape[:2]
    result = np.zeros([rows, cols, 3], np.uint8)
    left = 0
    right = 0

    # 找到左右重叠区域
    for col in range(0, cols):
        if src_img[:, col].any() and warp_img[:, col].any():
            left = col
            break
    for col in range(cols - 1, 0, -1):
        if src_img[:, col].any() and warp_img[:, col].any():
            right = col
            break

    # 根据权重进行图像融合
    # 根据左右重叠区域进行融合会导致图片中有横向的拼接痕迹
    for row in range(0, rows):
        for col in range(0, cols):
            # src不存在
            if not src_img[row, col].any():
                result[row, col, :] = warp_img[row, col, :]
            # warp_img 不存在
            elif not warp_img[row, col].any():
                result[row, col, :] = src_img[row, col, :]
            # src 和warp都存在，就是交叉区域
            else:
                src_len = float(abs(col - left))
                test_len = float(abs(col - right))
                alpha_1 = src_len / (src_len + test_len)
                result[row, col, :] = src_img[row, col, :] * alpha_1 + warp_img[row, col, :] * (1 - alpha_1)
    return result
