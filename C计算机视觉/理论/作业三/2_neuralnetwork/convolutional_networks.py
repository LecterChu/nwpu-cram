"""
Implements convolutional networks in PyTorch.
WARNING: you SHOULD NOT use ".to()" or ".cuda()" in each implementation block.
"""
import torch
import random
from eecs598 import Solver
from a3_helper import svm_loss, softmax_loss
from fully_connected_networks import *


def hello_convolutional_networks():
    """
  This is a sample function that we will try to import and run to ensure that
  our environment is correctly set up on Google Colab.
  """
    print('Hello from convolutional_networks.py!')


class Conv(object):

    @staticmethod
    def forward(x, w, b, conv_param):
        """
    A naive implementation of the forward pass for a convolutional layer.
    The input consists of N data points, each with C channels, height H and
    width W. We convolve each input with F different filters, where each filter
    spans all C channels and has height HH and width WW.

    Input:
    - x: Input data of shape (N, C, H, W)
    - w: Filter weights of shape (F, C, HH, WW)
    - b: Biases, of shape (F,)
    - conv_param: A dictionary with the following keys:
      - 'stride': The number of pixels between adjacent receptive fields in the
      horizontal and vertical directions.
      - 'pad': The number of pixels that will be used to zero-pad the input. 
      
    During padding, 'pad' zeros should be placed symmetrically (i.e equally on both sides)
    along the height and width axes of the input. Be careful not to modfiy the original
    input x directly.

    Returns a tuple of:
    - out: Output data, of shape (N, F, H', W') where H' and W' are given by
      H' = 1 + (H + 2 * pad - HH) / stride
      W' = 1 + (W + 2 * pad - WW) / stride
    - cache: (x, w, b, conv_param)
    """
        out = None
        N, C, H, W = x.shape
        F, _, HH, WW = w.shape
        pad = conv_param["pad"]
        stride = conv_param["stride"]
        H_p = 1 + (H + 2 * pad - HH) // stride
        W_p = 1 + (H + 2 * pad - WW) // stride

        out = torch.zeros((N, F, H_p, W_p)).to(x.device).type(x.dtype)
        x_padded = torch.nn.functional.pad(x, (pad, pad, pad, pad)).to(x.device).type(x.dtype)

        for h_p in range(H_p):
            for w_p in range(W_p):
                x_h = h_p * stride
                x_w = w_p * stride
                window = x_padded[:, :, x_h:x_h + HH, x_w:x_w + WW]
                window = window.reshape(N, 1, C, HH, WW)
                out[:, :, h_p, w_p] = (window * w).flatten(start_dim=2).sum(dim=2)

        out += b.reshape(1, F, 1, 1)
        cache = (x, w, b, conv_param)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    A naive implementation of the backward pass for a convolutional layer.

    Inputs:
    - dout: Upstream derivatives.
    - cache: A tuple of (x, w, b, conv_param) as in conv_forward_naive

    Returns a tuple of:
    - dx: Gradient with respect to x
    - dw: Gradient with respect to w
    - db: Gradient with respect to b
    """
        dx, dw, db = None, None, None
        x, w, b, conv_param = cache
        N, C, H, W = x.shape
        F, C, HH, WW = w.shape
        N, F, H_p, W_p = dout.shape
        pad = conv_param["pad"]
        stride = conv_param["stride"]

        dx = torch.zeros_like(x)
        dw = torch.zeros_like(w)
        db = torch.zeros_like(b)

        dout_s = None
        dout_s_p = None
        new_h = H_p
        new_w = W_p
        # dilation
        H_dout_s = new_h = new_h + (H_p - 1) * (stride - 1)
        W_dout_s = new_w = new_w + (W_p - 1) * (stride - 1)
        dout_s = torch.zeros((N, F, new_h, new_w)).to(dout.device).type(dout.dtype)
        dout_s[:, :, ::stride, ::stride] = dout

        if pad > 0:
            new_h = new_h + pad * 2
            new_w = new_w + pad * 2
            dout_s_p = torch.nn.functional.pad(dout_s, (pad, pad, pad, pad))
            dout_s_p = dout_s_p.to(dout_s.device).type(dout_s.dtype)
        else:
            dout_s_p = dout_s

        x_padded = torch.nn.functional.pad(x, (pad, pad, pad, pad)).to(x.device).type(x.dtype)
        w_flipped = w.clone().to(w.device).type(w.dtype)
        w_flipped = w_flipped.flip(dims=[2, 3])  # 180 deg rotatation

        db = dout.permute(1, 0, 2, 3).flatten(start_dim=1).sum(dim=1)

        for h_x in range(H):
            for w_x in range(W):
                window = dout_s_p[:, :, h_x:h_x + HH, w_x:w_x + WW]
                window = window.reshape(N, F, 1, HH, WW)
                result = (window * w_flipped).permute(0, 2, 1, 3, 4)
                result = result.flatten(start_dim=2).sum(dim=2)
                dx[:, :, h_x, w_x] += result

        window2 = dout_s.view(N, F, 1, H_dout_s, W_dout_s)  # N F 1 H_p W_p
        for hh in range(HH):
            for ww in range(WW):
                window1 = x_padded[:, :, hh:hh + H_dout_s, ww:ww + W_dout_s]  # N 1 C H_p W_p
                window1 = window1.view(N, 1, C, H_dout_s, W_dout_s)
                result = (window1 * window2)  # N F C H_p W_p
                result = result.sum(dim=3).sum(dim=3).sum(dim=0)  # F C
                dw[:, :, hh, ww] += result
        return dx, dw, db


class MaxPool(object):

    @staticmethod
    def forward(x, pool_param):
        """
    A naive implementation of the forward pass for a max-pooling layer.

    Inputs:
    - x: Input data, of shape (N, C, H, W)
    - pool_param: dictionary with the following keys:
      - 'pool_height': The height of each pooling region
      - 'pool_width': The width of each pooling region
      - 'stride': The distance between adjacent pooling regions
    No padding is necessary here.

    Returns a tuple of:
    - out: Output data, of shape (N, C, H', W') where H' and W' are given by
      H' = 1 + (H - pool_height) / stride
      W' = 1 + (W - pool_width) / stride
    - cache: (x, pool_param)
    """
        out = None
        N, C, H, W = x.shape
        stride = pool_param["stride"]
        pool_height = pool_param["pool_height"]
        pool_width = pool_param["pool_width"]

        H_p = 1 + (H - pool_height) // stride
        W_p = 1 + (W - pool_width) // stride
        out = torch.zeros((N, C, H_p, W_p)).to(x.device).type(x.dtype)

        for h_p in range(H_p):
            for w_p in range(W_p):
                x_h = h_p * stride
                x_w = w_p * stride
                window = x[:, :, x_h:x_h + pool_height, x_w:x_w + pool_width].flatten(start_dim=2)
                out[:, :, h_p, w_p], _ = torch.max(window, dim=2)
        cache = (x, pool_param)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    A naive implementation of the backward pass for a max-pooling layer.
    Inputs:
    - dout: Upstream derivatives
    - cache: A tuple of (x, pool_param) as in the forward pass.
    Returns:
    - dx: Gradient with respect to x
    """
        dx = None
        x, pool_param = cache
        N, C, H, W = x.shape
        stride = pool_param["stride"]
        pool_height = pool_param["pool_height"]
        pool_width = pool_param["pool_width"]

        H_p = 1 + (H - pool_height) // stride
        W_p = 1 + (W - pool_width) // stride

        dx = torch.zeros_like(x).to(x.device)

        for h_p in range(H_p):
            for w_p in range(W_p):
                x_h = h_p * stride
                x_w = w_p * stride
                x_window = x[:, :, x_h:x_h + pool_height, x_w:x_w + pool_width].flatten(start_dim=2)
                _, max_idx = torch.max(x_window, dim=2)
                max_idx = max_idx.flatten()

                dx_window = dx[:, :, x_h:x_h + pool_height, x_w:x_w + pool_width]
                dx_window = dx_window.view(N * C, pool_height, pool_width)
                row = (max_idx // pool_width)
                col = (max_idx % pool_width)
                dx_window[torch.arange(N * C), row, col] = dout[:, :, h_p, w_p].flatten()
        return dx


class ThreeLayerConvNet(object):
    """
  A three-layer convolutional network with the following architecture:
  conv - relu - 2x2 max pool - linear - relu - linear - softmax
  The network operates on minibatches of data that have shape (N, C, H, W)
  consisting of N images, each with height H and width W and with C input
  channels.
  """

    def __init__(self, input_dims=(3, 32, 32), num_filters=32, filter_size=7,
                 hidden_dim=100, num_classes=10, weight_scale=1e-3, reg=0.0,
                 dtype=torch.float, device='cpu'):
        """
    Initialize a new network.
    Inputs:
    - input_dims: Tuple (C, H, W) giving size of input data
    - num_filters: Number of filters to use in the convolutional layer
    - filter_size: Width/height of filters to use in the convolutional layer
    - hidden_dim: Number of units to use in the fully-connected hidden layer
    - num_classes: Number of scores to produce from the final linear layer.
    - weight_scale: Scalar giving standard deviation for random initialization
      of weights.
    - reg: Scalar giving L2 regularization strength
    - dtype: A torch data type object; all computations will be performed using
      this datatype. float is faster but less accurate, so you should use
      double for numeric gradient checking.
    - device: device to use for computation. 'cpu' or 'cuda'
    """
        self.params = {}
        self.reg = reg
        self.dtype = dtype

        C, H, W = input_dims
        F = num_filters
        HH = WW = filter_size
        stride = pool_height = pool_width = 2
        H_p = 1 + (H - pool_height) // stride
        W_p = 1 + (W - pool_width) // stride
        D = F * H_p * W_p

        self.params['W1'] = torch.normal(0, weight_scale, (F, C, HH, WW)).type(dtype).to(device)
        self.params['W2'] = torch.normal(0, weight_scale, (D, hidden_dim)).type(dtype).to(device)
        self.params['W3'] = torch.normal(0, weight_scale, (hidden_dim, num_classes)).type(dtype).to(device)
        self.params['b1'] = torch.zeros(F).type(dtype).to(device)
        self.params['b2'] = torch.zeros(hidden_dim).type(dtype).to(device)
        self.params['b3'] = torch.zeros(num_classes).type(dtype).to(device)

    def save(self, path):
        checkpoint = {
            'reg': self.reg,
            'dtype': self.dtype,
            'params': self.params,
        }

        torch.save(checkpoint, path)
        print("Saved in {}".format(path))

    def load(self, path):
        checkpoint = torch.load(path, map_location='cpu')
        self.params = checkpoint['params']
        self.dtype = checkpoint['dtype']
        self.reg = checkpoint['reg']
        print("load checkpoint file: {}".format(path))

    def loss(self, X, y=None):
        """
    Evaluate loss and gradient for the three-layer convolutional network.
    Input / output: Same API as TwoLayerNet.
    """
        X = X.to(self.dtype)
        W1, b1 = self.params['W1'], self.params['b1']
        W2, b2 = self.params['W2'], self.params['b2']
        W3, b3 = self.params['W3'], self.params['b3']

        # pass conv_param to the forward pass for the convolutional layer
        # Padding and stride chosen to preserve the input spatial size
        filter_size = W1.shape[2]
        conv_param = {'stride': 1, 'pad': (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {'pool_height': 2, 'pool_width': 2, 'stride': 2}

        scores = None
        out, conv_relu_pool_cache = Conv_ReLU_Pool.forward(X, W1, b1, conv_param, pool_param)
        out, linear_relu_cache = Linear_ReLU.forward(out, W2, b2)
        scores, linear_cache = Linear.forward(out, W3, b3)
        if y is None:
            return scores

        loss, grads = 0.0, {}

        loss, dout = softmax_loss(scores, y)

        dx, grads['W3'], grads['b3'] = Linear.backward(dout, linear_cache)
        dx, grads['W2'], grads['b2'] = Linear_ReLU.backward(dx, linear_relu_cache)
        dx, grads['W1'], grads['b1'] = Conv_ReLU_Pool.backward(dx, conv_relu_pool_cache)

        loss += (self.reg * torch.sum(W2 * W2) +
                 self.reg * torch.sum(W3 * W3))

        grads['W3'] += 2 * self.reg * self.params['W3']
        grads['W2'] += 2 * self.reg * self.params['W2']

        return loss, grads


class DeepConvNet(object):
    """
  A convolutional neural network with an arbitrary number of convolutional
  layers in VGG-Net style. All convolution layers will use kernel size 3 and 
  padding 1 to preserve the feature map size, and all pooling layers will be
  max pooling layers with 2x2 receptive fields and a stride of 2 to halve the
  size of the feature map.

  The network will have the following architecture:
  
  {conv - [batchnorm?] - relu - [pool?]} x (L - 1) - linear

  Each {...} structure is a "macro layer" consisting of a convolution layer,
  an optional batch normalization layer, a ReLU nonlinearity, and an optional
  pooling layer. After L-1 such macro layers, a single fully-connected layer
  is used to predict the class scores.

  The network operates on minibatches of data that have shape (N, C, H, W)
  consisting of N images, each with height H and width W and with C input
  channels.
  """

    def __init__(self, input_dims=(3, 32, 32),
                 num_filters=[8, 8, 8, 8, 8],
                 max_pools=[0, 1, 2, 3, 4],
                 batchnorm=False,
                 num_classes=10, weight_scale=1e-3, reg=0.0,
                 weight_initializer=None,
                 dtype=torch.float, device='cpu'):
        """
    Initialize a new network.

    Inputs:
    - input_dims: Tuple (C, H, W) giving size of input data
    - num_filters: List of length (L - 1) giving the number of convolutional
      filters to use in each macro layer.
    - max_pools: List of integers giving the indices of the macro layers that
      should have max pooling (zero-indexed).
    - batchnorm: Whether to include batch normalization in each macro layer
    - num_classes: Number of scores to produce from the final linear layer.
    - weight_scale: Scalar giving standard deviation for random initialization
      of weights, or the string "kaiming" to use Kaiming initialization instead
    - reg: Scalar giving L2 regularization strength. L2 regularization should
      only be applied to convolutional and fully-connected weight matrices;
      it should not be applied to biases or to batchnorm scale and shifts.
    - dtype: A torch data type object; all computations will be performed using
      this datatype. float is faster but less accurate, so you should use
      double for numeric gradient checking.
    - device: device to use for computation. 'cpu' or 'cuda'    
    """
        self.params = {}
        self.num_layers = len(num_filters) + 1
        self.max_pools = max_pools
        self.batchnorm = batchnorm
        self.reg = reg
        self.dtype = dtype

        if device == 'cuda':
            device = 'cuda:0'

        C, H, W = input_dims
        HH = WW = 3
        H_p = H
        W_p = W

        filters = [C] + num_filters
        for i in range(len(filters) - 1):
            F = filters[i]
            F_next = filters[i + 1]
            if weight_scale != 'kaiming':
                self.params[f'W{1 + i}'] = torch.normal(0, weight_scale, (F_next, F, HH, WW)).type(dtype).to(device)
            else:
                self.params[f'W{1 + i}'] = kaiming_initializer(F, F_next, K=HH, relu=True, device=device, dtype=dtype)

            self.params[f'b{1 + i}'] = torch.zeros(F_next).type(dtype).to(device)

            # print(f'W{1+i}', self.params[f'W{1+i}'].shape)
            # print(f'b{1+i}', self.params[f'b{1+i}'].shape)

            if self.batchnorm:
                self.params[f'beta{1 + i}'] = torch.zeros(F_next).type(dtype).to(device)
                self.params[f'gamma{1 + i}'] = torch.ones(F_next).type(dtype).to(device)
                # print(f'beta{1+i}', self.params[f'beta{1+i}'].shape)
                # print(f'gamma{1+i}', self.params[f'gamma{1+i}'].shape)

            if i in self.max_pools:
                H_p //= 2
                W_p //= 2

        # linear
        D = num_filters[-1] * H_p * W_p

        if weight_scale != 'kaiming':
            self.params[f'W{self.num_layers}'] = torch.normal(0, weight_scale, (D, num_classes)).type(dtype).to(device)
        else:
            self.params[f'W{self.num_layers}'] = kaiming_initializer(D, num_classes, relu=False, device=device,
                                                                     dtype=dtype)

        self.params[f'b{self.num_layers}'] = torch.zeros(num_classes).type(dtype).to(device)

        # print(f'W{self.num_layers}', self.params[f'W{self.num_layers}'].shape)
        # print(f'b{self.num_layers}', self.params[f'b{self.num_layers}'].shape)
        self.bn_params = []
        if self.batchnorm:
            self.bn_params = [{'mode': 'train'} for _ in range(len(num_filters))]

        # Check that we got the right number of parameters
        if not self.batchnorm:
            params_per_macro_layer = 2  # weight and bias
        else:
            params_per_macro_layer = 4  # weight, bias, scale, shift
        num_params = params_per_macro_layer * len(num_filters) + 2
        msg = 'self.params has the wrong number of elements. Got %d; expected %d'
        msg = msg % (len(self.params), num_params)
        assert len(self.params) == num_params, msg

        # Check that all parameters have the correct device and dtype:
        for k, param in self.params.items():
            msg = 'param "%s" has device %r; should be %r' % (k, param.device, device)
            assert param.device == torch.device(device), msg
            msg = 'param "%s" has dtype %r; should be %r' % (k, param.dtype, dtype)
            assert param.dtype == dtype, msg

    def save(self, path):
        checkpoint = {
            'reg': self.reg,
            'dtype': self.dtype,
            'params': self.params,
            'num_layers': self.num_layers,
            'max_pools': self.max_pools,
            'batchnorm': self.batchnorm,
            'bn_params': self.bn_params,
        }

        torch.save(checkpoint, path)
        print("Saved in {}".format(path))

    def load(self, path, dtype, device):
        checkpoint = torch.load(path, map_location='cpu')
        self.params = checkpoint['params']
        self.dtype = dtype
        self.reg = checkpoint['reg']
        self.num_layers = checkpoint['num_layers']
        self.max_pools = checkpoint['max_pools']
        self.batchnorm = checkpoint['batchnorm']
        self.bn_params = checkpoint['bn_params']

        for p in self.params:
            self.params[p] = self.params[p].type(dtype).to(device)

        for i in range(len(self.bn_params)):
            for p in ["running_mean", "running_var"]:
                self.bn_params[i][p] = self.bn_params[i][p].type(dtype).to(device)

        print("load checkpoint file: {}".format(path))

    def loss(self, X, y=None):
        """
    Evaluate loss and gradient for the deep convolutional network.
    Input / output: Same API as ThreeLayerConvNet.
    """
        X = X.to(self.dtype)
        mode = 'test' if y is None else 'train'

        # Set train/test mode for batchnorm params since they
        # behave differently during training and testing.
        if self.batchnorm:
            for bn_param in self.bn_params:
                bn_param['mode'] = mode
        scores = None

        # pass conv_param to the forward pass for the convolutional layer
        # Padding and stride chosen to preserve the input spatial size
        filter_size = 3
        conv_param = {'stride': 1, 'pad': (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {'pool_height': 2, 'pool_width': 2, 'stride': 2}

        scores = None
        caches = {}
        layer = {}
        layer[0] = X
        for i in range(1, self.num_layers):
            W = self.params[f'W{i}']
            b = self.params[f'b{i}']
            X_input = layer[i - 1]
            beta = gamma = None
            if self.batchnorm:
                gamma = self.params[f'gamma{i}']
                beta = self.params[f'beta{i}']
                bn_param = self.bn_params[i - 1]

            if i - 1 in self.max_pools:
                if self.batchnorm:
                    layer[i], caches[i] = Conv_BatchNorm_ReLU_Pool.forward(X_input, W, b, gamma, beta,
                                                                           conv_param, bn_param, pool_param)
                else:
                    layer[i], caches[i] = Conv_ReLU_Pool.forward(X_input, W, b, conv_param, pool_param)
            else:
                if self.batchnorm:
                    layer[i], caches[i] = Conv_BatchNorm_ReLU.forward(X_input, W, b, gamma, beta,
                                                                      conv_param, bn_param)
                else:
                    layer[i], caches[i] = Conv_ReLU.forward(X_input, W, b, conv_param)

        W = self.params[f'W{self.num_layers}']
        b = self.params[f'b{self.num_layers}']

        scores, caches[self.num_layers] = Linear.forward(layer[self.num_layers - 1], W, b)

        if y is None:
            return scores

        loss, grads = 0, {}

        loss, dout = softmax_loss(scores, y)
        dx = {}
        W = f'W{self.num_layers}'
        b = f'b{self.num_layers}'
        dx[self.num_layers], grads[W], grads[b] = Linear.backward(dout, caches[self.num_layers])
        for i in reversed(range(1, self.num_layers)):
            if i - 1 in self.max_pools:
                if self.batchnorm:
                    dx[i], grads[f'W{i}'], grads[f'b{i}'], grads[f'gamma{i}'], grads[
                        f'beta{i}'] = Conv_BatchNorm_ReLU_Pool.backward(dx[i + 1], caches[i])
                else:
                    dx[i], grads[f'W{i}'], grads[f'b{i}'] = Conv_ReLU_Pool.backward(dx[i + 1], caches[i])
            else:
                if self.batchnorm:
                    dx[i], grads[f'W{i}'], grads[f'b{i}'], grads[f'gamma{i}'], grads[
                        f'beta{i}'] = Conv_BatchNorm_ReLU.backward(dx[i + 1], caches[i])
                else:
                    dx[i], grads[f'W{i}'], grads[f'b{i}'] = Conv_ReLU.backward(dx[i + 1], caches[i])

        for i in range(1, self.num_layers + 1):
            W = self.params[f'W{i}']
            loss += 0.5 * self.reg * torch.sum(W * W)
            grads[f'W{i}'] += self.reg * W

        return loss, grads


def find_overfit_parameters():
    weight_scale = 2e-3  # Experiment with this!
    learning_rate = 1e-5  # Experiment with this!

    weight_scale = .4
    learning_rate = .04

    return weight_scale, learning_rate


def create_convolutional_solver_instance(data_dict, dtype, device):
    model = None
    solver = None
    input_dims = data_dict['X_train'].shape[1:]
    bn_model = DeepConvNet(input_dims=input_dims, num_classes=10,
                           num_filters=[32, 64, 128],
                           max_pools=[0, 1, 2],
                           weight_scale='kaiming',
                           batchnorm=True,
                           reg=1e-4, dtype=dtype, device=device)
    solver = Solver(bn_model, data_dict,
                    num_epochs=3, batch_size=128,
                    update_rule=adam,
                    optim_config={
                        'learning_rate': .005,
                    },
                    print_every=50,
                    print_acc_every=1,
                    verbose=True, device=device)
    return solver


def kaiming_initializer(Din, Dout, K=None, relu=True, device='cpu',
                        dtype=torch.float32):
    """
  Implement Kaiming initialization for linear and convolution layers.
  
  Inputs:
  - Din, Dout: Integers giving the number of input and output dimensions for
    this layer
  - K: If K is None, then initialize weights for a linear layer with Din input
    dimensions and Dout output dimensions. Otherwise if K is a nonnegative
    integer then initialize the weights for a convolution layer with Din input
    channels, Dout output channels, and a kernel size of KxK.
  - relu: If ReLU=True, then initialize weights with a gain of 2 to account for
    a ReLU nonlinearity (Kaiming initializaiton); otherwise initialize weights
    with a gain of 1 (Xavier initialization).
  - device, dtype: The device and datatype for the output tensor.

  Returns:
  - weight: A torch Tensor giving initialized weights for this layer. For a
    linear layer it should have shape (Din, Dout); for a convolution layer it
    should have shape (Dout, Din, K, K).
  """
    gain = 2. if relu else 1.
    weight = None
    if K is None:
        weight_scale = torch.sqrt(torch.tensor(gain / Din))
        weight = torch.normal(0, weight_scale, (Din, Dout)).type(dtype).to(device)
    else:
        weight_scale = torch.sqrt(torch.tensor(gain / (Din * K * K)))
        weight = torch.normal(0, weight_scale, (Dout, Din, K, K)).type(dtype).to(device)
    return weight


class BatchNorm(object):

    @staticmethod
    def forward(x, gamma, beta, bn_param):
        """
    Forward pass for batch normalization.

    During training the sample mean and (uncorrected) sample variance are
    computed from minibatch statistics and used to normalize the incoming data.
    During training we also keep an exponentially decaying running mean of the
    mean and variance of each feature, and these averages are used to normalize
    data at test-time.

    At each timestep we update the running averages for mean and variance using
    an exponential decay based on the momentum parameter:

    running_mean = momentum * running_mean + (1 - momentum) * sample_mean
    running_var = momentum * running_var + (1 - momentum) * sample_var

    Note that the batch normalization paper suggests a different test-time
    behavior: they compute sample mean and variance for each feature using a
    large number of training images rather than using a running average. For
    this implementation we have chosen to use running averages instead since
    they do not require an additional estimation step; the PyTorch
    implementation of batch normalization also uses running averages.

    Input:
    - x: Data of shape (N, D)
    - gamma: Scale parameter of shape (D,)
    - beta: Shift paremeter of shape (D,)
    - bn_param: Dictionary with the following keys:
      - mode: 'train' or 'test'; required
      - eps: Constant for numeric stability
      - momentum: Constant for running mean / variance.
      - running_mean: Array of shape (D,) giving running mean of features
      - running_var Array of shape (D,) giving running variance of features

    Returns a tuple of:
    - out: of shape (N, D)
    - cache: A tuple of values needed in the backward pass
    """
        mode = bn_param['mode']
        eps = bn_param.get('eps', 1e-5)
        momentum = bn_param.get('momentum', 0.9)

        N, D = x.shape
        running_mean = bn_param.get('running_mean', torch.zeros(D, dtype=x.dtype, device=x.device))
        running_var = bn_param.get('running_var', torch.zeros(D, dtype=x.dtype, device=x.device))

        out, cache = None, None
        if mode == 'train':
            sample_mean = x.t().mean(dim=1)  # D
            sample_var = (x - sample_mean).pow(2).t().mean(dim=1)  # D
            out = ((x - sample_mean) / torch.sqrt(sample_var + eps)) * gamma + beta  # N * D

            running_mean = momentum * running_mean + (1 - momentum) * sample_mean
            running_var = momentum * running_var + (1 - momentum) * sample_var

            cache = (x, bn_param, gamma)
        elif mode == 'test':
            out = ((x - running_mean) / torch.sqrt(running_var + eps)) * gamma + beta  # N * D
        else:
            raise ValueError('Invalid forward batchnorm mode "%s"' % mode)

        # Store the updated running means back into bn_param
        bn_param['running_mean'] = running_mean.detach()
        bn_param['running_var'] = running_var.detach()

        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    Backward pass for batch normalization.

    For this implementation, you should write out a computation graph for
    batch normalization on paper and propagate gradients backward through
    intermediate nodes.

    Inputs:
    - dout: Upstream derivatives, of shape (N, D)
    - cache: Variable of intermediates from batchnorm_forward.

    Returns a tuple of:
    - dx: Gradient with respect to inputs x, of shape (N, D)
    - dgamma: Gradient with respect to scale parameter gamma, of shape (D,)
    - dbeta: Gradient with respect to shift parameter beta, of shape (D,)
    """
        dx, dgamma, dbeta = None, None, None
        dbeta = dout.t().sum(dim=1)

        x, bn_param, gamma = cache
        N, D = x.shape
        eps = bn_param.get('eps', 1e-5)
        sample_mean = x.t().mean(dim=1)  # D
        sample_var = (x - sample_mean).pow(2).t().mean(dim=1)  # D
        x_hat = (x - sample_mean) / torch.sqrt(sample_var + eps)
        dgamma = (x_hat * dout).t().sum(dim=1)  # D

        # derivation acknowledgement : https://kevinzakka.github.io/2016/09/14/batch_normalization/
        dx_hat = gamma * dout
        term1 = N * dx_hat
        term2 = dx_hat.t().sum(dim=1)
        term3 = x_hat * (x_hat * dx_hat).t().sum(dim=1)
        term4 = N * torch.sqrt(sample_var + eps)
        dx = (term1 - term2 - term3) / term4

        return dx, dgamma, dbeta

    @staticmethod
    def backward_alt(dout, cache):
        """
    Alternative backward pass for batch normalization.
    For this implementation you should work out the derivatives for the batch
    normalizaton backward pass on paper and simplify as much as possible. You
    should be able to derive a simple expression for the backward pass. 
    See the jupyter notebook for more hints.
    
    Note: This implementation should expect to receive the same cache variable
    as batchnorm_backward, but might not use all of the values in the cache.

    Inputs / outputs: Same as batchnorm_backward
    """
        dx, dgamma, dbeta = None, None, None
        dbeta = dout.t().sum(dim=1)

        x, bn_param, gamma = cache
        N, D = x.shape
        eps = bn_param.get('eps', 1e-5)
        sample_mean = x.t().mean(dim=1)  # D
        var = (x - sample_mean).pow(2).t().mean(dim=1)  # D
        x_hat = (x - sample_mean) / torch.sqrt(var + eps)
        dgamma = (x_hat * dout).t().sum(dim=1)  # D

        # local gradients
        dy_du = -1 / torch.sqrt(var + eps)
        dvar_du = -2 * (x - sample_mean).t().mean(dim=1)
        dy_dstd = (sample_mean - x) / (var + eps)
        dstd_dvar = 1 / (2 * torch.sqrt(var + eps))
        dy_dx = 1 / torch.sqrt(var + eps)
        dvar_dx = (2 / N) * (x - sample_mean)
        du_dx = 1 / N

        dl_dy = gamma * dout  # N * D
        dl_dstd = (dl_dy * dy_dstd).t().sum(dim=1)  # D
        dl_dvar = dl_dstd * dstd_dvar  # D
        dl_du = dl_dvar * dvar_du + (dl_dy * dy_du).t().sum(dim=1)  # D
        dl_dx = dx = dl_du * du_dx + dl_dvar * dvar_dx + dl_dy * dy_dx  # N * D

        return dx, dgamma, dbeta


class SpatialBatchNorm(object):

    @staticmethod
    def forward(x, gamma, beta, bn_param):
        """
    Computes the forward pass for spatial batch normalization.

    Inputs:
    - x: Input data of shape (N, C, H, W)
    - gamma: Scale parameter, of shape (C,)
    - beta: Shift parameter, of shape (C,)
    - bn_param: Dictionary with the following keys:
      - mode: 'train' or 'test'; required
      - eps: Constant for numeric stability
      - momentum: Constant for running mean / variance. momentum=0 means that
      old information is discarded completely at every time step, while
      momentum=1 means that new information is never incorporated. The
      default of momentum=0.9 should work well in most situations.
      - running_mean: Array of shape (C,) giving running mean of features
      - running_var Array of shape (C,) giving running variance of features

    Returns a tuple of:
    - out: Output data, of shape (N, C, H, W)
    - cache: Values needed for the backward pass
    """
        out, cache = None, None
        N, C, H, W = x.shape
        x_p = x.permute(1, 0, 2, 3).flatten(start_dim=1).t()  # (N*H*W) X C => N X D
        x_bn, cache = BatchNorm.forward(x_p, gamma, beta, bn_param)
        out = x_bn.t().view(C, N, H, W).permute(1, 0, 2, 3)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    Computes the backward pass for spatial batch normalization.
    Inputs:
    - dout: Upstream derivatives, of shape (N, C, H, W)
    - cache: Values from the forward pass
    Returns a tuple of:
    - dx: Gradient with respect to inputs, of shape (N, C, H, W)
    - dgamma: Gradient with respect to scale parameter, of shape (C,)
    - dbeta: Gradient with respect to shift parameter, of shape (C,)
    """
        dx, dgamma, dbeta = None, None, None
        N, C, H, W = dout.shape
        dout_p = dout.permute(1, 0, 2, 3).flatten(start_dim=1).t()
        dx, dgamma, dbeta = BatchNorm.backward(dout_p, cache)
        dx = dx.t().view(C, N, H, W).permute(1, 0, 2, 3)

        return dx, dgamma, dbeta


class FastConv(object):

    @staticmethod
    def forward(x, w, b, conv_param):
        N, C, H, W = x.shape
        F, _, HH, WW = w.shape
        stride, pad = conv_param['stride'], conv_param['pad']
        layer = torch.nn.Conv2d(C, F, (HH, WW), stride=stride, padding=pad)
        layer.weight = torch.nn.Parameter(w)
        layer.bias = torch.nn.Parameter(b)
        tx = x.detach()
        tx.requires_grad = True
        out = layer(tx)
        cache = (x, w, b, conv_param, tx, out, layer)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        try:
            x, _, _, _, tx, out, layer = cache
            out.backward(dout)
            dx = tx.grad.detach()
            dw = layer.weight.grad.detach()
            db = layer.bias.grad.detach()
            layer.weight.grad = layer.bias.grad = None
        except RuntimeError:
            dx, dw, db = torch.zeros_like(tx), torch.zeros_like(layer.weight), torch.zeros_like(layer.bias)
        return dx, dw, db


class FastMaxPool(object):

    @staticmethod
    def forward(x, pool_param):
        N, C, H, W = x.shape
        pool_height, pool_width = pool_param['pool_height'], pool_param['pool_width']
        stride = pool_param['stride']
        layer = torch.nn.MaxPool2d(kernel_size=(pool_height, pool_width), stride=stride)
        tx = x.detach()
        tx.requires_grad = True
        out = layer(tx)
        cache = (x, pool_param, tx, out, layer)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        try:
            x, _, tx, out, layer = cache
            out.backward(dout)
            dx = tx.grad.detach()
        except RuntimeError:
            dx = torch.zeros_like(tx)
        return dx


class Conv_ReLU(object):

    @staticmethod
    def forward(x, w, b, conv_param):
        """
    A convenience layer that performs a convolution followed by a ReLU.
    Inputs:
    - x: Input to the convolutional layer
    - w, b, conv_param: Weights and parameters for the convolutional layer
    Returns a tuple of:
    - out: Output from the ReLU
    - cache: Object to give to the backward pass
    """
        a, conv_cache = FastConv.forward(x, w, b, conv_param)
        out, relu_cache = ReLU.forward(a)
        cache = (conv_cache, relu_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    Backward pass for the conv-relu convenience layer.
    """
        conv_cache, relu_cache = cache
        da = ReLU.backward(dout, relu_cache)
        dx, dw, db = FastConv.backward(da, conv_cache)
        return dx, dw, db


class Conv_ReLU_Pool(object):

    @staticmethod
    def forward(x, w, b, conv_param, pool_param):
        """
    A convenience layer that performs a convolution, a ReLU, and a pool.
    Inputs:
    - x: Input to the convolutional layer
    - w, b, conv_param: Weights and parameters for the convolutional layer
    - pool_param: Parameters for the pooling layer
    Returns a tuple of:
    - out: Output from the pooling layer
    - cache: Object to give to the backward pass
    """
        a, conv_cache = FastConv.forward(x, w, b, conv_param)
        s, relu_cache = ReLU.forward(a)
        out, pool_cache = FastMaxPool.forward(s, pool_param)
        cache = (conv_cache, relu_cache, pool_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    Backward pass for the conv-relu-pool convenience layer
    """
        conv_cache, relu_cache, pool_cache = cache
        ds = FastMaxPool.backward(dout, pool_cache)
        da = ReLU.backward(ds, relu_cache)
        dx, dw, db = FastConv.backward(da, conv_cache)
        return dx, dw, db


class Linear_BatchNorm_ReLU(object):

    @staticmethod
    def forward(x, w, b, gamma, beta, bn_param):
        """
    Convenience layer that performs an linear transform, batch normalization,
    and ReLU.
    Inputs:
    - x: Array of shape (N, D1); input to the linear layer
    - w, b: Arrays of shape (D2, D2) and (D2,) giving the weight and bias for
      the linear transform.
    - gamma, beta: Arrays of shape (D2,) and (D2,) giving scale and shift
      parameters for batch normalization.
    - bn_param: Dictionary of parameters for batch normalization.
    Returns:
    - out: Output from ReLU, of shape (N, D2)
    - cache: Object to give to the backward pass.
    """
        a, fc_cache = Linear.forward(x, w, b)
        a_bn, bn_cache = BatchNorm.forward(a, gamma, beta, bn_param)
        out, relu_cache = ReLU.forward(a_bn)
        cache = (fc_cache, bn_cache, relu_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
    Backward pass for the linear-batchnorm-relu convenience layer.
    """
        fc_cache, bn_cache, relu_cache = cache
        da_bn = ReLU.backward(dout, relu_cache)
        da, dgamma, dbeta = BatchNorm.backward(da_bn, bn_cache)
        dx, dw, db = Linear.backward(da, fc_cache)
        return dx, dw, db, dgamma, dbeta


class Conv_BatchNorm_ReLU(object):

    @staticmethod
    def forward(x, w, b, gamma, beta, conv_param, bn_param):
        a, conv_cache = FastConv.forward(x, w, b, conv_param)
        an, bn_cache = SpatialBatchNorm.forward(a, gamma, beta, bn_param)
        out, relu_cache = ReLU.forward(an)
        cache = (conv_cache, bn_cache, relu_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        conv_cache, bn_cache, relu_cache = cache
        dan = ReLU.backward(dout, relu_cache)
        da, dgamma, dbeta = SpatialBatchNorm.backward(dan, bn_cache)
        dx, dw, db = FastConv.backward(da, conv_cache)
        return dx, dw, db, dgamma, dbeta


class Conv_BatchNorm_ReLU_Pool(object):

    @staticmethod
    def forward(x, w, b, gamma, beta, conv_param, bn_param, pool_param):
        a, conv_cache = FastConv.forward(x, w, b, conv_param)
        an, bn_cache = SpatialBatchNorm.forward(a, gamma, beta, bn_param)
        s, relu_cache = ReLU.forward(an)
        out, pool_cache = FastMaxPool.forward(s, pool_param)
        cache = (conv_cache, bn_cache, relu_cache, pool_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        conv_cache, bn_cache, relu_cache, pool_cache = cache
        ds = FastMaxPool.backward(dout, pool_cache)
        dan = ReLU.backward(ds, relu_cache)
        da, dgamma, dbeta = SpatialBatchNorm.backward(dan, bn_cache)
        dx, dw, db = FastConv.backward(da, conv_cache)
        return dx, dw, db, dgamma, dbeta
