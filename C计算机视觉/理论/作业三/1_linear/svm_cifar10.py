import numpy as np
from utils import load_CIFAR10
from svm import SVM
import matplotlib.pyplot as plt


def VisualizeImage(X_train, y_train):
    """可视化数据集

    :param X_train: 训练集
    :param y_train: 训练标签
    :return:
    """
    plt.rcParams['figure.figsize'] = (10.0, 8.0)  # set default size of plots
    plt.rcParams['image.interpolation'] = 'nearest'
    plt.rcParams['image.cmap'] = 'gray'
    classes = ['plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
    num_classes = len(classes)
    samples_per_class = 8
    for y, cls in enumerate(classes):
        # 得到该标签训练样本下标索引
        idxs = np.flatnonzero(y_train == y)
        # 从某一分类的下标中随机选择8个图像（replace设为False确保不会选择到同一个图像）
        idxs = np.random.choice(idxs, samples_per_class, replace=False)
        # 将每个分类的8个图像显示出来
        for i, idx in enumerate(idxs):
            plt_idx = i * num_classes + y + 1
            # 创建子图像
            plt.subplot(samples_per_class, num_classes, plt_idx)
            plt.imshow(X_train[idx].astype('uint8'))
            plt.axis('off')
            # 增加标题
            if i == 0:
                plt.title(cls)
    plt.show()


def VisualizeLoss(loss_history):
    plt.plot(loss_history)
    plt.xlabel('Iteration number')
    plt.ylabel('Loss value')
    plt.show()


def pre_dataset():
    cifar10_dir = 'datasets/'
    X_train, y_train, X_test, y_test = load_CIFAR10(cifar10_dir)
    VisualizeImage(X_train, y_train)
    input('Enter any key to Cross-validation...')

    num_train = 49000
    num_val = 1000
    # dataset Validation
    sample_index = range(num_train, num_train + num_val)
    X_val = X_train[sample_index]
    y_val = y_train[sample_index]
    X_train = X_train[:num_train]
    y_train = y_train[:num_train]

    # subtract the mean image
    X_train = np.reshape(X_train, (X_train.shape[0], -1))
    X_test = np.reshape(X_test, (X_test.shape[0], -1))
    X_val = np.reshape(X_val, (X_val.shape[0], -1))

    mean_image = np.mean(X_train, axis=0)
    X_train = X_train - mean_image
    X_test = X_test - mean_image
    X_val = X_val - mean_image

    # add a parameter for W
    X_train = np.hstack([X_train, np.ones((X_train.shape[0], 1))])
    X_test = np.hstack([X_test, np.ones((X_test.shape[0], 1))])
    X_val = np.hstack([X_val, np.ones((X_val.shape[0], 1))])

    return X_train, y_train, X_test, y_test, X_val, y_val


def auto_get_parameter(X_train, y_train, X_val, y_val):
    learning_rates = [1e-7, 5e-5]
    regularization_strengths = [5e4, 1e5]

    best_parameter = None
    best_val = -1

    for i in learning_rates:
        for j in regularization_strengths:
            svm = SVM()
            # X, y, reg, delta, learning_rate, batch_num, num_iter, debug
            svm.train(X_train, y_train, j, 1, i, 200, 1500, True)
            y_pred = svm.predict(X_val)
            acc_val = np.mean(y_val == y_pred)
            if best_val < acc_val:
                best_val = acc_val
                best_parameter = (i, j)

    print('OK! Have been identified parameter! Best validation accuracy achieved during cross-validation: %f' % best_val)
    return best_parameter


def get_svm_model(parameter, X, y):
    svm = SVM()
    loss_history = svm.train(X, y, parameter[1], 1, parameter[0], 200, 1500, True)
    VisualizeLoss(loss_history)
    input('Enter any key to predict...')
    return svm


if __name__ == '__main__':
    # 对数据进行预处理，得到训练集，测试集，验证集
    X_train, y_train, X_test, y_test, X_val, y_val = pre_dataset()
    # 通过验证集自动化确定参数 learning_rate和reg
    best_parameter = auto_get_parameter(X_train, y_train, X_val, y_val)
    # 通过参数和训练集构建SVM模型
    svm = get_svm_model(best_parameter, X_train, y_train)
    # 用测试集预测准确率
    y_pred = svm.predict(X_test)

    y_train_pred = svm.predict(X_train)
    print('Total training accuracy: %f' % (np.mean(y_train == y_train_pred),))
    y_val_pred = svm.predict(X_val)
    print('Total validation accuracy: %f' % (np.mean(y_val == y_val_pred),))
    classes = ('plane', 'car', 'bird', 'cat','deer', 'dog', 'frog', 'horse', 'ship', 'truck')
    correct_pred = {classname: 0 for classname in classes}
    total_class = {classname: 0 for classname in classes}
    total_pred = {classname: 0 for classname in classes}

    for label, prediction in zip(y_val, y_val_pred):
        if label == prediction:
            correct_pred[classes[label]] += 1
        total_class[classes[label]] += 1
        total_pred[classes[prediction]] += 1

    precision = []
    recall = []

    for classname, correct_count in correct_pred.items():
        print(f'Class: {classname:5s}')
        accuracy = 100 * float(correct_count) / total_class[classname]
        precision.append(accuracy)
        print(f' Precision for class: {classname:5s} is {accuracy:.1f} %')
        accuracy = 100 * float(correct_count) / total_pred[classname]
        recall.append(accuracy)
        print(f' Recall for class: {classname:5s} is {accuracy:.1f} %')

    plt.stem(classes, precision, linefmt='-.', markerfmt='o', basefmt='-')
    plt.xlabel('Classes')
    plt.ylabel('Precision')
    plt.show()
    plt.stem(classes, recall, linefmt='-.', markerfmt='o', basefmt='-')
    plt.xlabel('Classes')
    plt.ylabel('Recall')
    plt.show()

    print('Accuracy achieved during cross-validation: %f' % (np.mean(y_pred == y_test)))