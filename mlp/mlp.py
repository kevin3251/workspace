# -*- coding: utf-8 -*-


import numpy as np
import sys
#numbers of neurons in layers
nl = np.array([16, 100, 100, 10])

def init(nl):
    weights = []
    biases = []
    for l in range(1 , nl.size):
        w = np.random.uniform(-0.5, 0.5, nl[l-1] * nl[l]).reshape(nl[l],nl[l-1])
        #b = np.random.uniform(-1.0, 1.0, nl[l]).reshape(nl[l],1)
        b = np.ones(nl[l]).reshape(nl[l],1)
        weights.append(w)
        biases.append(b)
    return weights,biases

def sigmoid(z):
    return np.tanh(z)

def deri_sigmoid(z):
    return 1 - sigmoid(z)**2
                       
def feedforward(x, ws, bs, nl_size):
    a_layer = [x]
    z_layer = []
    for l in range(nl_size-1):
        z =  np.dot(ws[l],a_layer[l]) + bs[l]
        z_layer.append(z)
        next_a = sigmoid(z)
        a_layer.append(next_a)
    return a_layer,z_layer

def output_error(last_z, a, target):
    z = np.copy(last_z)
    fn = deri_sigmoid(z).reshape(z.size)
    fn = np.diag(fn)
    target -= a.reshape(a.size)
    error = -2 * np.dot(fn,target)
    return error

def back_error(error, ws, zs, nl_size):
    es = [error]
    for l in range(nl_size-1, 1, -1):
        fn = deri_sigmoid(zs[l-1]).reshape(zs[l-1].size)
        fn = np.diag(fn)
        e = np.dot(ws[l-1].T, fn)
        e = np.dot(e, es[0])
        es.insert(0, e)
    return es

def save(weights, biases,nl_size):
    ws = open("weight.npy", "wb")
    bs = open("bias.npy", "wb")
    for l in range(nl_size-1):
        np.save( ws , weights[l])
        np.save( bs , biases[l])
    ws.close()
    bs.close()

def x_norm(x):
    min = x.min()
    max = x.max()
    norm_x = (x - min)/(max - min)
    return norm_x
        
def fit(nl , batch, train_set, target_set, weights, biases ,alpha):
    data_size = train_set.size/16
    count = 0
    delta_es = [0] * (nl.size-1)
    index = np.arange(target_set.size)
    np.random.shuffle(index)
    
    while count < data_size:
        idx = index[count]
        x = x_norm(train_set[idx:idx+1].T)
        t = np.zeros(10)
        ans = int(target_set[idx:idx+1])
        t[ans] =1
        a_layer,z_layer = feedforward(x, weights, biases, nl.size)
        
        error = output_error(z_layer[nl.size - 2], a_layer[nl.size-1], t)
        es = back_error(error, weights, z_layer, nl.size)
        
        for l in range(nl.size-1):
            delta_es[l] += es[l]
        
        count += 1
        
        if count % batch == 0 or count == data_size:
            for l in range(nl.size-1):
                delta_es[l] /= batch
                        
            for l in range(nl.size-1, 0, -1):
                e = delta_es[l-1].reshape(delta_es[l-1].size,1)
                delta_w =  np.dot(e, a_layer[l-1].T)
                weights[l-1] -= (alpha * delta_w)
                biases[l-1] -= (alpha * e)
            delta_es = [0] * (nl.size-1)

         
def train(nl, epoch = 1, batch =1 ,alpha =0.0085):
    train_set = np.loadtxt('in_train.txt')
    target_set = np.loadtxt('out_train.txt')
    weights,biases = init(nl)
    for i in range(epoch):
        #a = alpha/(2**i)
        a =alpha * batch * (0.8**i)
        fit(nl, batch, train_set, target_set, weights, biases, a)
    save(weights, biases, nl.size)

    
def predict(nl):
    test_set = np.loadtxt('in_test.txt')
    target_set = np.loadtxt('out_test.txt') 
    weights = []
    biases = []
    ws = open("weight.npy", "rb")
    bs = open("bias.npy", "rb")
    for l in range(nl.size-1):
        w = np.load(ws)
        b = np.load(bs)
        weights.append(w)
        biases.append(b)
    ws.close()
    bs.close()
    
    count = 0
    same = 0
    data_size = test_set.size/16
    while count < data_size:
        x = x_norm(test_set[count:count+1].T)
        t = target_set[count:count+1]
        a_layer,z_layer = feedforward(x, weights, biases, nl.size)
        y = np.argmax(a_layer[nl.size-1],axis=0)
        if t==y:
            same += 1
            
        count += 1
    
    print(same,count,'\n')
    print(format(same/count,'.2%'))
    return same/count

def confusion_matrix(nl):
    test_set = np.loadtxt('in_test.txt')
    target_set = np.loadtxt('out_test.txt') 
    weights = []
    biases = []
    ws = open("weight.npy", "rb")
    bs = open("bias.npy", "rb")
    for l in range(nl.size-1):
        w = np.load(ws)
        b = np.load(bs)
        weights.append(w)
        biases.append(b)
    ws.close()
    bs.close()
    
    count = 0
    data_size = test_set.size/16
    cm = np.zeros(100).reshape(10,10)
    
    while count < data_size:
        x = x_norm(test_set[count:count+1].T)
        t = target_set[count:count+1]
        a_layer,z_layer = feedforward(x, weights, biases, nl.size)
        y = np.argmax(a_layer[nl.size-1],axis=0)
        cm[int(t)][int(y)] += 1
            
        count += 1
    
    return cm    

def cm_display(cm):
    print("                  predict\n")
    print("        0,    1,    2,    3,    4,    5,    6,    7,    8,    9\n")
    col = "  actual  "
    t_num = "0123456789"           
    for i in range(10):
        print(col[i], t_num[i],cm[i])

def accuracy(cm):
    cnt = 0.0
    for i in range(10):
        for j in range(10):
            if i != j:
                cnt += cm[i][j]
    
    return 1 - cnt/np.sum(cm)