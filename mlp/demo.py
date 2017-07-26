# -*- coding: utf-8 -*-
"""
Created on Thu May 11 04:53:59 2017

@author: kevin
"""
import mlp as mlp
import numpy as np

ver1_nl = np.array([16,100,100,10])
ver2_nl = np.array([16,100,100,10])
ver3_nl = np.array([16,100,100,10])
ver4_nl = np.array([16,100,100,10])
ver5_nl = np.array([16,100,10])

ver1_alpha = 0.0085 
ver2_alpha = 0.0085 
ver3_alpha = 0.0085 
ver4_alpha = 0.0075 
ver5_alpha = 0.0085

ver1_batch = 1 
ver2_batch = 2 
ver3_batch = 6 
ver4_batch = 1 
ver5_batch = 1

ver1_epoch = 18 
ver2_epoch = 19 
ver3_epoch = 20 
ver4_epoch = 12 
ver5_epoch = 13

mlp.train(ver1_nl, ver1_epoch, ver1_batch, ver1_alpha)
v1_cm = mlp.confusion_matrix(ver1_nl) 
mlp.cm_display(v1_cm)
v1_acc = mlp.accuracy(v1_cm)

mlp.train(ver2_nl, ver2_epoch, ver2_batch, ver2_alpha)
v2_cm = mlp.confusion_matrix(ver2_nl) 
mlp.cm_display(v2_cm)
v2_acc = mlp.accuracy(v2_cm)

mlp.train(ver3_nl, ver3_epoch, ver3_batch, ver3_alpha)
v3_cm = mlp.confusion_matrix(ver3_nl) 
mlp.cm_display(v3_cm)
v3_acc = mlp.accuracy(v3_cm)

mlp.train(ver4_nl, ver4_epoch, ver4_batch, ver4_alpha)
v4_cm = mlp.confusion_matrix(ver4_nl) 
mlp.cm_display(v4_cm)
v4_acc = mlp.accuracy(v4_cm)

mlp.train(ver5_nl, ver5_epoch, ver5_batch, ver5_alpha)
v5_cm = mlp.confusion_matrix(ver5_nl) 
mlp.cm_display(v5_cm)
v5_acc = mlp.accuracy(v5_cm)

acc = np.array([v1_acc,v2_acc,v3_acc,v4_acc,v5_acc])
print("                         accuracy\n")
print("version ", acc)