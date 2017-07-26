# -*- coding: utf-8 -*-
"""
@author: 410221023
"""
import tensorflow as tf
import rnn as rnn

def basic_rnn_demo():
    sess, x, y ,pred= rnn.train(training_iters = 500)
    rnn.prediction(sess, x, y, pred )
    sess.close()

def lstm_rnn_demo():
    sess, x, y ,pred= rnn.train(training_iters = 500,use_lstm=True)
    rnn.prediction(sess, x, y, pred )
    sess.close()

with tf.variable_scope("basic"):
    basic_rnn_demo()

with tf.variable_scope("lstm"):
    lstm_rnn_demo()