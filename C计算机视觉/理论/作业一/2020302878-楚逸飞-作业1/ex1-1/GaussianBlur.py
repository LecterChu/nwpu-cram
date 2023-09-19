import cv2
from matplotlib import pyplot as plt


def Gaussian_Blur(image, title=None, sigma=0, display=False) -> None:
    images = [image]

    # 窗口大小kernel_size从3到29  每个sigma对应十五张图片（包括原图片在内）
    for k_size in range(3, 30, 2):
        img = cv2.GaussianBlur(image, (k_size, k_size), sigma)
        images.append(img)

    if title is not None:
        fig = plt.figure(title, figsize=(10, 6))
    else:
        fig = plt.figure("Gaussian_Blur", figsize=(10, 6))
    fig.subplots_adjust(left=0, right=1, bottom=0, top=0.95, hspace=0.25, wspace=0.1)

    for i in range(len(images)):
        if i == 0:
            result = fig.add_subplot(3, 5, i + 1, xticks=[], yticks=[], title="origin")
        else:
            result = fig.add_subplot(3, 5, i + 1, xticks=[], yticks=[], title="kSize=(%d,%d)" % (i * 2 + 1, i * 2 + 1))
        # 将BGR格式转换为RGB格式
        img = cv2.cvtColor(images[i], cv2.COLOR_BGR2RGB)
        result.imshow(img)
    plt.savefig("./1-1-1_results/%s.png" % title)

    if not display:
        return
    plt.show()


if __name__ == "__main__":
    # 加载图片
    gray_img = cv2.imread("../dataset/lena/lena512.bmp")
    color_img = cv2.imread("../dataset/lena/lena512color.tiff")

    # 尺度因子从1到11
    for sigma in range(1, 12):
        Gaussian_Blur(gray_img, "GaussianBlur_Gray(sigma=%d)" % sigma, sigma)
        Gaussian_Blur(color_img, "GaussianBlur_Color(sigma=%d)" % sigma, sigma)
