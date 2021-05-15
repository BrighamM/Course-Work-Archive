#/usr/bin/python

############################
# Module: cs5600_6600_f20_hw03.py
# Your name
# Your A#
############################

from ann import ann
from mnist_loader import load_data_wrapper
import random
import pickle as cPickle
import numpy as np

# load training, validation, and testing MNIST data
train_d, valid_d, test_d = load_data_wrapper()

def main():
    # train_1_hidden_layer_anns()
    train_2_hidden_layer_anns()



def train_1_hidden_layer_anns(lwr=10, upr=50, eta=0.25, mini_batch_size=10, num_epochs=50):
    ## your code here
    # But we also need to vary the learning rate.
    print("\nBEGIN TRAIN 1 DATA")
    etaArray = [2.0, 1.5, 1.0, .5, .25]
    for hlsSize in range(lwr, upr + 1, 10):
        print("\n*********** HLS = " + str(hlsSize) + " ***********\n")
        for etaVal in etaArray:
            netnn = ann([784, hlsSize, 10])
            netnn.mini_batch_sgd(train_d, num_epochs, mini_batch_size, etaVal, test_data=test_d)
            print("==== ETA : " + str(etaVal) + "\n")
        print("*********** HLS = " + str(hlsSize) + " ***********\n")
    print("END TRAIN 1 DATA\n")
            
    

def train_2_hidden_layer_anns(lwr=10, upr=50, eta=0.25, mini_batch_size=10, num_epochs=50):
    ## your code here
    print("\nBEGIN TRAIN 2 DATA")
    for hlsOneSize in range(lwr, upr + 1, 10):
        print("\n*********** BEGIN 1st HLS = " + str(hlsOneSize) + " ***********\n")
        etaArray = [2.0, 1.5, 1.0, .5, .25]
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
net1 = None
net2 = None
net3 = None
net4 = None
net5 = None

# define an ensemble of 5 nets
networks = (net1, net2, net3, net4, net5)
eta_vals = (0.1, 0.25, 0.3, 0.4, 0.5)
mini_batch_sizes = (5, 10, 15, 20)

# train networks
def train_nets(networks, eta_vals, mini_batch_sizes, num_epochs, path):
    # your code here
    pass

def load_nets(path):
    # your code here
    pass

# evaluate net ensemble.
def evaluate_net_ensemble(net_ensemble, test_data):
    # your code here
    pass




if __name__  == "__main__":
    main()



