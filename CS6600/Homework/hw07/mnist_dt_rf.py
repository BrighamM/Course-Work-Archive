'''
   *********** COMPARISON COMMENTS ***********

   DELIVERABLE #1 (The performance report and confusion matrix of my top performing DT;)
           0       0.91      0.94      0.93       980
           1       0.94      0.95      0.95      1135
           2       0.89      0.84      0.86      1032
           3       0.83      0.86      0.84      1010
           4       0.86      0.87      0.87       982
           5       0.81      0.82      0.82       892
           6       0.89      0.89      0.89       958
           7       0.90      0.90      0.90      1028
           8       0.83      0.79      0.81       974
           9       0.84      0.85      0.84      1009

    accuracy                           0.87     10000
   macro avg       0.87      0.87      0.87     10000
weighted avg       0.87      0.87      0.87     10000

[[ 920    1    4    3    7   15   13    6    5    6]
 [   0 1081    6   14    2    6    5    7   11    3]
 [   7   13  863   38   21   13   12   31   20   14]
 [   8    2   25  866    4   40    4    9   27   25]
 [   6    5   10    6  856   12   22   10   20   35]
 [  16   10    4   42   14  732   24   10   20   20]
 [  18    6   11    8   18   23  850    2   20    2]
 [   2   13   20   18   12    7    2  926    5   23]
 [  16   12   26   28   20   35   22   12  765   38]
 [  13    6    6   23   38   17    5   19   26  856]]

    DELIVERABLE #2 (The performance report and confusion matrix of your top performing RF. Be sure to specify the number of DTs in your RF;)
################## RF SIZE = 100
              precision    recall  f1-score   support

           0       0.97      0.99      0.98       980
           1       0.99      0.99      0.99      1135
           2       0.96      0.97      0.97      1032
           3       0.95      0.96      0.96      1010
           4       0.97      0.97      0.97       982
           5       0.96      0.95      0.96       892
           6       0.97      0.98      0.98       958
           7       0.97      0.96      0.97      1028
           8       0.97      0.95      0.96       974
           9       0.96      0.95      0.95      1009

    accuracy                           0.97     10000
   macro avg       0.97      0.97      0.97     10000
weighted avg       0.97      0.97      0.97     10000

[[ 970    0    1    0    0    3    2    1    2    1]
 [   0 1123    1    4    0    2    2    1    2    0]
 [   5    0 1001    6    2    0    4    8    6    0]
 [   0    0    9  973    0    8    0    9    8    3]
 [   1    0    1    0  956    0    5    0    2   17]
 [   5    2    1   18    3  848    6    2    5    2]
 [   8    3    0    0    3    4  938    0    2    0]
 [   1    2   18    3    2    0    0  991    2    9]
 [   4    0    5    9    6    5    6    3  926   10]
 [   6    6    1    9   11    9    1    5    4  957]]

    DELIVERABLE #3 (Your brief answer to the question: Do you think that ensemble learning makes a difference in going from single DTs to RFs?)
    MY RESPONSE:
    Yes I do see a difference in going from one DT to a forest of DTS, yet only to a point. My results quickly tapered off after using about 
    60 DTS in my forest. Such that my accuracy started around 87% and steadily improved to 97% and never improved after that. (ABOUT 60 Decision Trees)

    DELIVERABLE #4
    QUESTION 1: How does the accuracy of your best MNIST ConvNet compare to the accuracies of your best MNIST DT and RF 
    (i.e., their average weighted F1 scores)?
    RESPONSE 1: My best ConvNet accuracy from assignment 5 was:   Deeper ConvNet Acc = 0.9882
    A single decision tree practically wipes the floor with conv nets in terms of requisite training time, however it may not be as accurate as a fully trained 
    conv net. A forest is much better than a single conv net, but only after you have hit the limit of accuracy where more trees just doesn't help anymore.

    QUESTION 2:  Have you drawn any conclusions from this comparison?
    RESPONSE 2: Yes I have, DT are amazing!, and you get incredible results without the need to train forever and ever! But as was mentioned in class you need
    to evaluate your needs, capabilities, and knowledge and make a viable solution based on the resources you have available to you.


'''

#!/usr/bin/python

####################################################
# module: mnist_digits_random_forest.py
# description: Testing random forest for MNIST
# bugs to vladimir dot kulyukin via canvas
####################################################

from sklearn import tree, metrics
import numpy as np
import random
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix, classification_report
from mnist_loader import load_data_wrapper

mnist_train_data, mnist_test_data, mnist_valid_data = \
                  load_data_wrapper()

mnist_train_data_dc = np.zeros((50000, 784))
mnist_test_data_dc  = np.zeros((10000, 784))
mnist_valid_data_dc = np.zeros((10000, 784))

mnist_train_target_dc = None
mnist_test_target_dc  = None
mnist_valid_target_dc = None

def reshape_mnist_aux(mnist_data, mnist_data_dc):
    '''auxiliary function to reshape MNIST data for sklearn.'''
    for i in range(len(mnist_data)):
        mnist_data_dc[i] = mnist_data[i][0].reshape((784,))

def reshape_mnist_data():
    '''reshape all MNIST data for sklearn.'''
    global mnist_train_data
    global mnist_train_data_dc
    global mnist_test_data
    global mnist_test_data_dc
    global mnist_valid_data
    global mnist_valid_data_dc
    reshape_mnist_aux(mnist_train_data, mnist_train_data_dc)
    reshape_mnist_aux(mnist_test_data,  mnist_test_data_dc)
    reshape_mnist_aux(mnist_valid_data, mnist_valid_data_dc)

def reshape_mnist_target(mnist_data):
    '''reshape MNIST target given data.'''
    return np.array([np.argmax(mnist_data[i][1])
                    for i in range(len(mnist_data))])

def reshape_mnist_target2(mnist_data):
    '''another function for reshaping MNIST target given data.'''
    return np.array([mnist_data[i][1] for i in range(len(mnist_data))])

def prepare_mnist_data():
    '''reshape and prepare MNIST data for sklearn.'''
    global mnist_train_data
    global mnist_test_data
    global mnist_valid_data
    reshape_mnist_data()

    ### make sure that train, test, and valid data are reshaped
    ### correctly.
    for i in range(len(mnist_train_data)):
        assert np.array_equal(mnist_train_data[i][0].reshape((784,)),
                              mnist_train_data_dc[i])

    for i in range(len(mnist_test_data)):
        assert np.array_equal(mnist_test_data[i][0].reshape((784,)),
                              mnist_test_data_dc[i])

    for i in range(len(mnist_valid_data)):
        assert np.array_equal(mnist_valid_data[i][0].reshape((784,)),
                              mnist_valid_data_dc[i])

def prepare_mnist_targets():
    '''reshape and prepare MNIST targets for sklearn.'''
    global mnist_train_target_dc
    global mnist_test_target_dc
    global mnist_valid_target_dc    
    mnist_train_target_dc = reshape_mnist_target(mnist_train_data)
    mnist_test_target_dc  = reshape_mnist_target2(mnist_test_data)
    mnist_valid_target_dc = reshape_mnist_target2(mnist_valid_data) 

def fit_validate_dt():
    clf = tree.DecisionTreeClassifier(random_state=random.randint(0, 1000))
    dtr = clf.fit(mnist_train_data_dc, mnist_train_target_dc)
    valid_preds = dtr.predict(mnist_valid_data_dc)
    print(metrics.classification_report(mnist_valid_target_dc,valid_preds))
    cm1 = confusion_matrix(mnist_valid_target_dc, valid_preds)
    print(cm1)

def fit_validate_dts(num_dts):
    for i in range(num_dts):
        fit_validate_dt()
      

def fit_validate_rf(num_dts):
    clf = RandomForestClassifier(n_estimators=num_dts, random_state=random.randint(0, 1000))
    rf = clf.fit(mnist_train_data_dc, mnist_train_target_dc)
    valid_preds = rf.predict(mnist_valid_data_dc)
    print(metrics.classification_report(mnist_valid_target_dc,valid_preds))
    cm1 = confusion_matrix(mnist_valid_target_dc, valid_preds)
    print(cm1)

def fit_validate_rfs(low_nt, high_nt):
    for i in range(low_nt, high_nt+1, 10):
        print("################## current rf size = " + str(i))
        fit_validate_rf(i)

## Let's prepare MNIST data for unit tests.        
prepare_mnist_data()
prepare_mnist_targets()


if __name__ == '__main__':
    prepare_mnist_data()
    prepare_mnist_targets()

    
