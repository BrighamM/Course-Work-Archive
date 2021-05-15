#/usr/bin/python

from ann import *
import numpy as np
import sys
import scipy as sp
import matplotlib.pyplot as plt
from mnist_loader import load_data_wrapper

DIR_PATH = './AllDaNets/'

train_d, valid_d, test_d = load_data_wrapper()

##########################
# Brigham Michaelis
# A00364835
# Write your code at the end of
# this file in the provided
# function stubs.
##########################

def main():
    regArr = [.5, 1.5]
    etaArr = [.1, 2.5]
    for eachRegVal in regArr:
        for eachEtaVal in etaArr:
            print("================================================= BEGIN =================================================")
            print("REG: " + str(eachRegVal) + " @@@  " + "ETA: " + str(eachEtaVal))
            collect_1_hidden_layer_net_stats(30, 100,
                                             CrossEntropyCost,
                                             30, 10, eachEtaVal, eachRegVal,
                                             train_d, test_d, saveAllNets=True, stepValue=70)
            collect_2_hidden_layer_net_stats(30, 100,
                                             CrossEntropyCost,
                                             30, 10, eachEtaVal, eachRegVal,
                                             train_d, test_d, saveAllNets=True, stepValue=70)
            collect_3_hidden_layer_net_stats(30, 100,
                                             CrossEntropyCost,
                                             30, 10, eachEtaVal, eachRegVal,
                                             train_d, test_d, saveAllNets=True, stepValue=70)
            print("================================================== END ==================================================")
    print("Terminated!!!!! you are done!")

#### Libraries

#### auxiliary functions
def load(filename):
    """Load a neural network from the file ``filename``.  Returns an
    instance of ann.

    """
    f = open(filename, "r")
    data = json.load(f)
    f.close()
    cost = getattr(sys.modules[__name__], data["cost"])
    net = ann(data["sizes"], cost=cost)
    net.weights = [np.array(w) for w in data["weights"]]
    net.biases = [np.array(b) for b in data["biases"]]
    return net

#### plotting costs and accuracies
def plot_costs(eval_costs, train_costs, num_epochs):
    plt.title('Evaluation Cost (EC) and Training Cost (TC)')
    plt.xlabel('Epoch')
    plt.ylabel('Cost')
    epochs = [i for i in range(num_epochs)]
    plt.plot(epochs, eval_costs, label='EC', c='g')
    plt.plot(epochs, train_costs, label='TC', c='b')
    plt.grid()    
    plt.autoscale(tight=True)
    plt.legend(loc='best')
    plt.show()

def plot_accuracies(eval_accs, train_accs, num_epochs):
    plt.title('Evaluation Acc (EA) and Training Acc (TC)')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    epochs = [i for i in range(num_epochs)]
    plt.plot(epochs, eval_accs, label='EA', c='g')
    plt.plot(epochs, train_accs, label='TA', c='b')
    plt.grid()
    plt.autoscale(tight=True)
    plt.legend(loc='best')    
    plt.show()

def collect_1_hidden_layer_net_stats(lower_num_hidden_nodes,
                                     upper_num_hidden_nodes,
                                     cost_function,
                                     num_epochs,
                                     mbs,
                                     eta,
                                     lmbda,
                                     train_data,
                                     eval_data,
                                     saveAllNets = False,
                                     stepValue = 1):
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Starting Func 1 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    returnDict = {}
    highestEvaluationAccuracy = 0
    currBestNet = ()
    for hls in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
        currentNet = ann([784, hls, 10], cost=cost_function)
        net_stats = currentNet.mini_batch_sgd(train_data, num_epochs, mbs, eta, lmbda,
                                        evaluation_data=eval_data,
                                        monitor_evaluation_cost=True,
                                        monitor_evaluation_accuracy=True,
                                        monitor_training_cost=True,
                                        monitor_training_accuracy=True)
        eCost = net_stats[0][-1]
        eAcc = net_stats[1][-1]
        tCost = net_stats[2][-1]
        tAcc = net_stats[3][-1]
        fileName = "784_" + str(hls) + "_10_~epochs_" + str(num_epochs) + "_~mbs_" + str(mbs) + "_~eta_" + str(int(eta*10)) + "_~lmbda_" + str(int(lmbda*10))
        print("##############################################################################")
        print("#")
        print("# STAT OUTPUT FOR: " + str(fileName))
        print("# Final Evaluatation Cost   : " + str(eCost))
        print("# Final Evaluation Accuracy : " + str(eAcc))
        print("# Final Training Cost       : " + str(tCost))
        print("# Final Training Accuracy   : " + str(tAcc))
        print("#")
        print("##############################################################################\n")
        
        if saveAllNets:
            currentNet.save("./AllDaNets/" + fileName + ".json")
        returnDict.setdefault(hls, net_stats)
        currEvalAccuracy = net_stats[1][-1]
        if currEvalAccuracy > highestEvaluationAccuracy:
            highestEvaluationAccuracy = currEvalAccuracy
            currBestNet = currentNet
    currBestNet.save("./persisted_nets/net1.json")
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Ending Func 1 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    return returnDict



def collect_2_hidden_layer_net_stats(lower_num_hidden_nodes,
                                     upper_num_hidden_nodes,
                                     cost_function,
                                     num_epochs,
                                     mbs,
                                     eta,
                                     lmbda,
                                     train_data,
                                     eval_data,
                                     saveAllNets = False,
                                     stepValue = 1):
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Starting Func 2 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    returnDict = {}
    highestEvaluationAccuracy = 0
    currBestNet = ()
    for hlsFirst in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
        for hlsSecond in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
            currentNet = ann([784, hlsFirst, hlsSecond, 10], cost=cost_function)
            net_stats = currentNet.mini_batch_sgd(train_data, num_epochs, mbs, eta, lmbda,
                                        evaluation_data=eval_data,
                                        monitor_evaluation_cost=True,
                                        monitor_evaluation_accuracy=True,
                                        monitor_training_cost=True,
                                        monitor_training_accuracy=True)

            eCost = net_stats[0][-1]
            eAcc = net_stats[1][-1]
            tCost = net_stats[2][-1]
            tAcc = net_stats[3][-1]
            fileName = "784_" + str(hlsFirst) + "_" + str(hlsSecond) + "_10_~epochs_" + str(num_epochs) + "_~mbs_" + str(mbs) + "_~eta_" + str(int(eta*10)) + "_~lmbda_" + str(int(lmbda*10))
            print("##############################################################################")
            print("#")
            print("# STAT OUTPUT FOR: " + str(fileName))
            print("# Final Evaluatation Cost   : " + str(eCost))
            print("# Final Evaluation Accuracy : " + str(eAcc))
            print("# Final Training Cost       : " + str(tCost))
            print("# Final Training Accuracy   : " + str(tAcc))
            print("#")
            print("##############################################################################\n")
            if saveAllNets:
                currentNet.save("./AllDaNets/" + fileName + ".json")
            keyString = str(hlsFirst) + "_" + str(hlsSecond)
            returnDict.setdefault(keyString, net_stats)
            currEvalAccuracy = net_stats[1][-1]
            if currEvalAccuracy > highestEvaluationAccuracy:
                highestEvaluationAccuracy = currEvalAccuracy
                currBestNet = currentNet
    currBestNet.save("./persisted_nets/net2.json")
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Ending Func 2 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    return returnDict
    

def collect_3_hidden_layer_net_stats(lower_num_hidden_nodes,
                                     upper_num_hidden_nodes,
                                     cost_function,
                                     num_epochs,
                                     mbs,
                                     eta,
                                     lmbda,
                                     train_data,
                                     eval_data,
                                     saveAllNets = False,
                                     stepValue = 1):
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Starting Func 3 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    print("TRAINING: ")
    returnDict = {}
    highestEvaluationAccuracy = 0
    currBestNet = ()
    for hlsFirst in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
        for hlsSecond in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
            for hlsThird in range(lower_num_hidden_nodes, upper_num_hidden_nodes + 1, stepValue):
                currentNet = ann([784, hlsFirst, hlsSecond, hlsThird, 10], cost=cost_function)
                net_stats = currentNet.mini_batch_sgd(train_data, num_epochs, mbs, eta, lmbda,
                                            evaluation_data=eval_data,
                                            monitor_evaluation_cost=True,
                                            monitor_evaluation_accuracy=True,
                                            monitor_training_cost=True,
                                            monitor_training_accuracy=True)

                eCost = net_stats[0][-1]
                eAcc = net_stats[1][-1]
                tCost = net_stats[2][-1]
                tAcc = net_stats[3][-1]
                fileName = "784_" + str(hlsFirst) + "_" + str(hlsSecond) + "_ " + str(hlsThird) + "_10_~epochs_" + str(num_epochs) + "_~mbs_" + str(mbs) + "_~eta_" + str(int(eta*10)) + "_~lmbda_" + str(int(lmbda*10))
                print("##############################################################################")
                print("#")
                print("# STAT OUTPUT FOR: " + str(fileName))
                print("# Final Evaluatation Cost   : " + str(eCost))
                print("# Final Evaluation Accuracy : " + str(eAcc))
                print("# Final Training Cost       : " + str(tCost))
                print("# Final Training Accuracy   : " + str(tAcc))
                print("#")
                print("##############################################################################\n")
                if saveAllNets:
                    currentNet.save("./AllDaNets/" + fileName + ".json")
                keyString = str(hlsFirst) + "_" + str(hlsSecond) + "_" + str(hlsThird)
                returnDict.setdefault(keyString, net_stats)
                currEvalAccuracy = net_stats[1][-1]
                if currEvalAccuracy > highestEvaluationAccuracy:
                    highestEvaluationAccuracy = currEvalAccuracy
                    currBestNet = currentNet
    currBestNet.save("./persisted_nets/net3.json")
    print("\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Ending Func 3 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&")
    print("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n")
    return returnDict

if __name__ == "__main__":
    main()





# OUTPUT REPORT
'''
Here are the stats for my 3 "Best" Nets,
Please note that I took into account Accuracies and Costs
So I picked the highest accuracies possible for a given net architecture and 
then I looked at the kinds of cost reductions that could be achieved by giving up 
a little bit of accuracy
For example if I saw a 3% reduction in accuracy correspond to a 300 percent reduction in cost
I reported the net with the lower cost in that instance.

NET 1 
##############################################################################
#
# STAT OUTPUT FOR: 784_100_10_~epochs_30_~mbs_10_~eta_1_~lmbda_5
# ETA VALUE: .1
# LAMBDA VALUE: .5
# Final Evaluatation Cost   : 1.8130536893145976
# Final Evaluation Accuracy : 0.9612
# Final Training Cost       : 0.42293125390364494
# Final Training Accuracy   : 0.98816
#
##############################################################################

NET2
##############################################################################
#
# STAT OUTPUT FOR: 784_30_30_10_~epochs_30_~mbs_10_~eta_1_~lmbda_5
# ETA VALUE: .1
# LAMBDA VALUE: .5
# Final Evaluatation Cost   : 0.8356911935659337
# Final Evaluation Accuracy : 0.9531
# Final Training Cost       : 0.2682885804066206
# Final Training Accuracy   : 0.97698
#
##############################################################################

NET3
##############################################################################
#
# STAT OUTPUT FOR: 784_30_30_100_10_~epochs_30_~mbs_10_~eta_1_~lmbda_5
# ETA VALUE: .1
# LAMBDA VALUE: .5
# Final Evaluatation Cost   : 0.9279123223081149
# Final Evaluation Accuracy : 0.9536
# Final Training Cost       : 0.25922709103835423
# Final Training Accuracy   : 0.97934
#
##############################################################################


'''