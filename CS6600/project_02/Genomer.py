
import threading 
import pickle
import numpy as np
import tensorflow as tf
import tflearn
from tflearn.layers.core import input_data, fully_connected
from tflearn.layers.estimator import regression
import time
import os
import logging
import shutil
from random import seed
from random import random
from random import randint
import random
import time
import calendar
import copy

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
tf.get_logger().setLevel(logging.ERROR)


MIN_HIDDEN_LAYER_SIZE = 2

LEARNING_RATE_ARR1 = [    .1,     .075,     .05,     .025]
LEARNING_RATE_ARR2 = [   .01,    .0075,    .005,    .0025]
# LEARNING_RATE_ARR3 = [  .001,   .00075,   .0005,   .00025]


# BUZZ_DATA_DIRECTORY = "./bigData/BUZZ3/BUZZ3/"
# BUZZ_DATA_DIRECTORY = "./bigData/BUZZ2/BUZZ2/"
BUZZ_DATA_DIRECTORY = "./bigData/BUZZ1/BUZZ1/"

GENOME_MODELS_DIRECTORY = "./PopulationModels/"
CHILD_MODELS_DIRECTORY = "./ChildPopulationModels/"

GENOME_MODELS_DIRECTORY_DATA = "./PopulationModelsData/"
CHILD_MODELS_DIRECTORY_DATA = "./ChildPopulationModelsData/"

MODEL_DATA_FILE = "PopulationModelNames.txt"
CHILD_MODEL_DATA_FILE = "ChildModelNames.txt"

CHILD_GEN_DATA_FILE = "ChildGenModelNames.txt"

###############################################################################################################################################
################################################# BEGIN MODEL FUNCTIONS #######################################################################
###############################################################################################################################################

def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

def trainAudioAnnModel(model, train_X, train_Y, test_X, test_Y, num_epochs=25, batch_size=10):
    tf.reset_default_graph()
    model.fit(train_X, train_Y, n_epoch=num_epochs,
                shuffle=True,
                validation_set=(test_X, test_Y),
                show_metric=True,
                batch_size=batch_size,
                run_id='audio_ann_model')

def loadAudioAnnModelRetrain(hiddenLayerIdent, modelPath, currLearningRate):
    tf.reset_default_graph()
    fcLayerStringName = "fc_hidden_layer_"
    fclayerStringIndex = 1
    actualLayers = []

    input_layer = input_data(shape=[None, 4000, 1, 1])
    
    actualLayers.append(input_layer)

    for i in range(0, len(hiddenLayerIdent)):
        actualLayers.append(fully_connected(actualLayers[i], hiddenLayerIdent[i], activation='relu', name=fcLayerStringName+str(i)))

    output_layer = fully_connected(actualLayers[-1], 3, activation='softmax', name='output_layer')
    network = regression(output_layer, optimizer='sgd', loss='categorical_crossentropy', learning_rate=currLearningRate)
    model = tflearn.DNN(network)
    model.load(modelPath + str(hiddenLayerIdent))
    return model

def makeAudioAnnModel(someArr):
    tf.reset_default_graph()
    fcLayerStringName = "fc_hidden_layer_"
    fclayerStringIndex = 1
    actualLayers = []

    input_layer = input_data(shape=[None, 4000, 1, 1])
    
    actualLayers.append(input_layer)

    for i in range(0, len(someArr)):
        actualLayers.append(fully_connected(actualLayers[i], someArr[i], activation='relu', name=fcLayerStringName+str(i)))

    output_layer = fully_connected(actualLayers[-1], 3, activation='softmax', name='output_layer')
    network = regression(output_layer, optimizer='sgd', loss='categorical_crossentropy', learning_rate=0.1)
    model = tflearn.DNN(network)
    return model

def testAudioAnnModel(network_model, valid_X, valid_Y):
    results = []
    for i in range(len(valid_X)):
        prediction = network_model.predict(valid_X[i].reshape([-1, 4000, 1, 1]))
        results.append(np.argmax(prediction, axis=1)[0] == \
                       np.argmax(valid_Y[i]))
    return float(sum((np.array(results) == True))) / float(len(results))

###############################################################################################################################################
################################################# END MODEL FUNCTIONS #########################################################################
###############################################################################################################################################

###############################################################################################################################################
################################################# BEGIN GENETIC FUNCTIONS #####################################################################
###############################################################################################################################################

def getRandomVector():
    myRandomVector = []
    arrLen = randint(MIN_HIDDEN_LAYER_SIZE, 6)
    for i in range(arrLen):
        myRandomVector.append(randint(32, 512))
    return myRandomVector

# Takes in 2 arrays and returns two arrays.
# These 2 returned arrays have traits of both of the original arrays.
def mixNMatchArrays(array1, array2):
    returnArray1 = copy.deepcopy(array1)
    returnArray2 = copy.deepcopy(array2)

    arraysAreEqualSized = False
    array1IsSmaller = False
    if len(array1) == len(array2):
        arraysAreEqualSized = True
    
    if not arraysAreEqualSized:
        if len(array1) < len(array2):
            array1IsSmaller = True

    array1SubSet = []
    array2SubSet = []

    if arraysAreEqualSized:
        array1SubSet = getArraySubsetSmallerThan(len(array1), array1)
        array2SubSet = getArraySubsetSmallerThan(len(array2), array2)

    if not arraysAreEqualSized:
        if array1IsSmaller:
            array1SubSet = getArraySubsetSmallerThan(len(array1), array1)
            array2SubSet = getArraySubsetSmallerThan(len(array1), array2)
        else:
            array1SubSet = getArraySubsetSmallerThan(len(array2), array1)
            array2SubSet = getArraySubsetSmallerThan(len(array2), array2)

    arr1StartingChangeIndex = randint(0, len(array1) - len(array2SubSet))
    arr2StartingChangeIndex = randint(0, len(array2) - len(array1SubSet))

    arr1SubIndex = 0
    for i in range(arr1StartingChangeIndex, arr1StartingChangeIndex + len(array2SubSet), 1):
        returnArray1[i] = array2SubSet[arr1SubIndex]
        arr1SubIndex += 1
    
    arr2SubIndex = 0
    for i in range(arr2StartingChangeIndex, arr2StartingChangeIndex + len(array1SubSet), 1):
        returnArray2[i] = array1SubSet[arr2SubIndex]
        arr2SubIndex += 1
    return returnArray1, returnArray2

def getModelFitness(model):
    BUZZ_valid_X = load(BUZZ_DATA_DIRECTORY + 'valid_X.pck')
    BUZZ_valid_Y = load(BUZZ_DATA_DIRECTORY + 'valid_Y.pck')
    return testAudioAnnModel(model, BUZZ_valid_X, BUZZ_valid_Y)

def buildInitialGenomePopulation(size=10):
    populationList = []
    for i in range(0,size,1):
        genomeObject = []
        hiddenLayerArray = getRandomVector()
        modelObject = makeAudioAnnModel(hiddenLayerArray)
        fitness = getModelFitness(modelObject)
        genomeObject.append(hiddenLayerArray)
        genomeObject.append(modelObject)
        genomeObject.append(fitness)
        populationList.append(genomeObject)
    saveOffPopulationTuplesList(populationList, GENOME_MODELS_DIRECTORY, MODEL_DATA_FILE)

def getArraySubsetSmallerThan(thisInt, fromThisArray):
    arraySubSet = []
    randomSubSetSize = randint(1, thisInt-1)
    # Now I need a starting index from which I can start reading the values of the array randomSubSetSize times
    startingIndexPosition = randint(0, len(fromThisArray) - randomSubSetSize)
    for i in range(startingIndexPosition, startingIndexPosition + randomSubSetSize, 1):
        arraySubSet.append(fromThisArray[i])
    return arraySubSet

def mutateGenome(someGenome):
    genomeLen = len(someGenome)
    start = randint(0, genomeLen)
    end = randint(0, genomeLen)
    if start > end:
        temp = start
        start = end
        end = temp
    someGenome[start:end] = someGenome[start:end][::-1]
    if randint(1, 10) == 10:
        if randint(1, 4) > 2:
            someGenome.append(randint(32, 512))
        else:
            if genomeLen > MIN_HIDDEN_LAYER_SIZE:
                someGenome.remove(random.choice(someGenome))

def mateAndSelect(genome1, genome2):
    newGenome1 = []
    newGenome2 = []
    newGenome1, newGenome2 = mixNMatchArrays(genome1, genome2)
    if(randint(0, 25) == 16):
        mutateGenome(newGenome1)
    if(randint(0, 25) == 16):
        mutateGenome(newGenome2)
    return newGenome1, newGenome2

def buildGeneologyAndChildrenFromParents(parentHiddenLayerArrs):
    childGeneologyTuplesList = []
    for parent in parentHiddenLayerArrs:
        childParentList = []
        mate = randint(0, len(parentHiddenLayerArrs)-1)
        child1 = []
        child2 = []
        child1, child2 = mateAndSelect(parent, parentHiddenLayerArrs[mate])
        childParentList.append(child1)
        childParentList.append(parent)
        childGeneologyTuplesList.append(childParentList)
    return childGeneologyTuplesList

###############################################################################################################################################
################################################# END GENETIC FUNCTIONS #######################################################################
###############################################################################################################################################

###############################################################################################################################################
################################################# BEGIN UTILITY FUNCTIONS #####################################################################
###############################################################################################################################################

def singleThreadedModelTrainerSaver(model, identArray, learningRateValue, modelsDirectory, modelsDataDirectory):
    BUZZ_train_X = load(BUZZ_DATA_DIRECTORY + 'train_X.pck')
    BUZZ_train_Y = load(BUZZ_DATA_DIRECTORY + 'train_Y.pck')
    BUZZ_test_X = load(BUZZ_DATA_DIRECTORY + 'test_X.pck')
    BUZZ_test_Y = load(BUZZ_DATA_DIRECTORY + 'test_Y.pck')

    BUZZ_train_X = BUZZ_train_X.reshape([-1, 4000, 1, 1])
    BUZZ_test_X  = BUZZ_test_X.reshape([-1, 4000, 1, 1])

    trainAudioAnnModel(model, BUZZ_train_X, BUZZ_train_Y, BUZZ_test_X, BUZZ_test_Y)
    model.save(modelsDirectory + str(identArray))
    modelFitness = getModelFitness(model)
    with open(modelsDataDirectory + str(identArray) + '.txt', 'a') as filehandle:
        filehandle.write(str(learningRateValue).zfill(7) + " : " + str(modelFitness) + "\n")

def trainAndSaveModelPopulationWithThreads(modelsArr, hiddenLayerIdentArr, learningRateValue, modelsDirectory, dataDirectory):
    numModels = len(modelsArr)

    for i in range(0,numModels, 10):
        t0 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+0],hiddenLayerIdentArr[i+0],learningRateValue,modelsDirectory,dataDirectory,)) 
        t1 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+1],hiddenLayerIdentArr[i+1],learningRateValue,modelsDirectory,dataDirectory,)) 
        t2 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+2],hiddenLayerIdentArr[i+2],learningRateValue,modelsDirectory,dataDirectory,)) 
        t3 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+3],hiddenLayerIdentArr[i+3],learningRateValue,modelsDirectory,dataDirectory,)) 
        t4 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+4],hiddenLayerIdentArr[i+4],learningRateValue,modelsDirectory,dataDirectory,))
        t5 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+5],hiddenLayerIdentArr[i+5],learningRateValue,modelsDirectory,dataDirectory,)) 
        t6 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+6],hiddenLayerIdentArr[i+6],learningRateValue,modelsDirectory,dataDirectory,)) 
        t7 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+7],hiddenLayerIdentArr[i+7],learningRateValue,modelsDirectory,dataDirectory,)) 
        t8 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+8],hiddenLayerIdentArr[i+8],learningRateValue,modelsDirectory,dataDirectory,)) 
        t9 = threading.Thread(target=singleThreadedModelTrainerSaver, args=(modelsArr[i+9],hiddenLayerIdentArr[i+9],learningRateValue,modelsDirectory,dataDirectory,))

        t0.start()
        t1.start() 
        t2.start()
        t3.start() 
        t4.start()
        t5.start()
        t6.start()
        t7.start()
        t8.start()
        t9.start()

        t0.join()
        t1.join() 
        t2.join()
        t3.join() 
        t4.join()
        t5.join()
        t6.join()
        t7.join()
        t8.join()
        t9.join()

def getHiddenLayerIntArraysFromPopulationFile(populationFile):
    hiddenIdentList = []
    with open(populationFile, 'r') as filehandle:
        populationSize = int(filehandle.readline())
        for i in range(populationSize):
            someList = list(str(filehandle.readline()).split())
            intList = []
            for element in someList:
                intList.append(int(element))
            hiddenIdentList.append(intList)
    return hiddenIdentList

def getModelsWithLearningRate(hiddenLayerIdentArr, currLearningRate, modelsDirectory):
    modelsArr = []
    for identity in hiddenLayerIdentArr:
        modelsArr.append(loadAudioAnnModelRetrain(list(identity), modelsDirectory, currLearningRate))
    return modelsArr

def trainPopulationFromFile(populationFile, modelsDirectory, modelDataDirectory):
    hiddenLayerIdentArr = getHiddenLayerIntArraysFromPopulationFile(populationFile)
    for learningRateValue in LEARNING_RATE_ARR1:
        modelsArr = getModelsWithLearningRate(hiddenLayerIdentArr, learningRateValue, modelsDirectory)
        trainAndSaveModelPopulationWithThreads(modelsArr, hiddenLayerIdentArr, learningRateValue, modelsDirectory, modelDataDirectory)
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n ENTER ENTER ENTER ENTER \n\n\n\n\n')

    for learningRateValue in LEARNING_RATE_ARR2:
        modelsArr = getModelsWithLearningRate(hiddenLayerIdentArr, learningRateValue, modelsDirectory)
        trainAndSaveModelPopulationWithThreads(modelsArr, hiddenLayerIdentArr, learningRateValue, modelsDirectory, modelDataDirectory)
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n*************************************************')
        print('\n ENTER ENTER ENTER ENTER \n\n\n\n\n')

def loadmodelsArr():
    populationList = []
    hiddenIdentList = []
    modelList = []
    with open(MODEL_DATA_FILE, 'r') as filehandle:
        populationSize = int(filehandle.readline())
        for i in range(populationSize):
            someList = list(str(filehandle.readline()).split())
            intList = []
            for element in someList:
                intList.append(int(element))
            hiddenIdentList.append(intList)
            
        for identity in hiddenIdentList:
            modelList.append(loadAudioAnnModel(list(identity),GENOME_MODELS_DIRECTORY))
    
    identCounter = -1
    for model in modelList:
        identCounter += 1
        genomeObject = []
        genomeObject.append(hiddenIdentList[identCounter])
        genomeObject.append(model)
        genomeObject.append(getModelFitness(model))
        populationList.append(genomeObject)
    return populationList

def saveOffPopulationTuplesList(populationList, saveDirectory, saveFile):
    for entity in populationList:
        entity[1].save(saveDirectory + str(entity[0]))
    with open(saveFile, 'w') as filehandle:
        filehandle.write(str(len(populationList)) + "\n")
        for entity in populationList:
            for intValue in entity[0]:
                filehandle.write(str(intValue) + ' ')
            filehandle.write('\n')
        for thing in populationList:
            filehandle.write(str(thing[2]) + '\n')

def breedChildrenFromPrincipalPopulation():
    parentHiddenLayerArrs = getHiddenLayerIntArraysFromPopulationFile(MODEL_DATA_FILE)
    childGenerationalTuplesArr = buildGeneologyAndChildrenFromParents(parentHiddenLayerArrs) # [(Child, Parent),...]
    pureChildArr = []
    with open(CHILD_GEN_DATA_FILE, 'w') as filehandle:
        filehandle.write(str(len(childGenerationalTuplesArr)) + "\n")
        for thing in childGenerationalTuplesArr:
            for intValue in thing[0]:
                filehandle.write(str(intValue) + ' ')
            filehandle.write('\n')
            for intValue in thing[1]:
                filehandle.write(str(intValue) + ' ')
            filehandle.write('\n')
            pureChildArr.append(thing[0])
    childPopulationArr = []
    for child in pureChildArr:
        genomeObject = []
        hiddenLayerArray = child
        modelObject = makeAudioAnnModel(child)
        fitness = getModelFitness(modelObject)
        genomeObject.append(hiddenLayerArray)
        genomeObject.append(modelObject)
        genomeObject.append(fitness)
        childPopulationArr.append(genomeObject)
    saveOffPopulationTuplesList(childPopulationArr, CHILD_MODELS_DIRECTORY, CHILD_MODEL_DATA_FILE)
    
def getChildParentArrayFromFile():
    parentChildList = []
    with open(CHILD_GEN_DATA_FILE, 'r') as filehandle:
        populationSize = int(filehandle.readline())
        for i in range(populationSize):
            child = []          
            someList = list(str(filehandle.readline()).split())
            for element in someList:
                child.append(int(element))
            
            parent = []
            anotherList = list(str(filehandle.readline()).split())
            for element in anotherList:
                parent.append(int(element))
            parentChildElement = []
            parentChildElement.append(child)
            parentChildElement.append(parent)
            parentChildList.append(parentChildElement)
    return parentChildList

def replaceParentWithChild(cpCombo):
    # Remove the files that start with the parent array
    # move in the files that start with the child array
    childArr = cpCombo[0]
    parentArr = cpCombo[1]
    childFiles = getFilesInSubDir(CHILD_MODELS_DIRECTORY)
    parentFiles = getFilesInSubDir(GENOME_MODELS_DIRECTORY)

    for singleFile in parentFiles:
        if (singleFile).startswith(str(parentArr)):
            os.remove(os.path.join(GENOME_MODELS_DIRECTORY, str(singleFile)))

    for singleFile in childFiles:
        if str(singleFile).startswith(str(childArr)):
            os.rename(os.path.join(CHILD_MODELS_DIRECTORY + str(singleFile)), os.path.join(GENOME_MODELS_DIRECTORY + str(singleFile)))

def reprintPopulationModelNamesFile(newParentArray):
    with open(MODEL_DATA_FILE, 'w') as filehandle:
        filehandle.write(str(len(newParentArray)) + "\n")
        for newParent in newParentArray:
            for intValue in newParent:
                filehandle.write(str(intValue) + ' ')
            filehandle.write('\n')
        for newParent in newParentArray:
            filehandle.write(str(getModelFitness(loadAudioAnnModelRetrain(newParent, GENOME_MODELS_DIRECTORY, .00001))) + '\n')


def supercedePrincipalPopulation():
    # Compare the validation accuracies of the child and the parent,
    # If the child is better than the parent, then move the child into the parent directory and delete the parent
    childParentArray = getChildParentArrayFromFile()
    childArray = []
    parentArray = []
    for cpCombo in childParentArray:
        childArray.append(cpCombo[0])
        parentArray.append(cpCombo[1])
        
    for cpCombo in childParentArray:
        childModel = loadAudioAnnModelRetrain(list(cpCombo[0]), CHILD_MODELS_DIRECTORY, .00001)
        parentModel = loadAudioAnnModelRetrain(list(cpCombo[1]), GENOME_MODELS_DIRECTORY, .00001)
        childVacc = getModelFitness(childModel)
        parentVacc = getModelFitness(parentModel)
        if childVacc > parentVacc:
            parentArray.remove(cpCombo[1])
            parentArray.append(cpCombo[0])
            replaceParentWithChild(cpCombo)
    reprintPopulationModelNamesFile(parentArray)

def getFilesInSubDir(myDirPath):
    return [f for f in os.listdir(myDirPath) if os.path.isfile(os.path.join(myDirPath, f))]

def deleteChildInfo():
    remainingChildModels = getFilesInSubDir(CHILD_MODELS_DIRECTORY)
    oldChildDataFiles = getFilesInSubDir(CHILD_MODELS_DIRECTORY_DATA)
    oldPopulationDataFiles = getFilesInSubDir(GENOME_MODELS_DIRECTORY_DATA)
    for singleFile in remainingChildModels:
        os.remove(os.path.join(CHILD_MODELS_DIRECTORY, str(singleFile)))
    for singleFile in oldChildDataFiles:
        os.remove(os.path.join(CHILD_MODELS_DIRECTORY_DATA, str(singleFile)))
    for singleFile in oldPopulationDataFiles:
        os.remove(os.path.join(GENOME_MODELS_DIRECTORY_DATA, str(singleFile)))


###############################################################################################################################################
################################################# END UTILITY FUNCTIONS #####################################################################
###############################################################################################################################################



'''
Probable flow of program...
1. Build initial population of tuple objects
    a. Each tuple has a hidden layer representational array, model, "trained-fitness"
2. Save off the population of models
3. In batches of 10, readin 10 models and train them for some amount of time
4. When finished with the training, save the "trained" model population
5. Update the fitness, and model of every tuple
    a. Save off the current tuple population
6. Mate Genomes together, I will need to mate so many, and 
'''


def main():
    currentSeed = calendar.timegm(time.gmtime())
    seed(currentSeed)

    # buildInitialGenomePopulation(size=50) # IN MULTIPLES OF 10 ONLY

    # trainPopulationFromFile(MODEL_DATA_FILE, GENOME_MODELS_DIRECTORY, GENOME_MODELS_DIRECTORY_DATA)







    breedChildrenFromPrincipalPopulation()

    trainPopulationFromFile(CHILD_MODEL_DATA_FILE, CHILD_MODELS_DIRECTORY, CHILD_MODELS_DIRECTORY_DATA)

    supercedePrincipalPopulation()

    deleteChildInfo()



    # for i in range(0, 10):
    # while True:
    #     myFav = ['0','1']
    #     mutateGenome(myFav)
    #     input(str(myFav))




if __name__ == "__main__":
    main()