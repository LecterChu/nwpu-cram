import cv2


def load(image1_path='../data/image1.png', image2_path='../data/image2.png'):
    """
    读入两张图片
    :param image1_path: 图1的路径
    :param image2_path: 图2的路径
    :return: 经过pre process的两张图
    """
    image1 = cv2.imread(image1_path, cv2.COLOR_BGR2RGB)
    image2 = cv2.imread(image2_path, cv2.COLOR_BGR2RGB)

    rate = 600 / image1.shape[1]
    image1 = cv2.resize(image1, (int(rate * image1.shape[1]), int(rate * image1.shape[0])))
    image2 = cv2.resize(image2, (image1.shape[1], image1.shape[0]))

    top, bottom, left, right = 250, 250, 250, 250
    image1 = cv2.copyMakeBorder(image1, top, bottom, left, right, cv2.BORDER_CONSTANT, value=(0, 0, 0))
    image2 = cv2.copyMakeBorder(image2, top, bottom, left, right, cv2.BORDER_CONSTANT, value=(0, 0, 0))

    return image1, image2
