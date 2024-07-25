import math
from typing import List, Callable
import random
import matplotlib.pyplot as plt
import copy
class Layer:
    def __init__(self, input_dim:int, output_dim:int,f:Callable[[float],float],d_f:Callable[[float],float]) -> None:
        self.weights = [[random.randint(1,100)/100 for _ in range(input_dim)] for _ in range(output_dim)]
        # 不需要偏置
        self.f = f
        self.d_f = d_f
        self.input_dim = input_dim
        self.output_dim = output_dim
    def compute(self, inputs:list[float]) -> list[float]:
        #assert len(inputs) == self.input_dim
        return [self.f(sum([inputs[i]*self.weights[j][i] for i in range(self.input_dim)])) for j in range(self.output_dim)]
    def diff(self, inputs:list[float]) -> list[list[list[float]]]:
        # 计算对权重的偏导
        # assert len(inputs) == self.input_dim
        result = []
        for j in range(self.output_dim):
            sum_A = sum([inputs[i]*self.weights[j][i] for i in range(self.input_dim)])
            diff_ = self.d_f(sum_A)
            tmp = []
            for k in range(self.output_dim):
                tmp.append([inputs[i] * diff_ if j == k else 0.0 for i in range(self.input_dim)])
            result.append(tmp)
        return result
    def diff_chain(self, inputs:list[float], diff:list[list[list[float]]]) -> list[list[list[float]]]:
        # 计算对权重的偏导
        # 返回值是一个三维数组，第一维是对第n个output的偏导，第二、三维表示权重位置
        result = []
        for k in range(self.output_dim):
            sum_A = sum([inputs[i]*self.weights[k][i] for i in range(self.input_dim)])
            diff_ = self.d_f(sum_A)

            tmp = []
            for a in range(len(diff[0])):
                tmp2 = []
                for b in range(len(diff[0][0])):
                    sum_B = diff_ * sum([diff[i][a][b]*self.weights[k][i] for i in range(self.input_dim)])
                    tmp2.append(sum_B)
                tmp.append(tmp2)
            result.append(tmp)
        return result

    def update(self, diff:list[list[float]], lr:float) -> None:
        for j in range(self.output_dim):
            for i in range(self.input_dim):
                self.weights[j][i] -= lr * diff[j][i] * (abs(self.weights[j][i])+1)
    def apply_noise(self, noise:float) -> None:
        for j in range(self.output_dim):
            for i in range(self.input_dim):
                self.weights[j][i] += random.randint(-1000,1000)/1000.0 * noise
    def apply_noise_N(self, noise:float, num:int) -> None:
        counter = 0
        samples = random.sample(range(self.input_dim*self.output_dim), num)
        samples.sort()
        for j in range(self.output_dim):
            for i in range(self.input_dim):
                if counter < num and i*self.output_dim + j == samples[counter]:
                    self.weights[j][i] += random.randint(-1000,1000)/1000.0 * noise
                    counter += 1
    def normalize_diff(self, diff:list[list[float]]) -> None:
        # 将diff归一化
        tmp_diff = copy.deepcopy(diff)
        max_ = max([max([abs(diff[j][i]) for i in range(self.input_dim)]) for j in range(self.output_dim)]) + 1e-6
        for j in range(self.output_dim):
            for i in range(self.input_dim):
                tmp_diff[j][i] /= max_
        return tmp_diff
class Net:
    def __init__(self, layers:list[Layer],power=2) -> None:
        self.layers = layers.copy()
        self.power = power
        # 0是输入层

    def predict(self, inputs:list[float]) -> list[float]:
        tmp = inputs.copy()
        for layer in self.layers:
            tmp = layer.compute(tmp)
        return tmp
    def diff_layer_K(self, inputs:list[float], K:int) -> list[list[float]]:
        assert K < len(self.layers)
        tmp = inputs.copy()
        # 计算第K层的对权重的偏导
        for i in range(K):
            tmp = self.layers[i].compute(tmp)
        curr = self.layers[K].diff(tmp)
        # 从K开始向前传播
        tmp = self.layers[K].compute(tmp)
        
        n = len(self.layers)
        for i in range(K+1, n):
            curr = self.layers[i].diff_chain(tmp, curr)
            tmp = self.layers[i].compute(tmp)            
            
        return curr
    def loss(self, inputs:list[float], targets:list[float]) -> float:
        #print(f'inputs: {inputs}')
        #print(f'targets: {targets}')
        #print(f'predict: {[self.predict(inputs[i]) for i in range(len(inputs))]}')

        return math.sqrt(sum([sum([((self.predict(inputs[i])[j] - targets[i][j]))**2 for j in range(len(targets[0]))]) for i in range(len(inputs))]))
    def diff_loss(self, inputs:list[float], targets:list[float], layer:int) -> list[list[float]]:
        # 计算对每一层的偏导
        assert layer < len(self.layers)
        diff = self.diff_layer_K(inputs, layer)
        # 计算对loss的偏导
        result = []
        for i in range(len(diff[0])):
            tmp = []
            for j in range(len(diff[0][i])):
                tmp2 = 0.0
                for k in range(len(targets)):
                    delta= self.predict(inputs)[k] - targets[k]
                    tmp2 += 2 * delta * diff[k][i][j] 
                tmp.append(tmp2)
            result.append(tmp)
        return result
        
    def train(self, inputs:List[List[float]], targets:List[List[float]], lr:float, epoch:int, lambda_reg:float) -> None:
        last_loss = self.loss(inputs, targets)
        for k in range(epoch):
            for i in range(len(inputs)):
                # 计算对每一层的偏导
                diff = [self.diff_loss(inputs[i], targets[i], j) for j in range(len(self.layers))]
                # 更新权重
                tmp_net = Net(self.layers)
                loss = tmp_net.loss(inputs, targets)
                
                for j in range(len(tmp_net.layers)):
                    for a in range(len(diff[j])):
                        for b in range(len(diff[j][0])):
                            diff[j][a][b] /= 2 * loss
                    # 应用L2正则化
                    reg_term = [[lambda_reg * weight for weight in layer] for layer in tmp_net.layers[j].weights]
                    tmp_net.layers[j].update((diff[j]), lr * math.exp(-0.*loss))
                    #tmp_net.layers[j].apply_noise_N(0.1*math.exp(-10*math.sqrt(k/epoch))*float(k<epoch/2), 1)
                    # 更新权重时考虑正则化项
                    #for a in range(len(tmp_net.layers[j].weights)):
                    #    for b in range(len(tmp_net.layers[j].weights[0])):
                    #        tmp_net.layers[j].weights[a][b] -= lr * reg_term[a][b]
                loss = tmp_net.loss(inputs, targets)
                if loss < last_loss:
                    last_loss = loss
                    self.layers = tmp_net.layers
                else:
                    lr *= 0.9975
            print(f'[epoch: {k}] loss: {last_loss}')

def ReLU(x:float) -> float:
    return max(0, x)
def d_ReLU(x:float) -> float:
    return 1 if x > 0 else 0

def sigmoid(x:float) -> float:
    return 1/(1+math.exp(-x))
def d_sigmoid(x:float) -> float:
    return sigmoid(x) * (1-sigmoid(x))

# 可以拟合负值的激活函数
def atan(x:float) -> float:
    return math.atan(x)*3
def d_atan(x:float) -> float:
    return 1/(1+x*x)*3

def xExp(x:float) -> float:
    return 3*x * math.exp(-x*x)
def d_xExp(x:float) -> float:
    return 3*(math.exp(-x*x) - 2*x*x*math.exp(-x*x))

if __name__ == '__main__':
    """def target(x:float) -> float:
        return x+math.sin(x*5)*0.25
    # 训练一个能在[0,1]之间计算x^2的网络
    train_data_N = 20
    inputs = [[i/train_data_N, 0.1] for i in range(train_data_N)]
    targets = [[target(i/train_data_N)] for i in range(train_data_N)]

    net = Net([
                Layer(2, 4, xExp, d_xExp),
                Layer(4, 4, sigmoid, d_sigmoid),Layer(4, 4, xExp, d_xExp),
                Layer(4,  1, xExp, d_xExp),
            ]
            )
    print(f'inputs: {inputs}')
    print(f'targets: {targets}')
    net.train(inputs,targets, 0.05, 100,0.1)

    samples_N = 100
    predict = [net.predict([i/samples_N,0.1])[0] for i in range(samples_N)]
    print(predict)
    # 同时画出预测值和真实值
    plt.plot([i/len(predict) for i in range(len(predict))], predict)
    plt.plot([i/len(targets) for i in range(len(targets))], targets)

    plt.show()
    exit(0)
    """
    # 训练一个逻辑值运算的网络
    net = Net([Layer(3, 4, atan, d_atan), Layer(4, 4, atan, d_atan), Layer(4, 1, atan, d_atan)],power=3)
    inputs = [[0.0, 1.0, 1.0], [1.0, 1.0 , 1.0], [1.0, 0.0, 1.0], [0.0, 0.0, 1.0],[0.5, 0.5, 1.0]]
    targets = [[1.0], [1.0], [2.0], [0.0],[0.]]
    net.train(inputs,targets, 0.1, 3000,0.01)

    
    # 画出来三维的图
    import numpy as np
    from mpl_toolkits.mplot3d import Axes3D
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    x = np.linspace(0, 1, 100)
    y = np.linspace(0, 1, 100)
    X, Y = np.meshgrid(x, y)
    Z = np.array([[net.predict([X[i][j],Y[i][j],1])[0] for j in range(len(X[0]))] for i in range(len(X))])
    ax.plot_surface(X, Y, Z)
    plt.show()


    """# 训练一个线性网络
    net = Net([Layer(2, 1, ReLU, d_ReLU)])
    inputs = [[1.0,1], [2.0,1],[3.0,1]]
    targets = [[1.0], [3.0],[7.0]]
    net.train(inputs,targets, 0.25, 1000)
    predict = [net.predict([i/10,1])[0] for i in range(100)]
    print(predict)
    """
    