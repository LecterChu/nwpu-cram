import cv2
import time
from utils.blend import blend
from utils.image_loader import load
from utils.sift_match import sift_match
from utils.sift_match import get_good_matches


if __name__ == "__main__":
    image1_path = "./data/1.png"
    image2_path = "./data/2.png"

    # 加载图片
    src_img, warp_img = load(image1_path, image2_path)

    # sift特征点计算与匹配
    start = time.time()
    kp1, kp2, matches = sift_match(src_img, warp_img)
    end = time.time()
    print('特征点计算以及匹配的时间：', end - start)

    # 去除误匹配点、计算变换矩阵并进行拼接
    start = time.time()
    img1, img2, img3, dst, M = get_good_matches(src_img, warp_img, kp1, kp2, matches)
    end = time.time()
    print('去除误匹配点、计算变换矩阵并进行拼接的时间：', end - start)
    # 图像融合
    start = time.time()
    res = blend(img1, img2)
    end = time.time()
    print('图像融合时间：', end - start)

    # print
    print("变换矩阵", M)
    cv2.imshow("splicing", dst)
    cv2.imshow("sift_match", img3)
    cv2.imshow("blend_result", res)
    while True:
        if cv2.waitKey(0) == 27:
            break

