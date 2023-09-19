import cv2
import numpy as np
from matplotlib import pyplot as plt


def Gaussian_Laplace(image: np.ndarray, is_gray: bool, title=None, sigma= 0, display=True) -> None:

    images = [image]

    #  Gaussian Blur
    for k_size in range(3, 30, 2):
        img = cv2.GaussianBlur(image, (k_size, k_size), sigma)
        if is_gray:
            laplace_img = cv2.Laplacian(img, cv2.CV_32F, ksize=k_size)
        else:
            laplace_img = cv2.Laplacian(img, cv2.CV_32F, ksize=k_size)
        # result = cv2.convertScaleAbs(laplace_img)
        images.append(laplace_img)

    if title is not None:
        fig = plt.figure(title, figsize=(10, 6))
    else:
        fig = plt.figure("GaussianLaplace", figsize=(10, 6))
    fig.subplots_adjust(left=0, right=1, bottom=0, top=0.95, hspace=0.25, wspace=0.1)

    for i in range(len(images)):
        if i == 0:
            result = fig.add_subplot(3, 5, i + 1, xticks=[], yticks=[], title="origin")
        else:
            result = fig.add_subplot(3, 5, i + 1, xticks=[], yticks=[], title="kSize=(%d,%d)" % (i * 2 + 1, i * 2 + 1))
        img = cv2.cvtColor(images[i], cv2.COLOR_BGR2RGB)
        result.imshow(img)
    plt.savefig("./1-1-2_results/%s.png" % title)

    if not display:
        return
    plt.show()


if __name__ == "__main__":
    # read images
    gray_img = cv2.imread("../dataset/lena/lena512.bmp")
    color_img = cv2.imread("../dataset/lena/lena512color.tiff")

    for sigma in range(1, 12):
        Gaussian_Laplace(gray_img, True, "GaussianLaplace_Gray(sigma=%d)" % sigma, sigma)
        Gaussian_Laplace(color_img, False, "GaussianLaplace_Color(sigma=%d)" % sigma, sigma)

    # plt.subplot(1, 2, 1)
    # plt.imshow(result_gray)
    # plt.axis("off")
    # plt.title('Gray')
    #
    # plt.subplot(1, 2, 2)
    # plt.imshow(result_color)
    # plt.axis("off")
    # plt.title('Color')
    #
    # plt.show()

    # save the result
    # cv2.imwrite("./1-1-2_results/GL_gray.png", result_gray)
    # cv2.imwrite("./1-1-2_results/GL_color.png", result_color)
