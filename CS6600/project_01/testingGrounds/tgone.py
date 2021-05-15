
import threading 
import pickle
import numpy as np
import tensorflow as tf
import tflearn
from tflearn.layers.core import input_data, fully_connected
from tflearn.layers.estimator import regression
import time

netsFolder = './persistedNets/'
netsDataFolder = './netsDataFolder/'



## we need this to load the pickled data into Python.
def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj









### here's an example of how to make an ANN with tflearn.
### An ANN is nothing but a sequence of fully connected hidden layers
### plus the input layer and the output layer of appropriate dimensions.
def make_image_ann_model():
    # input_layer = input_data(shape=[None, 64, 64, 1])
    # fc_layer_1 = fully_connected(input_layer, 512, activation='relu', name='fc_layer_1')
    # fc_layer_2 = fully_connected(fc_layer_1, 256, activation='relu', name='fc_layer_2')
    # fc_layer_3 = fully_connected(fc_layer_2, 128, activation='relu', name='fc_layer_3')
    # fc_layer_4 = fully_connected(fc_layer_3, 64, activation='relu', name='fc_layer_4')
    # fc_layer_5 = fully_connected(fc_layer_4, 32, activation='relu', name='fc_layer_5')
    # fc_layer_6 = fully_connected(fc_layer_5, 16, activation='relu', name='fc_layer_6')
    # fc_layer_7 = fully_connected(fc_layer_6, 8, activation='relu', name='fc_layer_7')
    # fc_layer_8 = fully_connected(fc_layer_7, 2, activation='softmax', name='fc_layer_8')
    # network = regression(fc_layer_8, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    # model = tflearn.DNN(network)
    input_layer = input_data(shape=[None, 64, 64, 1])
    fc_layer_1 = fully_connected(input_layer, 128,
                                 activation='relu',
                                 name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2,
                                 activation='softmax',
                                 name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd',
                         loss='categorical_crossentropy',
                         learning_rate=0.1)
    model = tflearn.DNN(network)
    return model

### Note that the load function must mimick the
### the archictecture of the persisted model!!!
def load_image_ann_model(model_path):
    input_layer = input_data(shape=[None, 64, 64, 1])
    fc_layer_1 = fully_connected(input_layer, 128,
                                 activation='relu',
                                 name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2,
                                 activation='softmax',
                                 name='fc_layer_2')
    model = tflearn.DNN(fc_layer_2)
    model.load(model_path)
    return model

### test a tfl network model on valid_X and valid_Y.  
def test_tfl_image_ann_model(network_model, valid_X, valid_Y):
    results = []
    for i in range(len(valid_X)):
        prediction = network_model.predict(valid_X[i].reshape([-1, 64, 64, 1]))
        results.append(np.argmax(prediction, axis=1)[0] == \
                       np.argmax(valid_Y[i]))
    return float(sum((np.array(results) == True))) / float(len(results))

###  train a tfl model on train_X, train_Y, test_X, test_Y.
def train_tfl_image_ann_model(model, train_X, train_Y, test_X, test_Y, num_epochs=5, batch_size=10):
  tf.reset_default_graph()
  model.fit(train_X, train_Y, n_epoch=num_epochs,
            shuffle=True,
            validation_set=(test_X, test_Y),
            show_metric=True,
            batch_size=batch_size,
            run_id='image_ann_model')

### validating is testing on valid_X and valid_Y.
def validate_tfl_image_ann_model(model, valid_X, valid_Y):
    return test_tfl_image_ann_model(model, valid_X, valid_Y)


def getToWork(netFileName, netDataFileName):
    BEE1_gray_base_path='../bigData/BEE1_gray/BEE1_gray/'
    base_path = BEE1_gray_base_path
    BEE1_gray_train_X = load(base_path + 'train_X.pck')
    BEE1_gray_train_Y = load(base_path + 'train_Y.pck')
    BEE1_gray_test_X = load(base_path + 'test_X.pck')
    BEE1_gray_test_Y = load(base_path + 'test_Y.pck')
    BEE1_gray_valid_X = load(base_path + 'valid_X.pck')
    BEE1_gray_valid_Y = load(base_path + 'valid_Y.pck')
    BEE1_gray_train_X = BEE1_gray_train_X.reshape([-1, 64, 64, 1])
    BEE1_gray_test_X = BEE1_gray_test_X.reshape([-1, 64, 64, 1])
    assert BEE1_gray_train_X.shape[0] == BEE1_gray_train_Y.shape[0]
    assert BEE1_gray_test_X.shape[0]  == BEE1_gray_test_Y.shape[0]
    assert BEE1_gray_valid_X.shape[0] == BEE1_gray_valid_Y.shape[0]

    ann_model = make_image_ann_model()

    for i in range(0,5,1):
        train_tfl_image_ann_model(ann_model, BEE1_gray_train_X, BEE1_gray_train_Y, BEE1_gray_test_X, BEE1_gray_test_Y)
        v_acc = validate_tfl_image_ann_model(ann_model, BEE1_gray_valid_X, BEE1_gray_valid_Y)
        f = open(netsDataFolder + netDataFileName, "a")
        f.write(str(5 + 5*i) + " : " + str(v_acc) + "\n")
        f.close()

    
    ann_model.save(netsFolder + netFileName)


def megaTestNets(netsDirPath):
    print("Working")
    pertNetsList = []


  
def main():
    start = time.perf_counter()
    # getToWork("threadOne", "threadOne.txt")
    # getToWork("threadTwo", "threadTwo.txt")
    # getToWork("threadThree", "threadThree.txt")
    # getToWork("threadFour", "threadFour.txt")
    # getToWork("threadFive", "threadFive.txt")

    # t1 = threading.Thread(target=getToWork, args=("threadOne","threadOne.txt",)) 
    # t2 = threading.Thread(target=getToWork, args=("threadTwo","threadTwo.txt",)) 
    # t3 = threading.Thread(target=getToWork, args=("threadThree","threadThree.txt",)) 
    # t4 = threading.Thread(target=getToWork, args=("threadFour","threadFour.txt",))
    # t5 = threading.Thread(target=getToWork, args=("threadFive","threadFive.txt",)) 
    # t6 = threading.Thread(target=getToWork, args=("threadSix","threadSix.txt",)) 
    # t7 = threading.Thread(target=getToWork, args=("threadSeven","threadSeven.txt",)) 
    # t8 = threading.Thread(target=getToWork, args=("threadEight","threadEight.txt",)) 
    # t9 = threading.Thread(target=getToWork, args=("threadNine","threadNine.txt",))
    # t10 = threading.Thread(target=getToWork, args=("threadTen","threadTen.txt",)) 

    # t1.start() 
    # t2.start()
    # t3.start() 
    # t4.start()
    # t5.start()
    # t6.start()
    # t7.start()
    # t8.start()
    # t9.start()
    # t10.start()

    # t1.join() 
    # t2.join()
    # t3.join() 
    # t4.join()
    # t5.join()
    # t6.join()
    # t7.join()
    # t8.join()
    # t9.join()
    # t10.join()

    megaTestNets(netsFolder)

    end = time.perf_counter()


    print("Done! time! at: " + str(end - start)) 


#     print("Sup")
#     BEE1_gray_base_path='../bigData/BEE1_gray/BEE1_gray/'
#     ## let's load BEE1_gray
#     base_path = BEE1_gray_base_path
#     print('loading datasets from {}...'.format(base_path))
#     BEE1_gray_train_X = load(base_path + 'train_X.pck')
#     BEE1_gray_train_Y = load(base_path + 'train_Y.pck')
#     BEE1_gray_test_X = load(base_path + 'test_X.pck')
#     BEE1_gray_test_Y = load(base_path + 'test_Y.pck')
#     BEE1_gray_valid_X = load(base_path + 'valid_X.pck')
#     BEE1_gray_valid_Y = load(base_path + 'valid_Y.pck')
#     print(BEE1_gray_train_X.shape)
#     print(BEE1_gray_train_Y.shape)
#     print(BEE1_gray_test_X.shape)
#     print(BEE1_gray_test_Y.shape)
#     print(BEE1_gray_valid_X.shape)
#     print(BEE1_gray_valid_Y.shape)
#     print('datasets from {} loaded...'.format(base_path))
#     BEE1_gray_train_X = BEE1_gray_train_X.reshape([-1, 64, 64, 1])
#     BEE1_gray_test_X = BEE1_gray_test_X.reshape([-1, 64, 64, 1])

#     ## to make sure that the dimensions of the
#     ## examples and targets are the same.
#     assert BEE1_gray_train_X.shape[0] == BEE1_gray_train_Y.shape[0]
#     assert BEE1_gray_test_X.shape[0]  == BEE1_gray_test_Y.shape[0]
#     assert BEE1_gray_valid_X.shape[0] == BEE1_gray_valid_Y.shape[0]

    
    # # creating thread 
    # t1 = threading.Thread(target=print_cube, args=(10000000,11111111)) 
    # t2 = threading.Thread(target=print_cube, args=(10000000,22222222)) 
    # t3 = threading.Thread(target=print_cube, args=(10000000,33333333)) 
    # t4 = threading.Thread(target=print_cube, args=(10000000,44444444))
    # t5 = threading.Thread(target=print_cube, args=(10000000,55555555)) 
    # t6 = threading.Thread(target=print_cube, args=(10000000,66666666))   
    # t7 = threading.Thread(target=print_cube, args=(10000000,77777777))
    # t8 = threading.Thread(target=print_cube, args=(10000000,88888888))
    # t9 = threading.Thread(target=print_cube, args=(10000000,99999999))
    # t10 = threading.Thread(target=print_cube, args=(10000000,101010101))
    # # starting thread 1 
    # t1.start() 
    # t2.start()
    # t3.start() 
    # t4.start()
    # t5.start()
    # t6.start()
    # t7.start()
    # t8.start()
    # t9.start()
    # t10.start()
    # # wait until thread 1 is completely executed 
    # t1.join() 
    # # wait until thread 2 is completely executed 
    # t2.join() 
  
    # # both threads completely executed 
    # print("Done!") 


    




if __name__ == "__main__":
    main()
