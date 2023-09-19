"""
Implements fully connected networks in PyTorch.
WARNING: you SHOULD NOT use ".to()" or ".cuda()" in each implementation block.
"""
import torch
import random
from a3_helper import svm_loss, softmax_loss
from eecs598 import Solver

def hello_fully_connected_networks():
  """
  This is a sample function that we will try to import and run to ensure that
  our environment is correctly set up on Google Colab.
  """
  print('Hello from fully_connected_networks.py!')


class Linear(object):

  @staticmethod
  def forward(x, w, b):
    """
    Computes the forward pass for an linear (fully-connected) layer.
    The input x has shape (N, d_1, ..., d_k) and contains a minibatch of N
    examples, where each example x[i] has shape (d_1, ..., d_k). We will
    reshape each input into a vector of dimension D = d_1 * ... * d_k, and
    then transform it to an output vector of dimension M.
    Inputs:
    - x: A tensor containing input data, of shape (N, d_1, ..., d_k)
    - w: A tensor of weights, of shape (D, M)
    - b: A tensor of biases, of shape (M,)
    Returns a tuple of:
    - out: output, of shape (N, M)
    - cache: (x, w, b)
    """
    out = None
    out = torch.flatten(x, start_dim=1).mm(w) + b
    cache = (x, w, b)
    return out, cache

  @staticmethod
  def backward(dout, cache):
    """
    Computes the backward pass for an linear layer.
    Inputs:
    - dout: Upstream derivative, of shape (N, M)
    - cache: Tuple of:
      - x: Input data, of shape (N, d_1, ... d_k)
      - w: Weights, of shape (D, M)
      - b: Biases, of shape (M,)
    Returns a tuple of:
    - dx: Gradient with respect to x, of shape (N, d1, ..., d_k)
    - dw: Gradient with respect to w, of shape (D, M)
    - db: Gradient with respect to b, of shape (M,)
    """
    x, w, b = cache
    dx, dw, db = None, None, None
    x_2 = torch.flatten(x, start_dim=1)
    dx = dout.mm(w.t()).reshape(x.shape) 
    dw = x_2.t().mm(dout)
    db = dout.t().sum(dim=1)
    return dx, dw, db


class ReLU(object):

  @staticmethod
  def forward(x):
    """
    Computes the forward pass for a layer of rectified linear units (ReLUs).
    Input:
    - x: Input; a tensor of any shape
    Returns a tuple of:
    - out: Output, a tensor of the same shape as x
    - cache: x
    """
    out = None
    out = x.clone()
    out[out<0] = 0
    cache = x
    return out, cache

  @staticmethod
  def backward(dout, cache):
    """
    Computes the backward pass for a layer of rectified linear units (ReLUs).
    Input:
    - dout: Upstream derivatives, of any shape
    - cache: Input x, of same shape as dout
    Returns:
    - dx: Gradient with respect to x
    """
    dx, x = None, cache
    dx = dout.clone()
    dx[x<0] = 0
    return dx


class Linear_ReLU(object):

  @staticmethod
  def forward(x, w, b):
    """
    Convenience layer that performs an linear transform followed by a ReLU.

    Inputs:
    - x: Input to the linear layer
    - w, b: Weights for the linear layer
    Returns a tuple of:
    - out: Output from the ReLU
    - cache: Object to give to the backward pass
    """
    a, fc_cache = Linear.forward(x, w, b)
    out, relu_cache = ReLU.forward(a)
    cache = (fc_cache, relu_cache)
    return out, cache

  @staticmethod
  def backward(dout, cache):
    """
    Backward pass for the linear-relu convenience layer
    """
    fc_cache, relu_cache = cache
    da = ReLU.backward(dout, relu_cache)
    dx, dw, db = Linear.backward(da, fc_cache)
    return dx, dw, db


class Dropout(object):

  @staticmethod
  def forward(x, dropout_param):
    """
    Performs the forward pass for (inverted) dropout.
    Inputs:
    - x: Input data: tensor of any shape
    - dropout_param: A dictionary with the following keys:
      - p: Dropout parameter. We *drop* each neuron output with probability p.
      - mode: 'test' or 'train'. If the mode is train, then perform dropout;
      if the mode is test, then just return the input.
      - seed: Seed for the random number generator. Passing seed makes this
      function deterministic, which is needed for gradient checking but not
      in real networks.
    Outputs:
    - out: Tensor of the same shape as x.
    - cache: tuple (dropout_param, mask). In training mode, mask is the dropout
      mask that was used to multiply the input; in test mode, mask is None.
    NOTE: Please implement **inverted** dropout, not the vanilla version of dropout.
    See http://cs231n.github.io/neural-networks-2/#reg for more details.
    NOTE 2: Keep in mind that p is the probability of **dropping** a neuron
    output; this might be contrary to some sources, where it is referred to
    as the probability of keeping a neuron output.
    """
    p, mode = dropout_param['p'], dropout_param['mode']
    if 'seed' in dropout_param:
      torch.manual_seed(dropout_param['seed'])

    mask = None
    out = None

    if mode == 'train':
      keep_prop = 1-p
      mask = (torch.rand(x.shape) < keep_prop).to(x.device)
      out = torch.zeros_like(x).to(x.device)
      out[mask] = 1
      out /= keep_prop
      out *= x
    elif mode == 'test':
      mask = torch.ones_like(x).to(x.device)
      out = x.clone().to(x.device)

    cache = (dropout_param, mask)

    return out, cache

  @staticmethod
  def backward(dout, cache):
    """
    Perform the backward pass for (inverted) dropout.
    Inputs:
    - dout: Upstream derivatives, of any shape
    - cache: (dropout_param, mask) from Dropout.forward.
    """
    dropout_param, mask = cache
    mode = dropout_param['mode']

    dx = None
    if mode == 'train':
      keep_prop = 1 - dropout_param['p']
      dx = mask * dout / keep_prop
    elif mode == 'test':
      dx = dout
    return dx

class Linear_ReLU_Dropout(object):

  @staticmethod
  def forward(x, w, b, dropout_param):
    """
    Convenience layer that performs an linear transform followed by a ReLU
    followed by dropout.

    Inputs:
    - x: Input to the linear layer
    - w, b: Weights for the linear layer
    Returns a tuple of:
    - out: Output from the ReLU
    - cache: Object to give to the backward pass
    """
    out, cache = Linear_ReLU.forward(x, w, b)
    fc_cache, relu_cache = cache
    out, dp_cache = Dropout.forward(out, dropout_param)
    cache = (fc_cache, relu_cache, dp_cache)
    return out, cache

  @staticmethod
  def backward(dout, cache):
    """
    Backward pass for the linear-relu convenience layer
    """
    fc_cache, relu_cache, dp_cache = cache
    ddp_out = Dropout.backward(dout, dp_cache)
    drl_out = ReLU.backward(ddp_out, relu_cache)
    dx, dw, db = Linear.backward(drl_out, fc_cache)
    return dx, dw, db


class TwoLayerNet(object):
  """
  A two-layer fully-connected neural network with ReLU nonlinearity and
  softmax loss that uses a modular layer design. We assume an input dimension
  of D, a hidden dimension of H, and perform classification over C classes.
  The architecure should be linear - relu - linear - softmax.
  Note that this class does not implement gradient descent; instead, it
  will interact with a separate Solver object that is responsible for running
  optimization.

  The learnable parameters of the model are stored in the dictionary
  self.params that maps parameter names to PyTorch tensors.
  """

  def __init__(self, input_dim=3*32*32, hidden_dim=100, num_classes=10,
         weight_scale=1e-3, reg=0.0, dtype=torch.float32, device='cpu'):
    """
    Initialize a new network.
    Inputs:
    - input_dim: An integer giving the size of the input
    - hidden_dim: An integer giving the size of the hidden layer
    - num_classes: An integer giving the number of classes to classify
    - weight_scale: Scalar giving the standard deviation for random
      initialization of the weights.
    - reg: Scalar giving L2 regularization strength.
    - dtype: A torch data type object; all computations will be performed using
      this datatype. float is faster but less accurate, so you should use
      double for numeric gradient checking.
    - device: device to use for computation. 'cpu' or 'cuda'
    """
    self.params = {}
    self.reg = reg
    self.params['W1'] = torch.normal(0, weight_scale, (input_dim, hidden_dim)).type(dtype).to(device)
    self.params['b1'] = torch.zeros(hidden_dim).type(dtype).to(device)
    self.params['W2'] = torch.normal(0, weight_scale, (hidden_dim, num_classes)).type(dtype).to(device)
    self.params['b2'] = torch.zeros(num_classes).type(dtype).to(device)


  def save(self, path):
    checkpoint = {
      'reg': self.reg,
      'params': self.params,
    }
      
    torch.save(checkpoint, path)
    print("Saved in {}".format(path))

  def load(self, path, dtype, device):
    checkpoint = torch.load(path, map_location='cpu')
    self.params = checkpoint['params']
    self.reg = checkpoint['reg']
    for p in self.params:
      self.params[p] = self.params[p].type(dtype).to(device)
    print("load checkpoint file: {}".format(path))


  def loss(self, X, y=None):
    """
    Compute loss and gradient for a minibatch of data.

    Inputs:
    - X: Tensor of input data of shape (N, d_1, ..., d_k)
    - y: int64 Tensor of labels, of shape (N,). y[i] gives the label for X[i].

    Returns:
    If y is None, then run a test-time forward pass of the model and return:
    - scores: Tensor of shape (N, C) giving classification scores, where
      scores[i, c] is the classification score for X[i] and class c.
    If y is not None, then run a training-time forward and backward pass and
    return a tuple of:
    - loss: Scalar value giving the loss
    - grads: Dictionary with the same keys as self.params, mapping parameter
      names to gradients of the loss with respect to those parameters.
    """
    scores = None
    
    out1, cache1 = Linear_ReLU.forward(X, self.params['W1'], self.params['b1'])
    scores, cache2 = Linear.forward(out1, self.params['W2'], self.params['b2'])

    if y is None:
      return scores

    loss, grads = 0, {}
    loss, dout = softmax_loss(scores, y)
    dx_2, grads['W2'], grads['b2'] = Linear.backward(dout, cache2)
    dx_1, grads['W1'], grads['b1'] = Linear_ReLU.backward(dx_2, cache1)
    
    loss += (self.reg * torch.sum(self.params['W1'] * self.params['W1']) +
             self.reg * torch.sum(self.params['W2'] * self.params['W2']))

    grads['W2'] += 2 * self.reg * self.params['W2']
    grads['W1'] += 2 * self.reg * self.params['W1']

    return loss, grads

class FullyConnectedNet(object):
  """
  A fully-connected neural network with an arbitrary number of hidden layers,
  ReLU nonlinearities, and a softmax loss function.
  For a network with L layers, the architecture will be:

  {linear - relu - [dropout]} x (L - 1) - linear - softmax

  where dropout is optional, and the {...} block is repeated L - 1 times.

  Similar to the TwoLayerNet above, learnable parameters are stored in the
  self.params dictionary and will be learned using the Solver class.
  """

  def __init__(self, hidden_dims, input_dim=3*32*32, num_classes=10,
               dropout=0.0, reg=0.0, weight_scale=1e-2, seed=None,
               dtype=torch.float, device='cpu'):
    """
    Initialize a new FullyConnectedNet.

    Inputs:
    - hidden_dims: A list of integers giving the size of each hidden layer.
    - input_dim: An integer giving the size of the input.
    - num_classes: An integer giving the number of classes to classify.
    - dropout: Scalar between 0 and 1 giving the drop probability for networks
      with dropout. If dropout=0 then the network should not use dropout.
    - reg: Scalar giving L2 regularization strength.
    - weight_scale: Scalar giving the standard deviation for random
      initialization of the weights.
    - seed: If not None, then pass this random seed to the dropout layers. This
      will make the dropout layers deteriminstic so we can gradient check the
      model.
    - dtype: A torch data type object; all computations will be performed using
      this datatype. float is faster but less accurate, so you should use
      double for numeric gradient checking.
    - device: device to use for computation. 'cpu' or 'cuda'
    """
    self.use_dropout = dropout != 0
    self.reg = reg
    self.num_layers = 1 + len(hidden_dims)
    self.dtype = dtype
    self.params = {}
    
    dims = [input_dim] + hidden_dims + [num_classes]
    for i in range(self.num_layers):
      self.params[f'W{1+i}'] = torch.normal(0, weight_scale, (dims[i], dims[i+1])).type(dtype).to(device)
      self.params[f'b{1+i}'] = torch.zeros(dims[i+1]).type(dtype).to(device)

    self.dropout_param = {}
    if self.use_dropout:
      self.dropout_param = {'mode': 'train', 'p': dropout}
      if seed is not None:
        self.dropout_param['seed'] = seed


  def save(self, path):
    checkpoint = {
      'reg': self.reg,
      'dtype': self.dtype,
      'params': self.params,
      'num_layers': self.num_layers,
      'use_dropout': self.use_dropout,
      'dropout_param': self.dropout_param,
    }
      
    torch.save(checkpoint, path)
    print("Saved in {}".format(path))


  def load(self, path, dtype, device):
    checkpoint = torch.load(path, map_location='cpu')
    self.params = checkpoint['params']
    self.dtype = dtype
    self.reg = checkpoint['reg']
    self.num_layers = checkpoint['num_layers']
    self.use_dropout = checkpoint['use_dropout']
    self.dropout_param = checkpoint['dropout_param']

    for p in self.params:
      self.params[p] = self.params[p].type(dtype).to(device)

    print("load checkpoint file: {}".format(path))

  def loss(self, X, y=None):
    """
    Compute loss and gradient for the fully-connected net.
    Input / output: Same as TwoLayerNet above.
    """
    X = X.to(self.dtype)
    mode = 'test' if y is None else 'train'

    # Set train/test mode for batchnorm params and dropout param since they
    # behave differently during training and testing.
    if self.use_dropout:
      self.dropout_param['mode'] = mode
    scores = None
    caches = {}
    layer = {}
    layer[0] = X
    for i in range(1, self.num_layers):
      if self.use_dropout:
        layer[i], caches[i] = Linear_ReLU_Dropout.forward(layer[i-1], self.params[f'W{i}'], self.params[f'b{i}'], self.dropout_param)
      else:
        layer[i], caches[i] = Linear_ReLU.forward(layer[i-1], self.params[f'W{i}'], self.params[f'b{i}'])
        
    scores, caches[self.num_layers] = Linear.forward(layer[self.num_layers-1], self.params[f'W{self.num_layers}'], self.params[f'b{self.num_layers}'])

    # If test mode return early
    if mode == 'test':
      return scores

    loss, grads = 0.0, {}
    loss, dout = softmax_loss(scores, y)
    dx = {}
    dx[self.num_layers], grads[f'W{self.num_layers}'], grads[f'b{self.num_layers}'] = Linear.backward(dout, caches[self.num_layers])
    for i in reversed(range(1, self.num_layers)):
      if self.use_dropout:
        dx[i], grads[f'W{i}'], grads[f'b{i}'] = Linear_ReLU_Dropout.backward(dx[i+1], caches[i])
      else:
        dx[i], grads[f'W{i}'], grads[f'b{i}'] = Linear_ReLU.backward(dx[i+1], caches[i])
    
    for i in range(1, self.num_layers + 1):
      loss += 0.5 * self.reg * torch.sum(self.params[f'W{i}'] * self.params[f'W{i}'])
      grads[f'W{i}'] += self.reg * self.params[f'W{i}']

    return loss, grads


def create_solver_instance(data_dict, dtype, device):
  model = TwoLayerNet(hidden_dim=200, dtype=dtype, device=device)
  solver = None
  # Replace "pass" statement with your code
  solver = Solver(model, data_dict,
          update_rule=sgd,
          optim_config={
            'learning_rate': 1,
          },
          lr_decay=0.95,
          num_epochs=10, batch_size=500,
          print_every=500,
          device=device)
  return solver


def get_three_layer_network_params():
  weight_scale = .01   # Experiment with this!
  learning_rate = .9  # Experiment with this!
  weight_scale = .04  
  learning_rate = .6  
  return weight_scale, learning_rate


def get_five_layer_network_params():
  learning_rate = .04  # Experiment with this!
  weight_scale = .2   # Experiment with this!
  return weight_scale, learning_rate


def sgd(w, dw, config=None):
    """
    Performs vanilla stochastic gradient descent.
    config format:
    - learning_rate: Scalar learning rate.
    """
    if config is None: config = {}
    config.setdefault('learning_rate', 1e-2)

    w -= config['learning_rate'] * dw
    return w, config

def sgd_momentum(w, dw, config=None):
  """
  Performs stochastic gradient descent with momentum.
  config format:
  - learning_rate: Scalar learning rate.
  - momentum: Scalar between 0 and 1 giving the momentum value.
    Setting momentum = 0 reduces to sgd.
  - velocity: A numpy array of the same shape as w and dw used to store a
    moving average of the gradients.
  """
  if config is None: config = {}
  config.setdefault('learning_rate', 1e-2)
  config.setdefault('momentum', 0.9)
  v = config.get('velocity', torch.zeros_like(w))

  next_w = None
  mu = config['momentum']
  learning_rate = config['learning_rate']

  v = mu * v - learning_rate * dw # integrate velocity
  next_w = v + w # integrate position
  config['velocity'] = v

  return next_w, config

def rmsprop(w, dw, config=None):
  """
  Uses the RMSProp update rule, which uses a moving average of squared
  gradient values to set adaptive per-parameter learning rates.
  config format:
  - learning_rate: Scalar learning rate.
  - decay_rate: Scalar between 0 and 1 giving the decay rate for the squared
    gradient cache.
  - epsilon: Small scalar used for smoothing to avoid dividing by zero.
  - cache: Moving average of second moments of gradients.
  """
  if config is None: config = {}
  config.setdefault('learning_rate', 1e-2)
  config.setdefault('decay_rate', 0.99)
  config.setdefault('epsilon', 1e-8)
  config.setdefault('cache', torch.zeros_like(w))

  next_w = None

  config['cache'] = config['decay_rate'] * config['cache'] + (1 - config['decay_rate']) * dw.pow(2)
  next_w = w - config['learning_rate'] * dw / (torch.sqrt(config['cache']) + config['epsilon'])
  return next_w, config

def adam(w, dw, config=None):
  """
  Uses the Adam update rule, which incorporates moving averages of both the
  gradient and its square and a bias correction term.
  config format:
  - learning_rate: Scalar learning rate.
  - beta1: Decay rate for moving average of first moment of gradient.
  - beta2: Decay rate for moving average of second moment of gradient.
  - epsilon: Small scalar used for smoothing to avoid dividing by zero.
  - m: Moving average of gradient.
  - v: Moving average of squared gradient.
  - t: Iteration number.
  """
  if config is None: config = {}
  config.setdefault('learning_rate', 1e-3)
  config.setdefault('beta1', 0.9)
  config.setdefault('beta2', 0.999)
  config.setdefault('epsilon', 1e-8)
  config.setdefault('m', torch.zeros_like(w))
  config.setdefault('v', torch.zeros_like(w))
  config.setdefault('t', 0)

  next_w = None
  config['t'] = config['t'] + 1
  config['m'] = config['beta1']*config['m'] + (1-config['beta1'])*dw
  config['v'] = config['beta2']*config['v'] + (1-config['beta2'])*(dw.pow(2))
  mt = config['m'] / (1-(config['beta1']**config['t']))
  vt = config['v'] / (1-(config['beta2']**config['t']))
  next_w = w - (config['learning_rate'] * mt) / (torch.sqrt(vt) + config['epsilon'])
  return next_w, config


