#/usr/bin/python

############################
# Module: cs5600_6600_f20_hw03.py
# Your name
# Your A#
############################

from ann import ann
from mnist_loader import load_data_wrapper
import random
import os
import pickle as cPickle
import numpy as np

def save(obj, file_name):
    with open(file_name, 'wb') as fp:
        cPickle.dump(obj, fp)

def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = cPickle.load(fp)
    return obj

# load training, validation, and testing MNIST data
train_d, valid_d, test_d = load_data_wrapper()

def main():
    # train_1_hidden_layer_anns()
    # train_2_hidden_layer_anns()
    train_nets(networks, eta_vals, mini_batch_sizes, 50, path)
    # load_nets(path)
    # evaluate_net_ensemble(networks, valid_d)



def train_1_hidden_layer_anns(lwr=10, upr=50, eta=0.25, mini_batch_size=10, num_epochs=2):
    ## your code here
    # But we also need to vary the learning rate.
    print("\nBEGIN TRAIN 1 DATA")
    etaArray = [.25, .5, 1.0, 1.5, 2.0]
    for hlsSize in range(lwr, upr + 1, 10):
        print("\n*********** HLS = " + str(hlsSize) + " ***********\n")
        for etaVal in etaArray:
            netnn = ann([784, hlsSize, 10])
            netnn.mini_batch_sgd(train_d, num_epochs, mini_batch_size, etaVal, test_data=test_d)
            print("==== ETA : " + str(etaVal) + "\n")
        print("*********** HLS = " + str(hlsSize) + " ***********\n")
    print("END TRAIN 1 DATA\n")
            
    

def train_2_hidden_layer_anns(lwr=10, upr=50, eta=0.25, mini_batch_size=10, num_epochs=1):
    ## your code here
    print("\nBEGIN TRAIN 2 DATA")
    for hlsOneSize in range(lwr, upr + 1, 10):
        print("\n*********** BEGIN 1st HLS = " + str(hlsOneSize) + " ***********\n")
        etaArray = [.25, .5, 1.0, 1.5, 2.0]
        for hlsTwoSize in range(lwr, upr + 1, 10):
            print("\n*********** BEGIN 2nd HLS = " + str(hlsTwoSize) + " ***********\n")
            for etaVal in etaArray:
                netnn = ann([784, hlsOneSize, hlsTwoSize, 10])
                netnn.mini_batch_sgd(train_d, num_epochs, mini_batch_size, etaVal, test_data=test_d)
                print("==== ETA : " + str(etaVal) + "\n")
            print("*********** END 2nd HLS = " + str(hlsTwoSize) + " ***********\n")
        print("*********** END 1st HLS = " + str(hlsOneSize) + " ***********\n")
    print("END TRAIN 2 DATA\n")



# define your networks
net1 = ann([784, 10, 10])
net2 = ann([784,   10, 10, 10])
net3 = ann([784,   20, 20, 10])
net4 = ann([784,   40, 40, 40, 10])
net5 = ann([784,   80, 80, 80, 80, 10])

# define an ensemble of 5 nets
networks = (net1, net2, net3, net4, net5)
eta_vals = (0.1, 0.25, 0.3, 0.4, 0.5)
mini_batch_sizes = (5, 10, 15, 20)
path = "./pck_nets/"

# train networks
def train_nets(networks, eta_vals, mini_batch_sizes, num_epochs, path):
    
    for network in networks:
        randomEtaVal = random.choice(eta_vals)
        randomBatchSize = random.choice(mini_batch_sizes)
        network.mini_batch_sgd(train_d,num_epochs,randomBatchSize,randomEtaVal,test_d)
        fileName = ""
        fileName += "_" + str(int(randomEtaVal*100))
        fileName += "_" + str(randomBatchSize)
        fileName += ".pck"
        sizeName = "net"
        for val in network.sizes:
            sizeName += "_" + str(val)
        fullFileName = path + sizeName + fileName
        save(network, fullFileName)


def load_nets(path):
    pckFiles = getSubFilesList(path)
    returnTupleList = []
    for pckFile in pckFiles:
        filePath = os.path.join(path, pckFile)
        returnTupleList.append([str(pckFile), load(filePath)])
    return returnTupleList

# evaluate net ensemble.
def evaluate_net_ensemble(net_ensemble, test_data):
    # your code here
    # for piece in test_data:
    #     print(str(piece[1]))
    for net in net_ensemble:
        result = net.feedforward(test_data[0][0])
        # We have 10000 test images, test_data[0][0] is the actual image
        # test_data[0][1] is the ground truth
        print(str(np.argmax(result)) + " vs " + str(test_data[0][1]))

        # print(str(result) + " vs " + str(test_data[1][0]))
        # print(str(net.feedforward(test_data[0])))

    # pass

def getSubDirsList(pathname):
    return [d for d in os.listdir(pathname) if not os.path.isfile(os.path.join(pathname, d))]

def getSubFilesList(pathname):
    return [d for d in os.listdir(pathname) if os.path.isfile(os.path.join(pathname, d))]


if __name__  == "__main__":
    main()



