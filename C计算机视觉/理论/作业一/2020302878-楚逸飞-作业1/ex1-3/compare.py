import numpy as np
from scipy import io
import os
import cv2


def standard_canny_operation(img: np.ndarray, kernel_size: int = 5, sigma: float = 1.5, threshold_low: float = 15,
                             threshold_high: float = 20) -> np.ndarray:
    """
    使用cv2.canny计算
    :param img:
    :param kernel_size:
    :param sigma:
    :param threshold_low:
    :param threshold_high:
    :return:
    """
    standard_blur_img = cv2.GaussianBlur(src=img, ksize=(kernel_size, kernel_size), sigmaX=sigma, sigmaY=sigma)
    standard_canny_img = cv2.Canny(standard_blur_img, threshold1=threshold_low, threshold2=threshold_high)
    return standard_canny_img


def calculate_precision(root: str) -> float:
    origin_img_path = os.path.join(root, "images")
    ground_truth_result_path = os.path.join(root, "groundTruth")

    # log.txt中保存了精确度
    log = open('log.txt', mode='a', encoding='utf-8')

    for sub_dir_name in ['test']:
        # save_path = os.path.join(root, "compare", sub_dir_name)
        origin_img_sub_path = os.path.join(origin_img_path, sub_dir_name)
        ground_truth_result_sub_path = os.path.join(ground_truth_result_path, sub_dir_name)
        for index in range(len(os.listdir(ground_truth_result_sub_path))):
            filename_ground = os.listdir(ground_truth_result_sub_path)[index]
            data_ground = io.loadmat(os.path.join(ground_truth_result_sub_path, filename_ground))
            edge_data = data_ground['groundTruth'][0][0][0][0][1]
            edge_data_255 = edge_data * 255  # groundTruth 读取结果

            filename_origin = os.listdir(origin_img_sub_path)[index]
            img_origin = cv2.imread(os.path.join(origin_img_sub_path, filename_origin), cv2.IMREAD_GRAYSCALE)
            canny_img = standard_canny_operation(img=img_origin, kernel_size=5, sigma=1.5, threshold_low=75,
                                                 threshold_high=150)
            path = "./1-3_results/"
            new_img_name = filename_origin.split('.')[0] + '_img.png'
            cv2.imwrite(path + new_img_name, canny_img)
            new_edge_name = filename_ground.split('.')[0] + '_edge.png'
            cv2.imwrite(path + new_edge_name, edge_data_255)
            if edge_data_255.shape != canny_img.shape:
                print("ERROR SHAPE")
                break

            # 计算每张图片的精确度
            same_count = 0
            total_count = canny_img.shape[0] * canny_img.shape[1]
            for x in range(canny_img.shape[0]):
                for y in range(canny_img.shape[1]):
                    canny_value = canny_img[x][y]
                    ground_value = edge_data_255[x][y]
                    if canny_value == ground_value:
                        same_count = same_count + 1
            print(filename_origin.split('.')[0] + " accuracy: ", end="", file=log)
            print(same_count / total_count, file=log)


def bsds_trans(root, num):
    path = os.path.join(root, 'groundTruth')
    for sub_dir_name in ['train', 'test', 'val']:
        sub_path = os.path.join(path, sub_dir_name)
        save_path = os.path.join(root, f'save-data/GT_convert_{num}', sub_dir_name)
        os.makedirs(save_path, exist_ok=True)

        print(f"开始转换 {sub_dir_name} 文件夹中的内容")
        for index in range(len(os.listdir(sub_path))):
            filename = os.listdir(sub_path)[index]
            data = io.loadmat(os.path.join(sub_path, filename))
            try:
                if len(data['groundTruth'][0]) <= num:
                    raise IndexError
                edge_data = data['groundTruth'][0][num][0][0][1]
                edge_data_255 = edge_data * 255
                new_img_name = filename.split('.')[0] + '.png'
                cv2.imwrite(os.path.join(save_path, new_img_name), edge_data_255)

            except IndexError:
                index = min(len(os.listdir(sub_path)) - 1, index + 1)
                filename = os.listdir(sub_path)[index]


if __name__ == "__main__":
    current_path = os.path.abspath(__file__)
    # root 为BSD500的相对于此python文件的路径
    root_dir_path = os.path.dirname(os.path.dirname(current_path))
    database_path = os.path.join(root_dir_path, "dataset\\BSDS500\\data")
    print(database_path)
    print(calculate_precision(database_path))
