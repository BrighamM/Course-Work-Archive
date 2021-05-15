# %%
import math
from sklearn.metrics import precision_recall_fscore_support
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
from sklearn.neighbors import NearestNeighbors
import random
import itertools

import matplotlib.pyplot as plt
# sklearn.model_selection.train_test_split

# %%
# Comma-separated values
df = pd.read_csv('cleveland.csv')
df2 = pd.read_csv('cleveland-test.csv')

# Rename 'num' column to 'disease' and change 1,2,3,4 to 1
df = df.rename({'num': 'disease'}, axis=1)
df['disease'] = df.disease.apply(lambda x: min(x, 1))
df = df[df['thal'] != '?']
df = df[df['ca'] != '?']
df['thal'] = df['thal'].astype('float64')
df['ca'] = df['ca'].astype('float64')

df2 = df2.rename({'num': 'disease'}, axis=1)
df2['disease'] = df2.disease.apply(lambda x: min(x, 1))
df2 = df2[df2['thal'] != '?']
df2 = df2[df2['ca'] != '?']
df2['thal'] = df2['thal'].astype('float64')
df2['ca'] = df2['ca'].astype('float64')


# %%


def modelFunc(x_TrainingSet, x_TestingSet, y_TrainingSet, knn):
    y_PredictionSet = []
    nn = NearestNeighbors(
        n_neighbors=knn, metric='euclidean', algorithm='auto')

    fit = nn.fit(x_TrainingSet)
    for point in x_TestingSet:

        distances, indices = fit.kneighbors(
            point.reshape(1, -1), n_neighbors=knn)

        nbrs = y_TrainingSet[indices]
        heathyCount = 0
        diseaseCount = 0
        for thing in nbrs[0]:
            if int(thing) == 1:
                heathyCount = heathyCount + 1
            if int(thing) == 0:
                diseaseCount = diseaseCount + 1

        prediction = 0
        if diseaseCount > heathyCount:
            prediction = 1

        y_PredictionSet.append(prediction)
    return y_PredictionSet


# %%
# age,sex,cp,trestbps,chol,fbs,restecg,thalach,exang,oldpeak,slope,ca,thal,num
colNames = ["age", "sex", "cp", "trestbps", "chol", "fbs",
            "restecg", "thalach", "exang", "oldpeak", "slope", "ca", "thal"]
# Getting Stats

subStringArr = ['trestbps', 'chol', 'restecg']
# kList = range(4, 100)

# with open('output.txt', 'a+') as myFile:
#     # for combo in specialList:
#     #     someStringArr = []
#     #     for name in combo:
#     #         someStringArr.append(name)
X_train = df[subStringArr].values
y_train = df[['disease']].values

X_test = df2[subStringArr].values
y_test = df2[['disease']].values
#     myFile.write('p,r,f,k' + '\n')
#     for kValue in kList:
#         for i in range(100):
# X_train, X_test, y_train, y_test = train_test_split(
#     X, y, test_size=0.25)
y_pred = modelFunc(X_train, X_test, y_train, 32)
(p, r, f, s) = precision_recall_fscore_support(
    y_test, y_pred, labels=[1])
print(str(p[0]) + "," + str(r[0]) + "," +
      str(f[0]) + "," + str(32) + "\n")


# specialList = list(itertools.combinations(colNames, 2))
# kList = [4, 8, 16, 32]

# with open('output2.txt', 'a+') as myFile:
#     for combo in specialList:
#         someStringArr = []
#         for name in combo:
#             someStringArr.append(name)
#         X = df[someStringArr].values
#         y = df[['disease']].values

#         for kValue in kList:
#             myFile.write('HEADER: ' + str(someStringArr) + "\n")
#             farr = []
#             for i in range(10):
#                 X_train, X_test, y_train, y_test = train_test_split(
#                     X, y, test_size=0.25)
#                 y_pred = modelFunc(X_train, X_test, y_train, kValue)
#                 (p, r, f, s) = precision_recall_fscore_support(
#                     y_test, y_pred, labels=[1])
#                 myFile.write('Iteration: ' + str(i+1).zfill(2) + " p: " +
#                              str(p[0]).zfill(6)[:6] + " r: " + str(r[0]).zfill(6)[:6] + " f: " + str(f[0]).zfill(6)[:6] + "\n")
#                 farr.append(f)
#             myFile.write("Fmean: " + str(np.mean(farr)).zfill(6)[:6] +
#                          "\nKnn: " + str(kValue) + "\n\n")

# specialList = list(itertools.combinations(colNames, 3))
# kList = [4, 8, 16, 32]

# with open('output3.txt', 'a+') as myFile:
#     for combo in specialList:
#         someStringArr = []
#         for name in combo:
#             someStringArr.append(name)
#         X = df[someStringArr].values
#         y = df[['disease']].values

#         for kValue in kList:
#             myFile.write('HEADER: ' + str(someStringArr) + "\n")
#             farr = []
#             for i in range(10):
#                 X_train, X_test, y_train, y_test = train_test_split(
#                     X, y, test_size=0.25)
#                 y_pred = modelFunc(X_train, X_test, y_train, kValue)
#                 (p, r, f, s) = precision_recall_fscore_support(
#                     y_test, y_pred, labels=[1])
#                 myFile.write('Iteration: ' + str(i+1).zfill(2) + " p: " +
#                              str(p[0]).zfill(6)[:6] + " r: " + str(r[0]).zfill(6)[:6] + " f: " + str(f[0]).zfill(6)[:6] + "\n")
#                 farr.append(f)
#             myFile.write("Fmean: " + str(np.mean(farr)).zfill(6)[:6] +
#                          "\nKnn: " + str(kValue) + "\n\n")

# specialList = list(itertools.combinations(colNames, 4))
# kList = [4, 8, 16, 32]

# with open('output4.txt', 'a+') as myFile:
#     for combo in specialList:
#         someStringArr = []
#         for name in combo:
#             someStringArr.append(name)
#         X = df[someStringArr].values
#         y = df[['disease']].values

#         for kValue in kList:
#             myFile.write('HEADER: ' + str(someStringArr) + "\n")
#             farr = []
#             for i in range(10):
#                 X_train, X_test, y_train, y_test = train_test_split(
#                     X, y, test_size=0.25)
#                 y_pred = modelFunc(X_train, X_test, y_train, kValue)
#                 (p, r, f, s) = precision_recall_fscore_support(
#                     y_test, y_pred, labels=[1])
#                 myFile.write('Iteration: ' + str(i+1).zfill(2) + " p: " +
#                              str(p[0]).zfill(6)[:6] + " r: " + str(r[0]).zfill(6)[:6] + " f: " + str(f[0]).zfill(6)[:6] + "\n")
#                 farr.append(f)
#             myFile.write("Fmean: " + str(np.mean(farr)).zfill(6)[:6] +
#                          "\nKnn: " + str(kValue) + "\n\n")

# specialList = list(itertools.combinations(colNames, 5))
# kList = [4, 8, 16, 32]

# with open('output5.txt', 'a+') as myFile:
#     for combo in specialList:
#         someStringArr = []
#         for name in combo:
#             someStringArr.append(name)
#         X = df[someStringArr].values
#         y = df[['disease']].values

#         for kValue in kList:
#             myFile.write('HEADER: ' + str(someStringArr) + "\n")
#             farr = []
#             for i in range(10):
#                 X_train, X_test, y_train, y_test = train_test_split(
#                     X, y, test_size=0.25)
#                 y_pred = modelFunc(X_train, X_test, y_train, kValue)
#                 (p, r, f, s) = precision_recall_fscore_support(
#                     y_test, y_pred, labels=[1])
#                 myFile.write('Iteration: ' + str(i+1).zfill(2) + " p: " +
#                              str(p[0]).zfill(6)[:6] + " r: " + str(r[0]).zfill(6)[:6] + " f: " + str(f[0]).zfill(6)[:6] + "\n")
#                 farr.append(f)
#             myFile.write("Fmean: " + str(np.mean(farr)).zfill(6)[:6] +
#                          "\nKnn: " + str(kValue) + "\n\n")

# %%
