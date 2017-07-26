# -*- coding: utf-8 -*-
import numpy as np
import cv2
import os
import tensorflow as tf
import matplotlib.pyplot as plt

def enumerate_files(dirs, path='All_gray_1_32_32/', n_poses=3, n_samples=20):
    file_names = []
    targets = []
    for p in dirs:
        for n in range(n_poses):
            for j in range(3):
                dir_name = path + p + '/000' + str(n*3+j)  + '/'
                for s in range(n_samples):
                    d = dir_name + '%04d/' % s
                    for f in os.listdir(d):
                        if f.endswith('jpg'):
                            file_names += [d + f]
                            targets.append(n)
    return file_names, targets

def read_image(files):
    imgs = []
    for file in files:
        img = cv2.imread(file, cv2.IMREAD_GRAYSCALE) / 255.0
        imgs.append(img)
    return imgs

def conv2d(img, w, b):
    return tf.nn.relu(tf.nn.bias_add(tf.nn.conv2d(img, w, strides = [1,1,1,1], padding = 'SAME'),b))

def max_pooling(img, k):
    return tf.nn.max_pool(img, ksize = [1,k,k,1], strides = [1,k,k,1], padding ='SAME')

def model(n_classes = 3, lr = 0.001):
    x = tf.placeholder(tf.float32,[None, 32, 32])
    _X = tf.reshape(x, shape = [-1, 32, 32, 1])
    y = tf.placeholder(tf.float32,[None,n_classes])
    
    wc1 = tf.get_variable("wc1",[5,5,1,32], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    bc1 = tf.get_variable("bc1",[32],initializer = tf.zeros_initializer(),dtype = tf.float32)
    conv1 = conv2d(_X, wc1, bc1)
    conv1 = max_pooling(conv1, k = 2)
    keep_prob = tf.placeholder(tf.float32)
    conv1 = tf.nn.dropout(conv1, keep_prob)
    
    wc2 = tf.get_variable("wc2",[5,5,32,64], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    bc2 = tf.get_variable("bc2",[64],initializer = tf.zeros_initializer(),dtype = tf.float32)
    conv2 = conv2d(conv1, wc2, bc2)
    conv2 = max_pooling(conv2, k = 2)
    conv1 = tf.nn.dropout(conv2, keep_prob)
    
    wd = tf.get_variable("wd",[8*8*64,1024], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    bd = tf.get_variable("bd",[1024], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    dense = tf.reshape(conv2,[-1, wd.get_shape().as_list()[0]])
    dense = tf.nn.relu(tf.add(tf.matmul(dense,wd),bd))
    dense = tf.nn.dropout(dense, keep_prob)
    
    wout = tf.get_variable("wout",[1024,n_classes], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    bout = tf.get_variable("bout",[n_classes], initializer = tf.random_normal_initializer(), dtype= tf.float32)
    #pred = tf.nn.softmax(tf.nn.relu(tf.add(tf.matmul(dense,wout),bout)))
    pred = tf.add(tf.matmul(dense,wout),bout)
    
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=pred, labels=y))
    optimizer = tf.train.AdamOptimizer(learning_rate= lr).minimize(cost)
    correct_pred = tf.equal(tf.argmax(pred,1), tf.argmax(y,1))
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
    
    return x, y, pred, keep_prob, cost, optimizer, correct_pred, accuracy

def load_tr_data():
    train_sets = ['Set1','Set2','Set3']
    tr_filenames, tr_labels = enumerate_files(train_sets)
    tr_list_of_arrays = read_image(tr_filenames)
    tr_array = np.array(tr_list_of_arrays)
    tr_labels = np.array(tr_labels)
    return tr_array, tr_labels

def load_ts_data():
    test_sets = ['Set4','Set5']
    ts_filenames, ts_labels = enumerate_files(test_sets)
    ts_list_of_arrays = read_image(ts_filenames)
    ts_array = np.array(ts_list_of_arrays)
    ts_labels = np.array(ts_labels)
    batch_size = ts_labels.size
    batch_y = np.zeros(batch_size*3).reshape(batch_size, 3)
    for i  in range(batch_size):
        batch_y[i][int(ts_labels[i])] = 1
    return ts_array, batch_y
    
def next_batch(tr_array, tr_labels):
    batch_size = tr_labels.size
    batch_x = np.zeros_like(tr_array)
    batch_y = np.zeros(batch_size*3).reshape(batch_size, 3)
    index = np.arange(batch_size)
    np.random.shuffle(index)
    for i  in range(batch_size):
        idx  = index[i]
        batch_x[i] = tr_array[idx]
        batch_y[i][int(tr_labels[idx])] = 1
    return batch_x, batch_y


def train(tr_iters = 100000, display_step = 10, dropout = 0.7):
    x, y, pred, keep_prob, cost, optimizer, correct_pred, accuracy = model()
    
    init = tf.global_variables_initializer()
    saver = tf.train.Saver()
    sess = tf.InteractiveSession() 
    sess.run(init)
    
    tr_array, tr_labels= load_tr_data()
    batch_size = tr_labels.size
    
    step = 1
    while step * batch_size < tr_iters:
        batch_x, batch_y = next_batch(tr_array,tr_labels)
        sess.run(optimizer, feed_dict={x: batch_x, y: batch_y, keep_prob: dropout})
        if step % display_step == 0:
            acc = sess.run(accuracy, feed_dict={x:batch_x, y: batch_y, keep_prob: 1.})
            loss = sess.run(cost, feed_dict={x: batch_x, y: batch_y, keep_prob: 1.})
            print ("Iter " + str(step*batch_size) +", Minibatch Loss= " + "{:.6f}".format(loss) + ", Training Accuracy= " + "{:.5f}".format(acc))
        
        step += 1
        
    print("Optimization Finished")
    
    #ts_array, ts_labels = load_ts_data()
    #print ("Testing Accuracy:", sess.run(accuracy, feed_dict={x: ts_array, y: ts_labels, keep_prob: 1.}))
    
    save_path = saver.save(sess, "./model")
    print("Model saved in file: %s" % save_path)
    sess.close()

def test(is_trained = True):
    if is_trained == False:
        train()
    tf.reset_default_graph()
    with tf.Session() as sess:
        x, y, pred, keep_prob, cost, optimizer, correct_pred, accuracy = model()
        saver = tf.train.Saver()
        saver.restore(sess, tf.train.latest_checkpoint('./'))
            
        ts_array, ts_labels = load_ts_data()
        print ("Testing Accuracy:", sess.run(accuracy, feed_dict={x: ts_array, y: ts_labels, keep_prob: 1.}))
        confusion_matrix = tf.confusion_matrix(tf.argmax(pred,1), tf.argmax(y,1),num_classes=3)
        cm = sess.run(confusion_matrix , feed_dict={x: ts_array, y: ts_labels, keep_prob: 1.})
        cm_display(cm)

def cm_display(cm):
    mat = np.array(cm, dtype = np.int32)
    temp = np.zeros(3*3).reshape(3,3)
    for i in range(3) :
        temp[i] = mat[i]/ np.sum(mat[i])
    
    fig = plt.figure()
    plt.clf()
    ax = fig.add_subplot(111)
    ax.set_aspect(1)
    res = ax.imshow(temp, cmap=plt.cm.Wistia, 
                interpolation='nearest')
    for x in range(3):
        for y in range(3):
            ax.annotate(str(mat[x][y]), xy=(y, x), 
                                      horizontalalignment='center',
                                      verticalalignment='center')
    fig.colorbar(res)
    plt.xticks(np.arange(3), ['0', '1', '2'])
    plt.yticks(np.arange(3), ['0', '1', '2'])
    plt.show()
    plt.close()

