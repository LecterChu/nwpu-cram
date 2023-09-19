import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
import torch.nn.functional as F
import torch.optim as optim


class cifar_net_2layer(nn.Module):
    def __init__(self):
        super().__init__()  # 线性全连接函数
        self.fc1 = nn.Linear(32*32*3, 100)
        self.fc2 = nn.Linear(100, 100)
        self.fc3 = nn.Linear(100, 10)

    def forward(self, x):
        x = torch.flatten(x, 1)  # flatten all dimensions except batch
        x = F.relu(self.fc1(x))
        x = F.softmax(self.fc2(x))
        x = self.fc3(x)
        return x


class cifar_net(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        # 构建卷积函数
        self.conv1 = nn.Conv2d(3, 96, 5)
        # 池化层
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(96, 256, 5)
        # 线性全连接函数
        self.fc1 = nn.Linear(256 * 5 * 5, 1024)
        self.fc2 = nn.Linear(1024, 96)
        self.fc3 = nn.Linear(96, 10)

    def forward(self, x):
        # 输入x经过卷积conv1之后，经过激活函数ReLU，使用2x2的窗口进行最大池化Max pooling，然后更 新到x。
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))  # 至此经历了交替两次卷积和池化
        x = torch.flatten(x, 1)  # flatten all dimensions except batch
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x


def train():
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    print('using device:', device)
    # Load
    # 将通道范围从0-255变换到0-1之间，然后Normalize
    transform = transforms.Compose(
        [transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
    batch_size = 4
    train_set = torchvision.datasets.CIFAR10(
        root='./', train=True, download=False, transform=transform)
    train_loader = torch.utils.data.DataLoader(
        train_set, batch_size=batch_size, shuffle=True, num_workers=2)

    # classes = ('plane', 'car', 'bird', 'cat', 'deer',
    #            'dog', 'frog', 'horse', 'ship', 'truck')

    # CreateNet
    net = cifar_net()
    net.to(device=device)

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(net.parameters(), lr=0.005, momentum=0.9)
    StepLR = torch.optim.lr_scheduler.StepLR(
        optimizer, step_size=12000, gamma=0.85)

    lr_list = []
    loss_list = []

    for epoch in range(20):  # loop over the dataset multiple times
        running_loss = 0.0

        print("learning_rate of %d epoch: %f" % (epoch + 1, optimizer.param_groups[0]['lr']), file=open('info.txt', 'a'))
        lr_list.append(optimizer.param_groups[0]['lr'])
        # get the inputs; data is a list of [inputs, labels]
        for i, data in enumerate(train_loader, 0):
            inputs, labels = data[0].to(device), data[1].to(device)

            optimizer.zero_grad()
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            StepLR.step()

            running_loss += loss.item()
            if i % 2000 == 1999:  # print every 2000 mini-batches
                print(f'[{epoch + 1}, {i + 1:5d}] loss: {running_loss / 2000:.4f}', file=open('info.txt', 'a'))
                loss_list.append(running_loss / 2000)
                running_loss = 0.0

    plt.plot(lr_list)
    plt.savefig('./lr_list.jpg')
    plt.show()
    plt.plot(range(0, len(loss_list)*2000, 2000), loss_list)
    plt.savefig('./loss_list.jpg')
    plt.show()
    print('Finished Training')
    torch.save(net.state_dict(), './dnn_cifar10_net1.pth')


def test():
    transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

    batch_size = 4

    testset = torchvision.datasets.CIFAR10(root='./', train=False,
                                           download=False, transform=transform)
    testloader = torch.utils.data.DataLoader(testset, batch_size=batch_size,
                                             shuffle=False, num_workers=2)
    classes = ('plane', 'car', 'bird', 'cat',
               'deer', 'dog', 'frog', 'horse', 'ship', 'truck')
    net = cifar_net()
    net.load_state_dict(torch.load('./dnn_cifar10_net1.pth'))

    # prepare to count predictions for each class
    correct_pred = {classname: 0 for classname in classes}
    total_class = {classname: 0 for classname in classes}
    total_pred = {classname: 0 for classname in classes}

    # again no gradients needed
    with torch.no_grad():
        for data in testloader:
            images, labels = data
            outputs = net(images)
            _, predictions = torch.max(outputs, 1)
            # collect the correct predictions for each class
            for label, prediction in zip(labels, predictions):
                if label == prediction:
                    correct_pred[classes[label]] += 1
                total_class[classes[label]] += 1
                total_pred[classes[prediction]] += 1

    
    precision = []
    recall = []

    # print accuracy for each class
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



if __name__ == "__main__":
    train()
    test()
