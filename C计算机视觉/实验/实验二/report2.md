# **CV实验二**

## **实验目的**

本章实验的主要目的是掌握图像分割任务难点，了解如何使用深度学习解决相关问题。掌握不同图像分割神经网络架构的设计原理与核心思想，熟悉使用MindSpore深度学习框架实现深度学习实验的一般流程。

## **实验内容**

#### **任务一：按照华为平台实验手册进行操作**

要求：熟悉实验环境，掌握Unet图像分割原理及程序流程

具体：记录并观察记录实验结果，如损失函数随迭代轮数变化等



#### **任务二：完成华为平台实验手册思考题**

要求：尝试自动动手编写代码实现

具体：理解原理，记录实验结果并分析



#### **任务三：Unet-5模型性能分析**

要求：调节实验参数，进行试验对比及分析

实验参数包括：训练数据比例，批次大小，迭代轮数，学习速率



#### **任务四：传统分割模型与Unet分割性能对比**

要求：比较OTSU方法和Unet方法的性能

具体：1.比较单张图片两算法的Dice coefficient差异

​			2.比较测试集两算法的Dice coefficient差异



## **实验过程**

#### 任务一：

原理介绍：

OTSU：

大津阈值法（OTSU）,又称作最大类间方差法，是一种图像二值化分割阈值的算法，由日本学者大津于1979年提出。大津阈值法是具有统计意义上的最佳分割阈值。其核心思想就是使类间方差最大，按照大津阈值法求得的阈值进行图像二值分割以区分前后背景，前景与背景图像的类间方差最大。该算法要求被分割的物体颜色纹理比较紧凑，类内方差小，对于一些文本图像的处理（比如车牌、指纹）效果很好。

Unet网络结构：

Unet是一种改进的全卷积网络（FCN）用于图像分割任务。由Olaf Ronneberger等人在论文《U-Net: Convolutional Networks for Biomedical Image Segmentation》中提出。U-Net的网络结构和论文可以参考其官网：https://lmb.informatik.uni-freiburg.de/people/ronneber/u-net/ ；U-Net得名于它的网络结构图，类似一个英文字母“U”。左半边是一个从上到下，一步一步从原始图像抽取特征（即原始图像本质信息）的过程；右半边是一个从下到上，一步一步从图像特征还原目标信息的过程。U-Net网络主要分为encoder和decoder两个部分。网络结构如下所示：

![image-20221224121929453](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224121929453.png)

①打印图像和标签的形状，展示第一张图像和标签：

![image-20221224095751242](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224095751242.png)

可以看到图像的heigth和weigth都是512，这张图像的label是30

②绘制一张训练集中的直方图：

![image-20221224100127658](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100127658.png)

发现该数据集的图像的直方图很连续，并没有出现明显的波谷，使用传统基于统计的阈值分割算法可能并不能取得好的效果。

③基于OTSU的图像二值化分割：

![image-20221224100306200](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100306200.png)

可以看到分割的结果并不算理想

④使用基于神经网络的图像分割算法。首先进行超参数配置和、各个模块搭建、定义损失函数等等

⑤数据项预处理

⑥模型训练：

![image-20221224100720817](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100720817.png)

​			......

​			......

![image-20221224100809022](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100809022.png)

训练了两个epoch，共1200个step。可以看到loss从最初的0.5 - 0.7降低到了最后的0.16 - 0.17，loss值降低明显

⑦评估模型性能（使用Dice coefficient）：

![image-20221224101112639](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224101112639.png)

⑧在验证集上计算Dice值：

![image-20221224101243356](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224101243356.png)



#### 任务二：

实验中的思考题：

1.请用OpenCV和matplotlib取出一张训练集中的图像，并绘制图像直方图。（初级）

![image-20221224095751242](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224095751242.png)

2.请用OpenCV和matplotlib取出一张训练集中的图像，并绘制图像直方图。（初级）

![image-20221224100127658](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100127658.png)

3.使用MindSpore搭建Unet类，用于构建网络。要求：网络结构和原论文保持一致。

```python
class DoubleConv(nn.Cell):

    def __init__(self, in_channels, out_channels, mid_channels=None):
        super().__init__()
        init_value_0 = TruncatedNormal(0.06)
        init_value_1 = TruncatedNormal(0.06)
        if not mid_channels:
            mid_channels = out_channels
        self.double_conv = nn.SequentialCell(
            [nn.Conv2d(in_channels, mid_channels, kernel_size=3, has_bias=True,
                       weight_init=init_value_0, pad_mode="valid"),
             nn.ReLU(),
             nn.Conv2d(mid_channels, out_channels, kernel_size=3, has_bias=True,
                       weight_init=init_value_1, pad_mode="valid"),
             nn.ReLU()]
        )

    def construct(self, x):
        return self.double_conv(x)


class Down(nn.Cell):
    """Downscaling with maxpool then double conv"""

    def __init__(self, in_channels, out_channels):
        super().__init__()

        self.maxpool_conv = nn.SequentialCell(
            [nn.MaxPool2d(kernel_size=2, stride=2),
             DoubleConv(in_channels, out_channels)]
        )

    def construct(self, x):
        return self.maxpool_conv(x)


class Up1(nn.Cell):
    """Upscaling then double conv"""

    def __init__(self, in_channels, out_channels, bilinear=True):
        super().__init__()
        self.concat = F.Concat(axis=1)
        self.factor = 56.0 / 64.0
        self.center_crop = CentralCrop(central_fraction=self.factor)
        self.print_fn = F.Print()
        self.conv = DoubleConv(in_channels, out_channels, in_channels // 2)
        self.up = nn.Conv2dTranspose(in_channels, in_channels // 2, kernel_size=2, stride=2)
        self.relu = nn.ReLU()

    def construct(self, x1, x2):
        x1 = self.up(x1)
        x1 = self.relu(x1)
        x2 = self.center_crop(x2)
        x = self.concat((x1, x2))
        return self.conv(x)


class Up2(nn.Cell):
    """Upscaling then double conv"""

    def __init__(self, in_channels, out_channels, bilinear=True):
        super().__init__()
        self.concat = F.Concat(axis=1)
        self.factor = 104.0 / 136.0
        self.center_crop = CentralCrop(central_fraction=self.factor)
        self.conv = DoubleConv(in_channels, out_channels, in_channels // 2)
        self.up = nn.Conv2dTranspose(in_channels, in_channels // 2, kernel_size=2, stride=2)
        self.relu = nn.ReLU()

    def construct(self, x1, x2):
        x1 = self.up(x1)
        x1 = self.relu(x1)
        x2 = self.center_crop(x2)
        x = self.concat((x1, x2))
        return self.conv(x)


class Up3(nn.Cell):
    """Upscaling then double conv"""

    def __init__(self, in_channels, out_channels, bilinear=True):
        super().__init__()
        self.concat = F.Concat(axis=1)
        self.factor = 200 / 280
        self.center_crop = CentralCrop(central_fraction=self.factor)
        self.print_fn = F.Print()
        self.conv = DoubleConv(in_channels, out_channels, in_channels // 2)
        self.up = nn.Conv2dTranspose(in_channels, in_channels // 2, kernel_size=2, stride=2)
        self.relu = nn.ReLU()

    def construct(self, x1, x2):
        x1 = self.up(x1)
        x1 = self.relu(x1)
        x2 = self.center_crop(x2)
        x = self.concat((x1, x2))
        return self.conv(x)


class Up4(nn.Cell):
    """Upscaling then double conv"""

    def __init__(self, in_channels, out_channels, bilinear=True):
        super().__init__()
        self.concat = F.Concat(axis=1)
        self.factor = 392 / 568
        self.center_crop = CentralCrop(central_fraction=self.factor)
        self.conv = DoubleConv(in_channels, out_channels, in_channels // 2)
        self.up = nn.Conv2dTranspose(in_channels, in_channels // 2, kernel_size=2, stride=2)
        self.relu = nn.ReLU()

    def construct(self, x1, x2):
        x1 = self.up(x1)
        x1 = self.relu(x1)
        x2 = self.center_crop(x2)
        x = self.concat((x1, x2))
        return self.conv(x)


class OutConv(nn.Cell):
    def __init__(self, in_channels, out_channels):
        super(OutConv, self).__init__()
        init_value = TruncatedNormal(0.06)
        self.conv = nn.Conv2d(in_channels, out_channels, kernel_size=1, has_bias=True, weight_init=init_value)

    def construct(self, x):
        x = self.conv(x)
        return x

```

```python
class UNet(nn.Cell):
    def __init__(self, n_channels, n_classes):
        super(UNet, self).__init__()
        self.n_channels = n_channels
        self.n_classes = n_classes
        self.inc = DoubleConv(n_channels, 64)
        self.down1 = Down(64, 128)
        self.down2 = Down(128, 256)
        self.down3 = Down(256, 512)
        self.down4 = Down(512, 1024)
        self.up1 = Up1(1024, 512)
        self.up2 = Up2(512, 256)
        self.up3 = Up3(256, 128)
        self.up4 = Up4(128, 64)
        self.outc = OutConv(64, n_classes)

    def construct(self, x):

        x1 = self.inc(x)
        x2 = self.down1(x1)
        x3 = self.down2(x2)
        x4 = self.down3(x3)
        x5 = self.down4(x4)
        x = self.up1(x5, x4)
        x = self.up2(x, x3)
        x = self.up3(x, x2)
        x = self.up4(x, x1)
        logits = self.outc(x)
        return logits

```

4.请重新构建一个类，将MindSpore的nn.SoftmaxCrossEntropyWithLogits损失函数用于Unet，计算输出特征图各个位置平均的损失值。

```python
class CrossEntropyWithLogits(_Loss):
    #重写损失函数。
    def __init__(self):
        super(CrossEntropyWithLogits, self).__init__()
        self.transpose_fn = F.Transpose()
        self.reshape_fn = F.Reshape()
        self.softmax_cross_entropy_loss = nn.SoftmaxCrossEntropyWithLogits()
        self.cast = F.Cast()

    def construct(self, logits, label):
        # NCHW->NHWC
        logits = self.transpose_fn(logits, (0, 2, 3, 1))
        logits = self.cast(logits, mindspore.float32)
        label = self.transpose_fn(label, (0, 2, 3, 1))

        loss = self.reduce_mean(self.softmax_cross_entropy_loss(self.reshape_fn(logits, (-1, 2)),
                                                                self.reshape_fn(label, (-1, 2))))
        return self.get_loss(loss)
```

![image-20221224100720817](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100720817.png)

​			......

​			......

![image-20221224100809022](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224100809022.png)

5.定义一个名为dice_coeff的类，用于计算每张验证集图像的Dice以及返回验证集中Dice的均值。

```python
class dice_coeff(nn.Metric):
    def __init__(self):
        super(dice_coeff, self).__init__()
        self.clear()

    def clear(self):
        self._dice_coeff_sum = 0
        self._samples_num = 0

    def update(self, *inputs):
        if len(inputs) != 2:
            raise ValueError('Mean dice coeffcient need 2 inputs (y_pred, y), but got {}'.format(len(inputs)))

        y_pred = self._convert_data(inputs[0])
        y = self._convert_data(inputs[1])
        self._samples_num += y.shape[0]
        y_pred = y_pred.transpose(0, 2, 3, 1)
        y = y.transpose(0, 2, 3, 1)
        y_pred = softmax(y_pred, axis=3)

        inter = np.dot(y_pred.flatten(), y.flatten())
        union = np.dot(y_pred.flatten(), y_pred.flatten()) + np.dot(y.flatten(), y.flatten())

        single_dice_coeff = 2 * float(inter) / float(union + 1e-6)
        print("single dice coeff is:", single_dice_coeff)
        self._dice_coeff_sum += single_dice_coeff

    def eval(self):
        if self._samples_num == 0:
            raise RuntimeError('Total samples num must not be 0.')
        return self._dice_coeff_sum / float(self._samples_num)
```

![image-20221224101112639](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224101112639.png)

6.请在test_net原函数基础上调用测试数据集进行预测，并可视化预测结果，注意：Unet的输入图像尺寸是大于输出图像的尺寸的，需要对原图进行预处理。

```python
def test_net(data_dir, ckpt_path, cross_valid_ind=1, cfg=None):
    net = UNet(n_channels=cfg['num_channels'], n_classes=cfg['num_classes'])
    param_dict = load_checkpoint(ckpt_path)
    load_param_into_net(net, param_dict)

    criterion = CrossEntropyWithLogits()
    _, valid_dataset = create_dataset(data_dir, 1, 1, False, cross_valid_ind, False)
    model = Model(net, loss_fn=criterion, metrics={"dice_coeff": dice_coeff()})

    print("============== Starting Evaluating ============")
    dice_score = model.eval(valid_dataset, dataset_sink_mode=False)
    print("Cross valid dice coeff is:", dice_score)
```

```python
def test_net(data_dir, ckpt_path, cross_valid_ind=1, cfg=None):
    net = UNet(n_channels=cfg['num_channels'], n_classes=cfg['num_classes'])
    param_dict = load_checkpoint(ckpt_path)
    load_param_into_net(net, param_dict)

    criterion = CrossEntropyWithLogits()
    _, valid_dataset = create_dataset(data_dir, 1, 1, False, cross_valid_ind, False)
    model = Model(net, loss_fn=criterion, metrics={"dice_coeff": dice_coeff()})

    print("============== Starting Evaluating ============")
    dice_score = model.eval(valid_dataset, dataset_sink_mode=False)
    print("Cross valid dice coeff is:", dice_score)
    testimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/test-volume.tif"))])
    testdata=testimage[10]
    image = Image.fromarray(testdata)
    image = image.resize((388, 388))
    testdata = np.asarray(image)
    testdata = np.pad(testdata, ((92, 92),(92, 92) ),  'symmetric')
    testdata = testdata/127.5-1
    testdata = testdata.astype(np.float32)
    testdata = testdata.reshape(1,1,572,572)
    output = model.predict(Tensor(testdata))
    pred = np.argmax(output.asnumpy(), axis=1)
    pred = pred.reshape(388, 388)
    plt.figure(figsize=(10,10))
    plt.subplot(2,2,1)
    plt.imshow(testimage[10],cmap='gray')
    plt.subplot(2,2,2)
    plt.imshow(pred,cmap='gray')
    plt.show()


ckpt_path = './ckpt_2/ckpt_unet_medical_adam-2_600.ckpt'
test_net(data_dir=data_url, ckpt_path=ckpt_path, cross_valid_ind=cfg_unet['cross_valid_ind'],
         cfg=cfg_unet)
```

![image-20221224101243356](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224101243356.png)

#### 任务三：

由于时间限制和速度限制，无法每个参数都设置很多组进行对比，只设置了几个有限的组进行对照实验。

**1.批次大小：**

batch_size从16改为32

![image-20221224110045199](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224110045199.png)

可以看到dataset length从600变为了300，因为batch size从16改为32相当于变为了两倍。同时也能够明显感觉到每一个step耗费的时间变长了。

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224111258131.png" alt="image-20221224111258131" style="zoom:50%;" />

​												......

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224111330869.png" alt="image-20221224111330869" style="zoom:50%;" />

可以看到batch size设为32以后效果不如16好 loss一般都在0.185以上，相比于batch size为16时增加了差不多百分之十

Dice值表现：

![image-20221224111716664](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224111716664.png)



**2.迭代轮数：**

epochs从400改为600

![image-20221224110842501](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224110842501.png)

可以看到dataset length从600变为了900.

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224112440036.png" alt="image-20221224112440036" style="zoom:50%;" />

​												......

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224112534914.png" alt="image-20221224112534914" style="zoom:50%;" />

可以看到epoch改为600后，loss有了一定的下降，训练到最后大部分的loss都能在0.17以下，小部分在0.17以上，还有一部分达到了0.15甚至0.14，说明epoch为600的时候效果明显更好

Dice值表现：

![image-20221224112559539](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224112559539.png)

**3.学习速率：**

lr从0.0001改为0.0005

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224105130088.png" alt="image-20221224105130088" style="zoom:50%;" />

​											......

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224105153306.png" alt="image-20221224105153306" style="zoom:50%;" />

对比lr=0.0005和lr=0.0001来看，差别并不大

Dice值表现：

![image-20221224105213471](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224105213471.png)

与lr=0.0001的时候差别并不大

#### 任务四：

**1.比较单张图片两算法的Dice coefficient差异：**

用测试集中的第15张图像

①OTSU：

![image-20221224120459313](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224120459313.png)

②Unet（epoch=600时）：

![image-20221224120451951](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224120451951.png)

```python
def test_net(data_dir, ckpt_path, cross_valid_ind=1, cfg=None):
    net = UNet(n_channels=cfg['num_channels'], n_classes=cfg['num_classes'])
    param_dict = load_checkpoint(ckpt_path)
    load_param_into_net(net, param_dict)

    criterion = CrossEntropyWithLogits()
    _, valid_dataset = create_dataset(data_dir, 1, 1, False, cross_valid_ind, False)
    model = Model(net, loss_fn=criterion, metrics={"dice_coeff": dice_coeff()})

    print("============== Starting Evaluating ============")
    dice_score = model.eval(valid_dataset, dataset_sink_mode=False)
    print("Cross valid dice coeff is:", dice_score)
    testimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/test-volume.tif"))])
    testdata=testimage[15]
    image = Image.fromarray(testdata)
    image = image.resize((388, 388))
    testdata = np.asarray(image)
    testdata = np.pad(testdata, ((92, 92),(92, 92) ),  'symmetric')
    testdata = testdata/127.5-1
    testdata = testdata.astype(np.float32)
    testdata = testdata.reshape(1,1,572,572)
    output = model.predict(Tensor(testdata))
    pred = np.argmax(output.asnumpy(), axis=1)
    pred = pred.reshape(388, 388)
    plt.figure(figsize=(10,10))
    plt.subplot(2,2,1)
    plt.imshow(testimage[15],cmap='gray')
    plt.subplot(2,2,2)
    plt.imshow(pred,cmap='gray')
    plt.show()

    
def OTSU_coeffi(ckpt_path, cross_valid_ind=1, cfg=None):
    trainimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/test-volume.tif"))])
    traindata=trainimage[15] #直接从label拿
    image = Image.fromarray(traindata)
    image = image.resize((388, 388))
    traindata = np.asarray(image)
    traindata = np.pad(traindata, ((92, 92),(92, 92) ), 'symmetric')
    traindata = traindata / 127.5 - 1
    traindata = traindata.astype(np.float32)
    traindata = traindata.reshape(1,1,572,572)
    testimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/test-volume.tif"))])
    ret1, th1 = cv2.threshold(src=testimage[15], thresh=0, maxval=255, type=cv2.THRESH_OTSU)
    testdata=th1 #传统方法得到的 数据预处理 
    print(testdata)
    image = Image.fromarray(testdata)
    image = image.resize((388, 388))
    testdata = np.asarray(image)
    testdata = np.pad(testdata, ((92, 92),(92, 92) ), 'symmetric')
    testdata = testdata / 127.5 - 1
    testdata = testdata.astype(np.float32)
    testdata = testdata.reshape(1,1,572,572) 
    ret1, th1 = cv2.threshold(src=testimage[15], thresh=0, maxval=255, type=cv2.THRESH_OTSU)
    dice=dice_coeff()
    dice.update(testdata,traindata) # 把两个数据送进去 
    # print(ret1) 
    plt.figure(figsize=(10,10)) 
    plt.subplot(2,2,1) 
    plt.imshow(trainimage[15],cmap='gray')
    plt.subplot(2,2,2)
    plt.imshow(th1,cmap='gray')
    plt.show()

    
ckpt_path = './ckpt_2/ckpt_unet_medical_adam-2_900.ckpt'
test_net(data_dir=data_url, ckpt_path=ckpt_path, cross_valid_ind=cfg_unet['cross_valid_ind'],
         cfg=cfg_unet)

OTSU_coeffi(ckpt_path=ckpt_path, cross_valid_ind=cfg_unet['cross_valid_ind'], cfg=cfg_unet)
```



**2.比较测试集两算法的Dice coefficient差异：**

①OTSU:

<img src="E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224114121864.png" alt="image-20221224114121864" style="zoom: 50%;" />

```python
 def OTSU_coeffi_onValied(data_dir, ckpt_path, cross_valid_ind=1, cfg=None):
    for i in range(30):
        trainimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/train-labels.tif"))])
        traindata=trainimage[i]
        image = Image.fromarray(traindata)
        image = image.resize((388, 388))
        traindata = np.asarray(image)
        traindata = np.pad(traindata, ((92, 92),(92, 92) ), 'symmetric')
        traindata = traindata / 127.5 - 1
        traindata = traindata.astype(np.float32)
        traindata = traindata.reshape(1,1,572,572)
        testimage=np.array([np.array(p) for p in ImageSequence.Iterator(Image.open("./data/train-volume.tif"))])
        ret1, th1 = cv2.threshold(src=testimage[i], thresh=0, maxval=255, type=cv2.THRESH_OTSU)
        testdata=th1 
        # print(testdata)
        image = Image.fromarray(testdata)
        image = image.resize((388, 388))
        testdata = np.asarray(image)
        testdata = np.pad(testdata, ((92, 92),(92, 92) ), 'symmetric')
        testdata = testdata / 127.5 - 1
        testdata = testdata.astype(np.float32)
        testdata = testdata.reshape(1,1,572,572) 
        ret1, th1 = cv2.threshold(src=testimage[i], thresh=0, maxval=255, type=cv2.THRESH_OTSU)
        dice=dice_coeff()
        dice.update(testdata,traindata)

OTSU_coeffi_onValied(data_dir=data_url, ckpt_path=ckpt_path, cross_valid_ind=cfg_unet['cross_valid_ind'], cfg=cfg_unet)
```

②Unet（epoch=600时）：

![image-20221224120640780](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224120640780.png)

```python
def test_net(data_dir, ckpt_path, cross_valid_ind=1, cfg=None):
    net = UNet(n_channels=cfg['num_channels'], n_classes=cfg['num_classes'])
    param_dict = load_checkpoint(ckpt_path)
    load_param_into_net(net, param_dict)

    criterion = CrossEntropyWithLogits()
    _, valid_dataset = create_dataset(data_dir, 1, 1, False, cross_valid_ind, False)
    model = Model(net, loss_fn=criterion, metrics={"dice_coeff": dice_coeff()})

    print("============== Starting Evaluating ============")
    dice_score = model.eval(valid_dataset, dataset_sink_mode=False)
    print("Cross valid dice coeff is:", dice_score)

```

可以看到OTSU单张图像的dice值较低，基本不会超过0.65，大部分在0.5 - 0.6， 而Unet的dice值较高，均在0.9以上



## **实验结果及分析**

实验中分别使用了OTSU和Unet两种算法对医学图像进行了分割，前者是传统算法，后者是机器学习、深度学习兴起后出现的新算法。

实验中使用Dice这一指标进行评估，这是一种集合相似度度量函数，通常用于计算两个样本的相似度。

![image-20221224121253504](E:\homework\大三上作业\计算机视觉\实验\实验二\assets\image-20221224121253504.png)

从实验结果来看，Unet的Dice值明显高于OTSU。前者在各种条件下的Dice值基本可以为稳定在0.9以上，而后者的值较低，基本在0.5 - 0.6之间，少数可以超过0.6 说明Unet的效果明显好于OTSU。但是Unet需要一定的训练，当epoch增加的时候，其训练所需时间明显增加，训练性能明显降低；当只更改batch size或者learning rate的时候对训练时间影响很小，但是从最终结果来看，batch size值为16时表现比32时更好；learning rate为0.0001和0.0005时相差不大。





