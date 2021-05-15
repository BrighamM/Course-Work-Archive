'''
HERE FOLLOWS MY VALIDATION PERCENTAGES FOR MY VARIOUS ENSEMBLES:
Bee1_Gray_Ann_Ensemble_Validation_Perc......: 0.933390022675737
Bee2_1S_Gray_Ann_Ensemble_Validation_Perc...: 0.6832360452389639
Bee4_Gray_Ann_Ensemble_Validation_Perc......: 0.7849555335968379
Buzz1_Ann_Ensemble_Validation_Perc..........: 0.5852173913043478
Buzz2_Ann_Ensemble_Validation_Perc..........: 0.42333333333333334
Buzz3_Ann_Ensemble_Validation_Perc..........: 0.7183580387685291
Bee1_Cnn_Ensemble_Validation_Perc...........: 0.9739229024943311
Bee2_1S_Cnn_Ensemble_Validation_Perc........: 0.7837468077344035
Bee4_Cnn_Ensemble_Validation_Perc...........: 0.737401185770751
Buzz1_Cnn_Ensemble_Validation_Perc..........: 0.5530434782608695
Buzz2_Cnn_Ensemble_Validation_Perc..........: 0.3616666666666667
Buzz3_Cnn_Ensemble_Validation_Perc..........: 0.6596351197263398

'''



import pickle
import numpy as np
import unittest
import tensorflow as tf
import tflearn
from tflearn.layers.core import input_data, fully_connected
from tflearn.layers.conv import conv_2d, max_pool_2d
from tflearn.layers.estimator import regression
import logging
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
tf.get_logger().setLevel(logging.ERROR)
# from load_nets import *

## we need this to load the pickled data into Python.
def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

BUZZ1_base_path = "./ValidationDataSets/BUZZ1/"
BUZZ2_base_path = "./ValidationDataSets/BUZZ2/"
BUZZ3_base_path = "./ValidationDataSets/BUZZ3/"

BEE1_GRAY_base_path = "./ValidationDataSets/BEE1_gray/"
BEE2_1S_GRAY_base_path = "./ValidationDataSets/BEE2_1S_gray/"
BEE4_GRAY_base_path = "./ValidationDataSets/BEE4_gray/"

BEE1_base_path = "./ValidationDataSets/BEE1/"
BEE2_1S_base_path = "./ValidationDataSets/BEE2_1S/"
BEE4_base_path = "./ValidationDataSets/BEE4/"

########################################################################

audioAnnsBuzz1ModelsDirectory = "./tfl_nets/AudioAnns/buzz1/"
audioAnnsBuzz1ModelNames = ["ann_audio_model_buzz1_threadOne",
                   "ann_audio_model_buzz1_threadTwo",
                   "ann_audio_model_buzz1_threadThree",
                   "ann_audio_model_buzz1_threadFour",
                   "ann_audio_model_buzz1_threadFive",
                   "ann_audio_model_buzz1_threadSix",
                   "ann_audio_model_buzz1_threadSeven",
                   "ann_audio_model_buzz1_threadEight",
                   "ann_audio_model_buzz1_threadNine",
                   "ann_audio_model_buzz1_threadTen"]

audioAnnsBuzz2ModelsDirectory = "./tfl_nets/AudioAnns/buzz2/"
audioAnnsBuzz2ModelNames = ["ann_audio_model_buzz1_threadOne",
                   "ann_audio_model_buzz1_threadTwo",
                   "ann_audio_model_buzz1_threadThree",
                   "ann_audio_model_buzz1_threadFour",
                   "ann_audio_model_buzz1_threadFive",
                   "ann_audio_model_buzz1_threadSix",
                   "ann_audio_model_buzz1_threadSeven",
                   "ann_audio_model_buzz1_threadEight",
                   "ann_audio_model_buzz1_threadNine",
                   "ann_audio_model_buzz1_threadTen"]

audioAnnsBuzz3ModelsDirectory = "./tfl_nets/AudioAnns/buzz3/"
audioAnnsBuzz3ModelNames = ["ann_audio_model_buzz1_threadOne",
                   "ann_audio_model_buzz1_threadTwo",
                   "ann_audio_model_buzz1_threadThree",
                   "ann_audio_model_buzz1_threadFour",
                   "ann_audio_model_buzz1_threadFive",
                   "ann_audio_model_buzz1_threadSix",
                   "ann_audio_model_buzz1_threadSeven",
                   "ann_audio_model_buzz1_threadEight",
                   "ann_audio_model_buzz1_threadNine",
                   "ann_audio_model_buzz1_threadTen"]

########################################################################

imageAnnsBee1_gray_ModelsDirectory = "./tfl_nets/ImageAnns/bee1/"
imageAnnsBee1_gray_ModelNames = ["ann_image_model_bee1_gray_threadOne",
                  "ann_image_model_bee1_gray_threadTwo",
                  "ann_image_model_bee1_gray_threadThree",
                  "ann_image_model_bee1_gray_threadFour",
                  "ann_image_model_bee1_gray_threadFive",
                  "ann_image_model_bee1_gray_threadSix",
                  "ann_image_model_bee1_gray_threadSeven",
                  "ann_image_model_bee1_gray_threadEight",
                  "ann_image_model_bee1_gray_threadNine",
                  "ann_image_model_bee1_gray_threadTen"]

imageAnnsBee2_1s_gray_ModelsDirectory = "./tfl_nets/ImageAnns/bee2_1s/"
imageAnnsBee2_1s_gray_ModelNames = ["ann_image_model_bee2_1s_gray_threadOne",
                  "ann_image_model_bee2_1s_gray_threadTwo",
                  "ann_image_model_bee2_1s_gray_threadThree",
                  "ann_image_model_bee2_1s_gray_threadFour",
                  "ann_image_model_bee2_1s_gray_threadFive",
                  "ann_image_model_bee2_1s_gray_threadSix",
                  "ann_image_model_bee2_1s_gray_threadSeven",
                  "ann_image_model_bee2_1s_gray_threadEight",
                  "ann_image_model_bee2_1s_gray_threadNine",
                  "ann_image_model_bee2_1s_gray_threadTen"]

imageAnnsBee4_gray_ModelsDirectory = "./tfl_nets/ImageAnns/bee4/"
imageAnnsBee4_gray_ModelNames = ["ann_image_model_bee4_gray_threadOne",
                  "ann_image_model_bee4_gray_threadTwo",
                  "ann_image_model_bee4_gray_threadThree",
                  "ann_image_model_bee4_gray_threadFour",
                  "ann_image_model_bee4_gray_threadFive",
                  "ann_image_model_bee4_gray_threadSix",
                  "ann_image_model_bee4_gray_threadSeven",
                  "ann_image_model_bee4_gray_threadEight",
                  "ann_image_model_bee4_gray_threadNine",
                  "ann_image_model_bee4_gray_threadTen"]

########################################################################

audioCnnsBuzz1ModelsDirectory = "./tfl_nets/AudioCnns/buzz1/"
audioCnnsBuzz1ModelNames = ["cnn_audio_model_buzz1_threadOne",
                   "cnn_audio_model_buzz1_threadTwo",
                   "cnn_audio_model_buzz1_threadThree",
                   "cnn_audio_model_buzz1_threadFour",
                   "cnn_audio_model_buzz1_threadFive",
                   "cnn_audio_model_buzz1_threadSix",
                   "cnn_audio_model_buzz1_threadSeven",
                   "cnn_audio_model_buzz1_threadEight",
                   "cnn_audio_model_buzz1_threadNine",
                   "cnn_audio_model_buzz1_threadTen"]

audioCnnsBuzz2ModelsDirectory = "./tfl_nets/AudioCnns/buzz2/"
audioCnnsBuzz2ModelNames = ["cnn_audio_model_buzz1_threadOne",
                   "cnn_audio_model_buzz1_threadTwo",
                   "cnn_audio_model_buzz1_threadThree",
                   "cnn_audio_model_buzz1_threadFour",
                   "cnn_audio_model_buzz1_threadFive",
                   "cnn_audio_model_buzz1_threadSix",
                   "cnn_audio_model_buzz1_threadSeven",
                   "cnn_audio_model_buzz1_threadEight",
                   "cnn_audio_model_buzz1_threadNine",
                   "cnn_audio_model_buzz1_threadTen"]

audioCnnsBuzz3ModelsDirectory = "./tfl_nets/AudioCnns/buzz3/"
audioCnnsBuzz3ModelNames = ["cnn_audio_model_buzz1_threadOne",
                   "cnn_audio_model_buzz1_threadTwo",
                   "cnn_audio_model_buzz1_threadThree",
                   "cnn_audio_model_buzz1_threadFour",
                   "cnn_audio_model_buzz1_threadFive",
                   "cnn_audio_model_buzz1_threadSix",
                   "cnn_audio_model_buzz1_threadSeven",
                   "cnn_audio_model_buzz1_threadEight",
                   "cnn_audio_model_buzz1_threadNine",
                   "cnn_audio_model_buzz1_threadTen"]

########################################################################

imageCnnsBee1ModelsDirectory = "./tfl_nets/ImageCnns/bee1/"
imageCnnsBee1ModelNames = ["cnn_image_model_bee1_threadOne",
                  "cnn_image_model_bee1_threadTwo",
                  "cnn_image_model_bee1_threadThree",
                  "cnn_image_model_bee1_threadFour",
                  "cnn_image_model_bee1_threadFive",
                  "cnn_image_model_bee1_threadSix",
                  "cnn_image_model_bee1_threadSeven",
                  "cnn_image_model_bee1_threadEight",
                  "cnn_image_model_bee1_threadNine",
                  "cnn_image_model_bee1_threadTen"]

imageCnnsBee2_1s_ModelsDirectory = "./tfl_nets/ImageCnns/bee2_1s/"
imageCnnsBee2_1s_ModelNames = ["cnn_image_model_bee2_1s_threadOne",
                  "cnn_image_model_bee2_1s_threadTwo",
                  "cnn_image_model_bee2_1s_threadThree",
                  "cnn_image_model_bee2_1s_threadFour",
                  "cnn_image_model_bee2_1s_threadFive",
                  "cnn_image_model_bee2_1s_threadSix",
                  "cnn_image_model_bee2_1s_threadSeven",
                  "cnn_image_model_bee2_1s_threadEight",
                  "cnn_image_model_bee2_1s_threadNine",
                  "cnn_image_model_bee2_1s_threadTen"]

imageCnnsBee4ModelsDirectory = "./tfl_nets/ImageCnns/bee4/"
imageCnnsBee4ModelNames = ["cnn_image_model_bee4_threadOne",
                  "cnn_image_model_bee4_threadTwo",
                  "cnn_image_model_bee4_threadThree",
                  "cnn_image_model_bee4_threadFour",
                  "cnn_image_model_bee4_threadFive",
                  "cnn_image_model_bee4_threadSix",
                  "cnn_image_model_bee4_threadSeven",
                  "cnn_image_model_bee4_threadEight",
                  "cnn_image_model_bee4_threadNine",
                  "cnn_image_model_bee4_threadTen"]
                  
########################################################################

### ================== ENSEMBLE FUNCTIONS ===========================

def load_audio_ann_model(model_path):
    tf.reset_default_graph()
    input_layer = input_data(shape=[None, 4000, 1, 1])
    fc_layer_1 = fully_connected(input_layer, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 3, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    model.load(model_path)
    return model

def load_audio_cnn_model(model_path):
    tf.reset_default_graph()
    input_layer = input_data(shape=[None, 4000, 1, 1])
    conv_layer_1 = conv_2d(input_layer, nb_filter=8, filter_size=3, activation='relu', name='conv_layer_1')
    pool_layer_1 = max_pool_2d(conv_layer_1, 2, name='pool_layer_1')
    fc_layer_1 = fully_connected(pool_layer_1, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 3, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    model.load(model_path)
    return model

def load_image_ann_model(model_path):
    tf.reset_default_graph()
    input_layer = input_data(shape=[None, 64, 64, 1])
    fc_layer_1 = fully_connected(input_layer, 128, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(fc_layer_1, 2, activation='softmax', name='fc_layer_2')
    network = regression(fc_layer_2, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    model.load(model_path)
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

def get_Buzz1_Ann_Ensemble():
    ensembleNets = []
    for model in audioAnnsBuzz1ModelNames:
        ensembleNets.append(load_audio_ann_model(audioAnnsBuzz1ModelsDirectory + model))
    return ensembleNets
def get_Buzz2_Ann_Ensemble():
    ensembleNets = []
    for model in audioAnnsBuzz2ModelNames:
        ensembleNets.append(load_audio_ann_model(audioAnnsBuzz2ModelsDirectory + model))
    return ensembleNets
def get_Buzz3_Ann_Ensemble():
    ensembleNets = []
    for model in audioAnnsBuzz3ModelNames:
        ensembleNets.append(load_audio_ann_model(audioAnnsBuzz3ModelsDirectory + model))
    return ensembleNets

def get_Bee1_Gray_Ann_Ensemble():
    ensembleNets = []
    for model in imageAnnsBee1_gray_ModelNames:
        ensembleNets.append(load_image_ann_model(imageAnnsBee1_gray_ModelsDirectory + model))
    return ensembleNets
def get_Bee2_1S_Gray_Ann_Ensemble():
    ensembleNets = []
    for model in imageAnnsBee2_1s_gray_ModelNames:
        ensembleNets.append(load_image_ann_model(imageAnnsBee2_1s_gray_ModelsDirectory + model))
    return ensembleNets
def get_Bee4_Gray_Ann_Ensemble():
    ensembleNets = []
    for model in imageAnnsBee4_gray_ModelNames:
        ensembleNets.append(load_image_ann_model(imageAnnsBee4_gray_ModelsDirectory + model))
    return ensembleNets

def get_Buzz1_Cnn_Ensemble():
    ensembleNets = []
    for model in audioCnnsBuzz1ModelNames:
        ensembleNets.append(load_audio_cnn_model(audioCnnsBuzz1ModelsDirectory + model))
    return ensembleNets
def get_Buzz2_Cnn_Ensemble():
    ensembleNets = []
    for model in audioCnnsBuzz2ModelNames:
        ensembleNets.append(load_audio_cnn_model(audioCnnsBuzz2ModelsDirectory + model))
    return ensembleNets
def get_Buzz3_Cnn_Ensemble():
    ensembleNets = []
    for model in audioCnnsBuzz3ModelNames:
        ensembleNets.append(load_audio_cnn_model(audioCnnsBuzz3ModelsDirectory + model))
    return ensembleNets

def get_Bee1_Cnn_Ensemble():
    ensembleNets = []
    for model in imageCnnsBee1ModelNames:
        ensembleNets.append(load_image_cnn_model(imageCnnsBee1ModelsDirectory + model))
    return ensembleNets
def get_Bee2_1S_Cnn_Ensemble():
    ensembleNets = []
    for model in imageCnnsBee2_1s_ModelNames:
        ensembleNets.append(load_image_cnn_model(imageCnnsBee2_1s_ModelsDirectory + model))
    return ensembleNets
def get_Bee4_Cnn_Ensemble():
    ensembleNets = []
    for model in imageCnnsBee4ModelNames:
        ensembleNets.append(load_image_cnn_model(imageCnnsBee4ModelsDirectory + model))
    return ensembleNets

def validateAllEnsembles():
    # ENSEMBLES, ASSEMBLE!
    Bee1_Gray_Ann_Ensemble = get_Bee1_Gray_Ann_Ensemble()
    Bee2_1S_Gray_Ann_Ensemble = get_Bee2_1S_Gray_Ann_Ensemble()
    Bee4_Gray_Ann_Ensemble = get_Bee4_Gray_Ann_Ensemble()

    Buzz1_Ann_Ensemble = get_Buzz1_Ann_Ensemble()
    Buzz2_Ann_Ensemble = get_Buzz2_Ann_Ensemble()
    Buzz3_Ann_Ensemble = get_Buzz3_Ann_Ensemble()

    Bee1_Cnn_Ensemble = get_Bee1_Cnn_Ensemble()
    Bee2_1S_Cnn_Ensemble = get_Bee2_1S_Cnn_Ensemble()
    Bee4_Cnn_Ensemble = get_Bee4_Cnn_Ensemble()

    Buzz1_Cnn_Ensemble = get_Buzz1_Cnn_Ensemble()
    Buzz2_Cnn_Ensemble = get_Buzz2_Cnn_Ensemble()
    Buzz3_Cnn_Ensemble = get_Buzz3_Cnn_Ensemble()

    Bee1_Gray_Ann_Ensemble_Validation_Perc = validateEnsemble(Bee1_Gray_Ann_Ensemble, BEE1_GRAY_base_path, predict_with_tfl_ann_image_model)
    Bee2_1S_Gray_Ann_Ensemble_Validation_Perc = validateEnsemble(Bee2_1S_Gray_Ann_Ensemble, BEE2_1S_GRAY_base_path, predict_with_tfl_ann_image_model)
    Bee4_Gray_Ann_Ensemble_Validation_Perc = validateEnsemble(Bee4_Gray_Ann_Ensemble, BEE4_GRAY_base_path, predict_with_tfl_ann_image_model)

    Buzz1_Ann_Ensemble_Validation_Perc = validateEnsemble(Buzz1_Ann_Ensemble, BUZZ1_base_path, predict_with_tfl_audio_model)
    Buzz2_Ann_Ensemble_Validation_Perc = validateEnsemble(Buzz2_Ann_Ensemble, BUZZ2_base_path, predict_with_tfl_audio_model)
    Buzz3_Ann_Ensemble_Validation_Perc = validateEnsemble(Buzz3_Ann_Ensemble, BUZZ3_base_path, predict_with_tfl_audio_model)

    Bee1_Cnn_Ensemble_Validation_Perc = validateEnsemble(Bee1_Cnn_Ensemble, BEE1_base_path, predict_with_tfl_cnn_image_model)
    Bee2_1S_Cnn_Ensemble_Validation_Perc = validateEnsemble(Bee2_1S_Cnn_Ensemble, BEE2_1S_base_path, predict_with_tfl_cnn_image_model)
    Bee4_Cnn_Ensemble_Validation_Perc = validateEnsemble(Bee4_Cnn_Ensemble, BEE4_base_path, predict_with_tfl_cnn_image_model)

    Buzz1_Cnn_Ensemble_Validation_Perc = validateEnsemble(Buzz1_Cnn_Ensemble, BUZZ1_base_path, predict_with_tfl_audio_model)
    Buzz2_Cnn_Ensemble_Validation_Perc = validateEnsemble(Buzz2_Cnn_Ensemble, BUZZ2_base_path, predict_with_tfl_audio_model)
    Buzz3_Cnn_Ensemble_Validation_Perc = validateEnsemble(Buzz3_Cnn_Ensemble, BUZZ3_base_path, predict_with_tfl_audio_model)

    print("Bee1_Gray_Ann_Ensemble_Validation_Perc : " + str(Bee1_Gray_Ann_Ensemble_Validation_Perc))
    print("Bee2_1S_Gray_Ann_Ensemble_Validation_Perc : " + str(Bee2_1S_Gray_Ann_Ensemble_Validation_Perc))
    print("Bee4_Gray_Ann_Ensemble_Validation_Perc : " + str(Bee4_Gray_Ann_Ensemble_Validation_Perc))
    print("Buzz1_Ann_Ensemble_Validation_Perc : " + str(Buzz1_Ann_Ensemble_Validation_Perc))
    print("Buzz2_Ann_Ensemble_Validation_Perc : " + str(Buzz2_Ann_Ensemble_Validation_Perc))
    print("Buzz3_Ann_Ensemble_Validation_Perc : " + str(Buzz3_Ann_Ensemble_Validation_Perc))
    print("Bee1_Cnn_Ensemble_Validation_Perc : " + str(Bee1_Cnn_Ensemble_Validation_Perc))
    print("Bee2_1S_Cnn_Ensemble_Validation_Perc : " + str(Bee2_1S_Cnn_Ensemble_Validation_Perc))
    print("Bee4_Cnn_Ensemble_Validation_Perc : " + str(Bee4_Cnn_Ensemble_Validation_Perc))
    print("Buzz1_Cnn_Ensemble_Validation_Perc : " + str(Buzz1_Cnn_Ensemble_Validation_Perc))
    print("Buzz2_Cnn_Ensemble_Validation_Perc : " + str(Buzz2_Cnn_Ensemble_Validation_Perc))
    print("Buzz3_Cnn_Ensemble_Validation_Perc : " + str(Buzz3_Cnn_Ensemble_Validation_Perc))








def validateEnsemble(someEnsemble, validationDir, predictorFunction):
    base_path = validationDir
    BUZZ_valid_X = load(base_path + 'valid_X.pck')
    BUZZ_valid_Y = load(base_path + 'valid_Y.pck')

    correctResults = 0
    for i in range(len(BUZZ_valid_X)):
        localVoteResults = []
        for net in someEnsemble:
            localVoteResults.append(predictorFunction(net, BUZZ_valid_X[i]))
            # netPrediction = net.predict(BUZZ_valid_X[i].reshape([-1, 4000, 1, 1]))
            # localVoteResults.append(np.argmax(netPrediction, axis=1)[0])
        subResult = max(set(localVoteResults), key = localVoteResults.count)
        if str(subResult) == str(np.argmax(BUZZ_valid_Y[i])):
            correctResults += 1
    return float(correctResults) / float(len(BUZZ_valid_X))

def validateEnsembleTWO(someEnsemble, validationDir, predictorFunction):
    base_path = validationDir
    BUZZ_valid_X = load(base_path + 'valid_X.pck')
    BUZZ_valid_Y = load(base_path + 'valid_Y.pck')

    results = []
    for i in range(len(BUZZ_valid_X)):
        prediction = predict_with_tfl_ensemble(someEnsemble, BUZZ_valid_X[i], predictorFunction)
        results.append(prediction == np.argmax(BUZZ_valid_Y[i]))
    return float(sum((np.array(results) == True))) / float(len(results))

def predict_with_tfl_audio_model(network_model, audio_example):
    prediction = network_model.predict(audio_example.reshape([-1, 4000, 1, 1]))
    return np.argmax(prediction, axis=1)[0]

def predict_with_tfl_ann_image_model(ann_model, image_example):
    prediction = ann_model.predict(image_example.reshape([-1, 64, 64, 1]))    
    return np.argmax(prediction, axis=1)[0]

def predict_with_tfl_cnn_image_model(cnn_model, image_example):
    prediction = cnn_model.predict(image_example.reshape([-1, 64, 64, 3]))    
    return np.argmax(prediction, axis=1)[0]

def predict_with_tfl_ensemble(ensemble, example, predict_fun):
    d = {}
    for net in ensemble:
        prediction = predict_fun(net, example)
        if prediction in d:
            d[prediction] += 1
        else:
            d[prediction] = 1
    dlist = []
    for kv in d.items():
        dlist.append(kv)
    dlist.sort(key=lambda x: x[1], reverse=True)
    return dlist[0][0]

## =============== ENSEMBLE LOADERS AND CLASSIFIERS THAT YOU HAVE TO DEFINE =============================

def load_tfl_ann_ensemble_for_buzz1():
    return get_Buzz1_Ann_Ensemble()

def load_tfl_ann_ensemble_for_buzz2():
    return get_Buzz2_Ann_Ensemble()

def load_tfl_ann_ensemble_for_buzz3():
    return get_Buzz3_Ann_Ensemble()

def load_tfl_cnn_ensemble_for_buzz1():
    return get_Buzz1_Cnn_Ensemble()

def load_tfl_cnn_ensemble_for_buzz2():
    return get_Buzz2_Cnn_Ensemble()

def load_tfl_cnn_ensemble_for_buzz3():
    return get_Buzz3_Cnn_Ensemble()

def load_tfl_ann_ensemble_for_bee1_gray():
    return get_Bee1_Gray_Ann_Ensemble()

def load_tfl_ann_ensemble_for_bee2_1s_gray():
    return get_Bee2_1S_Gray_Ann_Ensemble()

def load_tfl_ann_ensemble_for_bee4_gray():
    return get_Bee4_Gray_Ann_Ensemble()

def load_tfl_cnn_ensemble_for_bee1():
    return get_Bee1_Cnn_Ensemble()

def load_tfl_cnn_ensemble_for_bee2_1s():
    return get_Bee2_1S_Cnn_Ensemble()

def load_tfl_cnn_ensemble_for_bee4():
    return get_Bee4_Cnn_Ensemble()

### sample ensemble unit tests
class cs5600_6600_f20_project01_ensemble_uts(unittest.TestCase):

    def test_ut00(self):
        ensemble = load_tfl_ann_ensemble_for_buzz1()
        assert len(ensemble) == 3

    def test_ut01(self):
        tf.reset_default_graph()
        ensemble_list = ['ann_audio_model_buzz1.tfl', 'ann_audio_model_buzz1.tfl', 'ann_audio_model_buzz1.tfl']
        loader_funs = [load_ann_audio_model_buzz1, load_ann_audio_model2_buzz1, load_ann_audio_model3_buzz1]
        ensemble = load_tfl_net_ensemble(NET_PATH, ensemble_list, loader_funs)
        assert len(ensemble_list) == 3

    def test_ut02(self):
        tf.reset_default_graph()        
        ensemble_list = ['ann_audio_model_buzz1.tfl', 'ann_audio_model_buzz1.tfl', 'ann_audio_model_buzz1.tfl']
        loader_funs = [load_ann_audio_model_buzz1, load_ann_audio_model2_buzz1, load_ann_audio_model_buzz1]        
        ensemble = load_tfl_net_ensemble(NET_PATH, ensemble_list, loader_funs)
        assert len(ensemble_list) == 3
        assert predict_with_tfl_ensemble(ensemble, BUZZ_valid_X[0], predict_with_tfl_audio_model) == 0

    def test_ut03(self):
        tf.reset_default_graph()
        ensemble_list = ['ann_image_model_bee1_gray.tfl', 'ann_image_model_bee1_gray.tfl', 'ann_image_model_bee1_gray.tfl']
        loader_funs = [load_ann_image_model_bee1_gray,
                       load_ann_image_model2_bee1_gray,
                       load_ann_image_model2_bee1_gray]
        ensemble = load_tfl_net_ensemble(NET_PATH, ensemble_list, loader_funs)
        assert len(ensemble_list) == 3
        assert predict_with_tfl_ensemble(ensemble, BEE_gray_valid_X[0], predict_with_tfl_ann_image_model) == 0

    def test_ut04(self):
        tf.reset_default_graph()        
        ensemble_list = ['cnn_audio_model_buzz2.tfl', 'cnn_audio_model_buzz2.tfl', 'cnn_audio_model_buzz2.tfl']
        loader_funs = [load_cnn_audio_model_buzz2, load_cnn_audio_model2_buzz2, load_cnn_audio_model3_buzz2]        
        ensemble = load_tfl_net_ensemble(NET_PATH, ensemble_list, loader_funs)
        assert len(ensemble_list) == 3
        assert predict_with_tfl_ensemble(ensemble, BUZZ_valid_X[0], predict_with_tfl_audio_model) == 1

    def test_ut05(self):
        tf.reset_default_graph()
        ensemble_list = ['cnn_image_model_bee1.tfl', 'cnn_image_model_bee1.tfl', 'cnn_image_model_bee1.tfl']
        loader_funs = [load_cnn_image_model_bee1,
                       load_cnn_image_model2_bee1,
                       load_cnn_image_model2_bee1]
        ensemble = load_tfl_net_ensemble(NET_PATH, ensemble_list, loader_funs)
        assert len(ensemble_list) == 3
        assert predict_with_tfl_ensemble(ensemble, BEE_valid_X[0], predict_with_tfl_cnn_image_model) == 1
    
if __name__ == '__main__':
    # unittest.main()
    validateAllEnsembles()
