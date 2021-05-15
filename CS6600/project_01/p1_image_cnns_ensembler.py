
import threading 
import pickle
import numpy as np
import tensorflow as tf
import tflearn
from tflearn.layers.core import input_data, fully_connected
from tflearn.layers.conv import conv_2d, max_pool_2d
from tflearn.layers.estimator import regression
import time
import os
import logging
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
tf.get_logger().setLevel(logging.ERROR)

LEARNING_RATE_ARR1 = [    .1,     .075,     .05,     .025]
LEARNING_RATE_ARR2 = [   .01,    .0075,    .005,    .0025]
LEARNING_RATE_ARR3 = [  .001,   .00075,   .0005,   .00025]
LEARNING_RATE_ARR4 = [ .0001,  .000075,  .00005,  .000025]
LEARNING_RATE_ARR5 = [.00001, .0000075, .000005, .0000025]

buzz1ModelsDataDir = "./ImageCnnsData/bee1Data/"
buzz2ModelsDataDir = "./ImageCnnsData/bee2Data/"
buzz3ModelsDataDir = "./ImageCnnsData/bee4Data/"

buzz1ModelsDirectory = "./ImageCnns/bee1/"
buzz1ModelNames = ["cnn_image_model_bee1_threadOne",
                  "cnn_image_model_bee1_threadTwo",
                  "cnn_image_model_bee1_threadThree",
                  "cnn_image_model_bee1_threadFour",
                  "cnn_image_model_bee1_threadFive",
                  "cnn_image_model_bee1_threadSix",
                  "cnn_image_model_bee1_threadSeven",
                  "cnn_image_model_bee1_threadEight",
                  "cnn_image_model_bee1_threadNine",
                  "cnn_image_model_bee1_threadTen"]

buzz2ModelsDirectory = "./ImageCnns/bee2_1s/"
buzz2ModelNames = ["cnn_image_model_bee2_1s_threadOne",
                  "cnn_image_model_bee2_1s_threadTwo",
                  "cnn_image_model_bee2_1s_threadThree",
                  "cnn_image_model_bee2_1s_threadFour",
                  "cnn_image_model_bee2_1s_threadFive",
                  "cnn_image_model_bee2_1s_threadSix",
                  "cnn_image_model_bee2_1s_threadSeven",
                  "cnn_image_model_bee2_1s_threadEight",
                  "cnn_image_model_bee2_1s_threadNine",
                  "cnn_image_model_bee2_1s_threadTen"]

buzz3ModelsDirectory = "./ImageCnns/bee4/"
buzz3ModelNames = ["cnn_image_model_bee4_threadOne",
                  "cnn_image_model_bee4_threadTwo",
                  "cnn_image_model_bee4_threadThree",
                  "cnn_image_model_bee4_threadFour",
                  "cnn_image_model_bee4_threadFive",
                  "cnn_image_model_bee4_threadSix",
                  "cnn_image_model_bee4_threadSeven",
                  "cnn_image_model_bee4_threadEight",
                  "cnn_image_model_bee4_threadNine",
                  "cnn_image_model_bee4_threadTen"]


BUZZ1_DATA_DIRECTORY = "./bigData/BEE1/BEE1/"
BUZZ2_DATA_DIRECTORY = "./bigData/BEE2_1S/BEE2_1S/"
BUZZ3_DATA_DIRECTORY = "./bigData/BEE4/BEE4/"

def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

def make_image_cnn_model():
    input_layer = input_data(shape=[None, 64, 64, 3])
    conv_layer_1 = conv_2d(input_layer, nb_filter=8, filter_size=3, activation='relu', name='conv_layer_1')
    pool_layer_1 = max_pool_2d(conv_layer_1, 2, name='pool_layer_1')
    fc_layer_1 = fully_connected(pool_layer_1, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    return model

def load_image_cnn_model(model_path):
    tf.reset_default_graph()
    input_layer = input_data(shape=[None, 64, 64, 3])
    conv_layer_1 = conv_2d(input_layer, nb_filter=8, filter_size=3, activation='relu', name='conv_layer_1')
    pool_layer_1 = max_pool_2d(conv_layer_1, 2, name='pool_layer_1')
    fc_layer_1 = fully_connected(pool_layer_1, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    model.load(model_path)
    return model

def test_tfl_image_cnn_model(network_model, validX, validY):
    results = []
    for i in range(len(validX)):
        prediction = network_model.predict(validX[i].reshape([-1, 64, 64, 3]))
        results.append(np.argmax(prediction, axis=1)[0] == \
                       np.argmax(validY[i]))
    return float(sum((np.array(results) == True))) / float(len(results))

def train_tfl_image_cnn_model(model, train_X, train_Y, test_X, test_Y, num_epochs=5, batch_size=10):
    tf.reset_default_graph()
    model.fit(train_X, train_Y, n_epoch=num_epochs,
                shuffle=True,
                validation_set=(test_X, test_Y),
                show_metric=True,
                batch_size=batch_size,
                run_id='image_cnn_model')

def validate_tfl_image_cnn_model(model, valid_X, valid_Y):
    return test_tfl_image_cnn_model(model, valid_X, valid_Y)


################################################################################################################################

def load_image_cnn_model_retrain(model_path, learningRate):
    tf.reset_default_graph()
    input_layer = input_data(shape=[None, 64, 64, 3])
    conv_layer_1 = conv_2d(input_layer, nb_filter=8, filter_size=3, activation='relu', name='conv_layer_1')
    pool_layer_1 = max_pool_2d(conv_layer_1, 2, name='pool_layer_1')
    fc_layer_1 = fully_connected(pool_layer_1, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=learningRate)
    model = tflearn.DNN(network)
    model.load(model_path)
    return model

def createSingleBuzzNet(netFileName, netDataFileName, buzzDataPath, buzzyDataDirectory, modelSaveDirectory):
    base_path = buzzDataPath
    BUZZ_train_X = load(base_path + 'train_X.pck')
    BUZZ_train_Y = load(base_path + 'train_Y.pck')
    BUZZ_test_X = load(base_path + 'test_X.pck')
    BUZZ_test_Y = load(base_path + 'test_Y.pck')
    BUZZ_valid_X = load(base_path + 'valid_X.pck')
    BUZZ_valid_Y = load(base_path + 'valid_Y.pck')

    BUZZ_train_X = BUZZ_train_X.reshape([-1, 64, 64, 3])
    BUZZ_test_X  = BUZZ_test_X.reshape([-1, 64, 64, 3])

    assert BUZZ_train_X.shape[0] == BUZZ_train_Y.shape[0]
    assert BUZZ_test_X.shape[0]  == BUZZ_test_Y.shape[0]
    assert BUZZ_valid_X.shape[0] == BUZZ_valid_Y.shape[0]

    cnn_model = make_image_cnn_model()

    for i in range(0,5,1):
        train_tfl_image_cnn_model(cnn_model, BUZZ_train_X, BUZZ_train_Y, BUZZ_test_X, BUZZ_test_Y)
        v_acc = validate_tfl_image_cnn_model(cnn_model, BUZZ_valid_X, BUZZ_valid_Y)
        f = open(buzzyDataDirectory + netDataFileName, "a")
        f.write(str(5 + 5*i).zfill(3) + " : " + str(v_acc) + "\n")
        f.close()
    cnn_model.save(modelSaveDirectory + netFileName)

def createBuzzNets(buzzNetModelNames, buzzDataPath, buzzyDataDir, modelSaveDirectory):
    start = time.perf_counter()
    t1 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[0],"threadOne.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t2 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[1],"threadTwo.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t3 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[2],"threadThree.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t4 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[3],"threadFour.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,))
    t5 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[4],"threadFive.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 

    t1.start() 
    t2.start()
    t3.start() 
    t4.start()
    t5.start()    
    
    t1.join() 
    t2.join()
    t3.join() 
    t4.join()
    t5.join()
    
    t6 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[5],"threadSix.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t7 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[6],"threadSeven.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t8 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[7],"threadEight.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 
    t9 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[8],"threadNine.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,))
    t10 = threading.Thread(target=createSingleBuzzNet, args=(buzzNetModelNames[9],"threadTen.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,)) 

    t6.start()
    t7.start()
    t8.start()
    t9.start()
    t10.start()

    t6.join()
    t7.join()
    t8.join()
    t9.join()
    t10.join()
    end = time.perf_counter()
    print("DONE!!! with time: " + str(end - start))

def retrainSingleBuzzNet(netFileName, netDataFileName, buzzDataPath, buzzyDataDirectory, modelSaveDirectory, retrainLearningRate):
    base_path = buzzDataPath
    BUZZ_train_X = load(base_path + 'train_X.pck')
    BUZZ_train_Y = load(base_path + 'train_Y.pck')
    BUZZ_test_X = load(base_path + 'test_X.pck')
    BUZZ_test_Y = load(base_path + 'test_Y.pck')
    BUZZ_valid_X = load(base_path + 'valid_X.pck')
    BUZZ_valid_Y = load(base_path + 'valid_Y.pck')

    BUZZ_train_X = BUZZ_train_X.reshape([-1, 64, 64, 3])
    BUZZ_test_X  = BUZZ_test_X.reshape([-1, 64, 64, 3])

    assert BUZZ_train_X.shape[0] == BUZZ_train_Y.shape[0]
    assert BUZZ_test_X.shape[0]  == BUZZ_test_Y.shape[0]
    assert BUZZ_valid_X.shape[0] == BUZZ_valid_Y.shape[0]

    cnn_model = load_image_cnn_model_retrain(modelSaveDirectory + netFileName, retrainLearningRate)

    for i in range(0,5,1):
        train_tfl_image_cnn_model(cnn_model, BUZZ_train_X, BUZZ_train_Y, BUZZ_test_X, BUZZ_test_Y)
        v_acc = validate_tfl_image_cnn_model(cnn_model, BUZZ_valid_X, BUZZ_valid_Y)
        f = open(buzzyDataDirectory + netDataFileName, "a")
        f.write(str(5 + 5*i).zfill(3) + " : " + str(retrainLearningRate).zfill(5) + " : " + str(v_acc) + "\n")
        f.close()
    cnn_model.save(modelSaveDirectory + netFileName)

def retrainBuzzNets(buzzNetModelNames, buzzDataPath, buzzyDataDir, modelSaveDirectory, retrainLearningRate):
    start = time.perf_counter()
    t1 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[0],"threadOne.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t2 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[1],"threadTwo.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t3 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[2],"threadThree.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t4 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[3],"threadFour.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,))
    t5 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[4],"threadFive.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 

    t1.start() 
    t2.start()
    t3.start() 
    t4.start()
    t5.start()

    t1.join() 
    t2.join()
    t3.join() 
    t4.join()
    t5.join()

    t6 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[5],"threadSix.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t7 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[6],"threadSeven.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t8 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[7],"threadEight.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 
    t9 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[8],"threadNine.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,))
    t10 = threading.Thread(target=retrainSingleBuzzNet, args=(buzzNetModelNames[9],"threadTen.txt",buzzDataPath,buzzyDataDir,modelSaveDirectory,retrainLearningRate,)) 

    t6.start()
    t7.start()
    t8.start()
    t9.start()
    t10.start()

    t6.join()
    t7.join()
    t8.join()
    t9.join()
    t10.join()
    end = time.perf_counter()
    print("DONE!!! with time: " + str(end - start))    

def testBuzzNets(buzzModelsDirectory, buzzModelNames, buzzDataPath):
    ensembleNets = []
    for model in buzzModelNames:
        ensembleNets.append(load_image_cnn_model(buzzModelsDirectory + model))

    base_path = buzzDataPath
    BUZZ_valid_X = load(base_path + 'valid_X.pck')
    BUZZ_valid_Y = load(base_path + 'valid_Y.pck')

    correctResults = 0
    for i in range(len(BUZZ_valid_X)):
        localVoteResults = []
        for net in ensembleNets:
            netPrediction = net.predict(BUZZ_valid_X[i].reshape([-1, 64, 64, 3]))
            localVoteResults.append(np.argmax(netPrediction, axis=1)[0])
        subResult = max(set(localVoteResults), key = localVoteResults.count)
        if str(subResult) == str(np.argmax(BUZZ_valid_Y[i])):
            correctResults += 1
    print( float(correctResults) / float(len(BUZZ_valid_X)) )    

################################################################################################################################

def createNets():
    # createBuzzNets(buzz1ModelNames, BUZZ1_DATA_DIRECTORY, buzz1ModelsDataDir, buzz1ModelsDirectory)
    # createBuzzNets(buzz2ModelNames, BUZZ2_DATA_DIRECTORY, buzz2ModelsDataDir, buzz2ModelsDirectory)
    # createBuzzNets(buzz3ModelNames, BUZZ3_DATA_DIRECTORY, buzz3ModelsDataDir, buzz3ModelsDirectory)
    pass

def retrainNets():
    # for i in range(len(LEARNING_RATE_ARR1)):
    #     currLearningRate = LEARNING_RATE_ARR1[i]
    #     retrainBuzzNets(buzz1ModelNames, BUZZ1_DATA_DIRECTORY, buzz1ModelsDataDir, buzz1ModelsDirectory, currLearningRate)
    #     retrainBuzzNets(buzz2ModelNames, BUZZ2_DATA_DIRECTORY, buzz2ModelsDataDir, buzz2ModelsDirectory, currLearningRate)
    #     retrainBuzzNets(buzz3ModelNames, BUZZ3_DATA_DIRECTORY, buzz3ModelsDataDir, buzz3ModelsDirectory, currLearningRate)
    
    # for i in range(len(LEARNING_RATE_ARR2)):
    #     currLearningRate = LEARNING_RATE_ARR2[i]
    #     retrainBuzzNets(buzz1ModelNames, BUZZ1_DATA_DIRECTORY, buzz1ModelsDataDir, buzz1ModelsDirectory, currLearningRate)
    #     retrainBuzzNets(buzz2ModelNames, BUZZ2_DATA_DIRECTORY, buzz2ModelsDataDir, buzz2ModelsDirectory, currLearningRate)
    #     retrainBuzzNets(buzz3ModelNames, BUZZ3_DATA_DIRECTORY, buzz3ModelsDataDir, buzz3ModelsDirectory, currLearningRate)


    # for i in range(len(LEARNING_RATE_ARR3)):
    #     currLearningRate = LEARNING_RATE_ARR3[i]

    # for i in range(len(LEARNING_RATE_ARR4)):
    #     currLearningRate = LEARNING_RATE_ARR4[i]

    # for i in range(len(LEARNING_RATE_ARR5)):
    #     currLearningRate = LEARNING_RATE_ARR5[i]
    pass

def testNets():
    testBuzzNets(buzz1ModelsDirectory, buzz1ModelNames, BUZZ1_DATA_DIRECTORY)
    testBuzzNets(buzz2ModelsDirectory, buzz2ModelNames, BUZZ2_DATA_DIRECTORY)
    testBuzzNets(buzz3ModelsDirectory, buzz3ModelNames, BUZZ3_DATA_DIRECTORY)
    pass

def main():
    choice = input("C: Create \nR: Retrain \nT: Test \n")
    if choice.lower() == "c":
        createNets()
    if choice.lower() == "r":
        retrainNets()
    if choice.lower() == "t":
        testNets()

if __name__ == "__main__":
    main()


