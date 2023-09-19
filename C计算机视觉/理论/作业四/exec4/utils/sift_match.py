import cv2
import numpy as np


def sift_match(image1, image2):
    """
    匹配特征点
    :param image1: 图1
    :param image2: 图2
    :return: 特征点组
    """
    sift = cv2.SIFT_create()
    kp1, des1 = sift.detectAndCompute(image1, None)
    kp2, des2 = sift.detectAndCompute(image2, None)

    FLANN_INDEX_KDTREE = 1
    index = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    search = dict(checks=50)
    flann = cv2.FlannBasedMatcher(index, search)
    matches_kp = flann.knnMatch(des1, des2, k=2)

    return kp1, kp2, matches_kp


def get_good_matches(image1, image2, kp1, kp2, matches):
    """
    计算变换矩阵并拼接图像
    :param image1:图1
    :param image2:图2
    :param kp1:图1关键点
    :param kp2:图2关键点
    :param matches: 匹配结果
    :return:图1 配准的图2 匹配结果 拼接图 变换矩阵
    """

    matches_mask = [[0, 0] for _ in range(len(matches))]
    good = []
    for i, (m, n) in enumerate(matches):
        if m.distance < 0.5 * n.distance:
            good.append(m)
            matches_mask[i] = [1, 0]
    draw_params = dict(matchColor=(30, 144, 255),
                       singlePointColor=(255, 97, 0),
                       matchesMask=matches_mask,
                       flags=0)
    image3 = cv2.drawMatchesKnn(image1, kp1, image2, kp2, matches, None, **draw_params)

    MIN_MATCH_COUNT = 10
    if len(good) < MIN_MATCH_COUNT:
        print("Not enough matches are found - {}{}".format(len(good), MIN_MATCH_COUNT))
        return None

    src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
    dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
    M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
    image2 = cv2.warpPerspective(image2, np.array(M), (image2.shape[1], image2.shape[0]), flags=cv2.WARP_INVERSE_MAP)

    dst = image1.copy()
    for i in range(image2.shape[0]):
        for j in range(image2.shape[1]):
            pix = image2[i, j]
            if pix.any():
                dst[i, j] = pix

    return image1, image2, image3, dst, M
