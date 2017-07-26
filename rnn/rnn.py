# -*- coding: utf-8 -*-
"""
@author: 410221023
"""
import tensorflow as tf
import tensorflow.contrib.rnn as rnn
import numpy as np
import matplotlib.pyplot as plt

def load_data():
    data_x = np.loadtxt('in_train.txt')
    data_y = np.loadtxt('out_train.txt')
    return data_x,data_y

#normalize input data 
def norm_x(x):
    x_min =  x.min()
    x_max = x.max()
    norm_x = (x - x_min)/(x_max - x_min)
    return norm_x

# generate next batch data
def get_batch(data_x, data_y):
    batch_size = data_y.size
    batch_x = np.zeros(batch_size * 16).reshape(batch_size, 16)
    batch_y = np.zeros(batch_size*10).reshape(batch_size, 10)
    index = np.arange(data_y.size)
    np.random.shuffle(index)
    for i  in range(batch_size):
        idx  = index[i]
        batch_x[i] = norm_x(data_x[idx])
        batch_y[i][int(data_y[idx])] = 1
    ###  shape = batch_size * steps * inputs
    return batch_x.reshape(batch_size,  8, 2), batch_y

#define RNN structure
def RNN(x, w, b, n_steps, n_neurons,use_lstm):
    x_seqs = tf.unstack(tf.transpose(x , perm = [1, 0, 2] ))    
    if use_lstm == True:
        cell =  rnn.BasicLSTMCell(num_units  =  n_neurons, forget_bias = 0.5)   
    else :
        cell =  rnn.BasicRNNCell(num_units  =  n_neurons)    
    outputs,  states =  rnn.static_rnn(cell, x_seqs, dtype = tf.float32)
    return tf.tanh( tf.matmul(outputs[-1], w) + b)

#set weight and bias
def get_weight_and_bias(n_neurons,n_classes):
    with tf.variable_scope("weight"):
        w  =tf.get_variable("w",[n_neurons, n_classes], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    with tf.variable_scope("bias"):
        b =  tf.get_variable("b",[n_classes],initializer = tf.ones_initializer(),dtype = tf.float32)    
    return w,b

def train( n_inputs = 2, n_steps = 8, n_neurons = 100, n_classes = 10, lr = 0.001,training_iters = 200,use_lstm= False):    
    x = tf.placeholder(tf.float32, [None, n_steps, n_inputs])
    y = tf.placeholder(tf.float32, [None, n_classes])
    weights,biases = get_weight_and_bias(n_neurons,n_classes)
    data_x, data_y = load_data() 
    pred = RNN(x, weights, biases,n_steps, n_neurons, use_lstm)
    
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=pred, labels =y))
    optimizer = tf.train.AdamOptimizer(learning_rate=lr).minimize(cost)
    
    # Evaluate model
    correct_pred = tf.equal(tf.argmax(pred,1), tf.argmax(y,1))
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

    # Initializing the variables
    init = tf.global_variables_initializer()
    sess = tf.InteractiveSession() 
    sess.run(init)
    
    step = 0
    while step < training_iters:
        batch_x, batch_y = get_batch(data_x,data_y)
        sess.run(optimizer, feed_dict={x: batch_x, y: batch_y} )
        
        if step % 20 == 0:
            acc = sess.run(accuracy, feed_dict={x: batch_x, y: batch_y})
            loss = sess.run(cost, feed_dict={x: batch_x, y: batch_y} )
            print( "Iter " + str(step) + ", Minibatch Loss= " + \
                         "{:.6f}".format(loss) + ", Training Accuracy= " + \
                         "{:.5f}".format(acc))
        
        step += 1
    print ("Optimization Finished!")
    return sess,x, y, pred

#display sonfusion matrix
def cm_display(cm):
    mat = np.array(cm, dtype = np.int32)
    temp = np.zeros(10*10).reshape(10,10)
    for i in range(10) :
        temp[i] = mat[i]/ np.sum(mat[i])
    
    fig = plt.figure()
    plt.clf()
    ax = fig.add_subplot(111)
    ax.set_aspect(1)
    res = ax.imshow(temp, cmap=plt.cm.Wistia, 
                interpolation='nearest')
    for x in range(10):
        for y in range(10):
            ax.annotate(str(mat[x][y]), xy=(y, x), 
                                      horizontalalignment='center',
                                      verticalalignment='center')
    fig.colorbar(res)
    plt.xticks(np.arange(10), ['0', '1', '2', '3', '4', '5','6', '7', '8', '9'])
    plt.yticks(np.arange(10), ['0', '1', '2', '3', '4', '5','6', '7', '8', '9'])
    plt.show()
    plt.close()
       
def prediction(sess, x, y, pred ):
    data_x = np.loadtxt('in_test.txt')
    data_y = np.loadtxt('out_test.txt')
    test_x = np.zeros(data_y.size * 16).reshape(data_y.size, 16)
    test_y = np.zeros(data_y.size *10).reshape(data_y.size , 10)
    for i  in range(data_y.size):
        test_x[i] = norm_x(data_x[i])
        test_y[i][int(data_y[i])] = 1
    test_x = test_x.reshape(data_y.size,  8, 2)
    
    # Evaluate model
    labels = sess.run(tf.argmax(pred,1),feed_dict={x: test_x, y: test_y})
    predictions = sess.run(tf.argmax(y,1),feed_dict={x: test_x, y: test_y})
    correct_pred = tf.equal(labels, predictions)
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
    
    acc = sess.run(accuracy, feed_dict={x: test_x, y: test_y})
    print(  "Test Accuracy= " + "{:.5f}".format(acc))
    confusion_matrix = tf.confusion_matrix(labels,predictions,num_classes=10)
    cm = sess.run(confusion_matrix)
    cm_display(cm)
