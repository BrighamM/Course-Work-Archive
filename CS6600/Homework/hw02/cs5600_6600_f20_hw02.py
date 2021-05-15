#!/usr/bin/python

#########################################
# module: cs5600_6600_f20_hw02.py
# Brigham Michaelis
# A00364835
#########################################

import numpy as np
import pickle
import os
from cs5600_6600_f20_hw02_data import *

# sigmoid function and its derivative.
# you'll use them in the training and fitting
# functions below.
def sigmoidf(x):
    return 1 / (1 + np.exp(-x))

def sigmoidf_prime(x):
    # return np.exp(-x)/((1 + np.exp(-x))**2)
    return x * (1 - x)

# save() function to save the trained network to a file
def save(obj, file_name):
    with open(file_name, 'wb') as fp:
        pickle.dump(obj, fp)

# restore() function to restore the file
def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

def build_nn_wmats(mat_dims):
    returnMatrix = []
    for i in range(1, len(mat_dims)):
        returnMatrix.append(np.random.uniform(-1,1, (mat_dims[i-1], mat_dims[i])))
    return returnMatrix
    pass

def build_231_nn():
    return build_nn_wmats((2, 3, 1))

def build_2331_nn():
    return build_nn_wmats((2, 3, 3, 1))

def build_221_nn():
    return build_nn_wmats((2, 2, 1))

def build_838_nn():
    return build_nn_wmats((8, 3, 8))

def build_949_nn():
    return build_nn_wmats((9, 4, 9))

def build_4221_nn():
    return build_nn_wmats((4, 2, 2, 1))

def build_421_nn():
    return build_nn_wmats((4, 2, 1))

def build_121_nn():
    return build_nn_wmats((1, 2, 1))

def build_1221_nn():
    return build_nn_wmats((1, 2, 2, 1))

def train_3_layer_nn(numIters, X, y, build):
    W1, W2 = build()
    for j in range(numIters):
        # Feed Forward
        Z2 = np.dot(X, W1)
        a2 = sigmoidf(Z2)
        Z3 = np.dot(a2, W2)
        yHat = sigmoidf(Z3)
        # Back propagation
        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoidf_prime(yHat)
        a2_error = yHat_delta.dot(W2.T)
        a2_delta = a2_error * sigmoidf_prime(a2)
        W2 += a2.T.dot(yHat_delta)
        W1 += X.T.dot(a2_delta)

    return W1, W2



def train_4_layer_nn(numIters, X, y, build):
    W1, W2, W3 = build()
    for j in range(numIters):
        Z2 = np.dot(X, W1)
        a2 = sigmoidf(Z2)
        Z3 = np.dot(a2, W2)
        a3 = sigmoidf(Z3)
        Z4 = np.dot(a3, W3)
        yHat = sigmoidf(Z4)

        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoidf_prime(yHat)
        a3_error = yHat_delta.dot(W3.T)
        a3_delta = a3_error * sigmoidf_prime(a3)
        a2_error = a3_delta.dot(W2.T)
        a2_delta = a3_error * sigmoidf_prime(a2)

        W3 += a3.T.dot(yHat_delta)
        W2 += a2.T.dot(a3_delta)
        W1 += X.T.dot(a2_delta)

    return W1, W2, W3

def fit_3_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    Z2 = np.dot(x, wmats[0])
    a2 = sigmoidf(Z2)
    Z3 = np.dot(a2, wmats[1])
    yHat = sigmoidf(Z3)
    if thresh_flag:
        for element in range(len(yHat)):
            if yHat[element] > thresh:
                yHat[element] = 1
            else:
                yHat = 0
    return yHat

def fit_4_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    Z2 = np.dot(x, wmats[0])
    a2 = sigmoidf(Z2)
    Z3 = np.dot(a2, wmats[1])
    a3 = sigmoidf(Z3)
    Z4 = np.dot(a3, wmats[2])
    yHat = sigmoidf(Z4)
    if thresh_flag:
        for element in range(len(yHat)):
            if yHat[element] > thresh:
                yHat[element] = 1
            else:
                yHat = 0
    return yHat


def converge_train_n_layer_nn(X, y, build):
    print("\nTraining")
    weightLayers = build()
    absoluteErrorSum = 5
    totalIters = 0
    while absoluteErrorSum > .0005:
        totalIters += 1
        # Feed Forward...
        zValArray = [] # Z2 starts at index 0, Z3 at index 1 ...
        aValArray = [] # a2 starts at index 0, a3 at index 1 ... The last element in here is y_hat
        actvErrorArr = []
        actvErrorDeltaArr = []

        currentActivation = X
        aValArray.append(currentActivation)
        for i in range(0, len(weightLayers)):
            Zi = np.dot(currentActivation, weightLayers[i])
            zValArray.append(Zi)
            currentActivation = sigmoidf(Zi)
            aValArray.append(currentActivation)
        # Now aValArray contains yHat

        yHat = aValArray[-1]
        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoidf_prime(yHat)

        currentError = yHat_error
        actvErrorArr.append(currentError)

        currentDelta = yHat_delta
        actvErrorDeltaArr.append(currentDelta)
        for i in reversed(range(0, len(weightLayers))):
            currentError = currentDelta.dot(weightLayers[i].T)
            actvErrorArr.append(currentError)
            currentDelta = currentError * sigmoidf_prime(aValArray[i])
            actvErrorDeltaArr.append(currentDelta)
        
        # Now assign the weights...
        someSize = 0
        absoluteErrorSum = 0
        for i in reversed(range(0, len(weightLayers))):
            absoluteErrorSum += np.sum(np.absolute(aValArray[i].T.dot(actvErrorDeltaArr[someSize])))
            weightLayers[i] += aValArray[i].T.dot(actvErrorDeltaArr[someSize])
            someSize += 1
        if totalIters % 100000 == 0:
            print("Current Iterations: " + str(totalIters))
            print("Current Absolute Error: " + str(absoluteErrorSum) + "\n")
    print("Total Iterations: " + str(totalIters))
    print("Absolute Error: " + str(absoluteErrorSum) + "\n")
    return weightLayers


def fit_n_layer_nn():
    print("Fitting")
