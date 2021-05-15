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

# Rename 'num' column to 'disease' and change 1,2,3,4 to 1
df = df.rename({'num': 'disease'}, axis=1)
df['disease'] = df.disease.apply(lambda x: min(x, 1))
df = df[df['thal'] != '?']
df = df[df['ca'] != '?']
df['thal'] = df['thal'].astype('float64')
df['ca'] = df['ca'].astype('float64')


# %%
def modelFunc(x_TrainingSet, x_TestingSet, y_TrainingSet, knn):
    y_PredictionSet = []
    '''
        Return a ... y_PredictionSet...
        We are going to use the trainingset(x and y).
        Using those two sets, we are going to create a y_PredictionSet from the x_TestingSet
        So we need to build a list of binaries. This is simply our prediction given each x_Testing set
        So... Foreach x_testing rowData thing, we are going to find it's K-NearestNeighbors
        from the x_TrainingSet
        Then we are going to poll those nearest neighbors to see if they have heart disease.
        If the majority have heart disease then we put a 1 in the corresponding prediction array.
        Otherwise a 0


        ...
        ...
        This needs to be generalized a bit...
        given a df and some cols, we need to produce a report with the 10 score-reports, and 
        the mean f1 score per report.
    '''
    nn = NearestNeighbors(
        n_neighbors=knn, metric='euclidean', algorithm='auto')

    fit = nn.fit(x_TrainingSet)
    distances, indices = fit.kneighbors(x_TestingSet)
    for i in range(len(x_TestingSet)):
        nbrs = df.iloc[indices[i]]
        healthy = nbrs[nbrs.disease == 0].count().disease
        sick = nbrs[nbrs.disease == 1].count().disease
        predict = 0 if (healthy > sick) else 1
        actual = 0 if (y_TrainingSet[i] == 0) else 1
        success = predict == actual
        y_PredictionSet.append(success)
    return y_PredictionSet


# %%
# age,sex,cp,trestbps,chol,fbs,restecg,thalach,exang,oldpeak,slope,ca,thal,num
colNames = ["age", "sex", "cp", "trestbps", "chol", "fbs",
            "restecg", "thalach", "exang", "oldpeak", "slope", "ca", "thal"]
# Getting Stats

specialList = list(itertools.combinations(colNames, 2))


with open('output2.txt', 'a+') as myFile:
    for combo in specialList:
        someStringArr = []
        for name in combo:
            someStringArr.append(name)
        X = df[someStringArr].values
        y = df[['disease']].values

        myFile.write('HEADER: ' + str(someStringArr) + "\n")
        farr = []
        for i in range(10):
            X_train, X_test, y_train, y_test = train_test_split(
                X, y, test_size=0.25)
            y_pred = modelFunc(X_train, X_test, y_train, 21)
            (p, r, f, s) = precision_recall_fscore_support(
                y_test, y_pred, labels=[1])
            myFile.write('Iteration: ' + str(i+1).zfill(2) + " p: " +
                         str(p[0]).zfill(5) + " r: " + str(r[0]).zfill(5) + " f: " + str(f[0]).zfill(5) + "\n")
            farr.append(f)
        myFile.write("Fmean: " + str(np.mean(farr)).zfill(6) +
                     "\nKnn: " + str(21) + "\n\n")

# X = df[['age', 'trestbps', 'chol', 'thalach']].values
# y = df[['disease']].values

# # Use random_state if you want the same values each time you run for debugging,
# # but you should select the split randomly when you're ready to actually train
# # and test on the data.
# X_train, X_test, y_train, y_test = train_test_split(
#     X, y, test_size=0.25)  # , random_state=42)
# y_pred = modelFunc(X_train, X_test, y_train)
# # Build the model with the training data and test with the test data

# # You may also want to use this function to compute the f score. The labels parameter indicates
# # that label 1 is "positive" in the sense of "true positive", "false positive" etc.
# (p, r, f, s) = precision_recall_fscore_support(y_test, y_pred, labels=[1])

# print('FINAL REPORT1: ', p, r, f, s)
'''
Precision = TP/(TP+FP)
In this case... Out of all the patients queried, how many actually have heart disease
Recall = TP/(TP+FN)
In this case... Catching most diseased people
'''

# %%
import pandas as pd
from sklearn.metrics import precision_recall_fscore_support
from sklearn.model_selection import train_test_split
from sklearn.neighbors import NearestNeighbors
from statistics import mean
from itertools import combinations

# %%
df = pd.read_csv('student-mat.csv', ';')
columns = df.columns
target_column = 'G3'
median = df[target_column].median()
df[target_column] = df[target_column].apply(lambda x: 0 if x <= median else 1)

binary_values = [
    ('school', 'GP'), 
    ('sex', 'M'), 
    ('address', 'U'), 
    ('famsize', 'GT3'), 
    ('Pstatus', 'T'),
    ('schoolsup', 'yes'),
    ('famsup', 'yes'),
    ('paid', 'yes'),
    ('activities', 'yes'),
    ('nursery', 'yes'),
    ('higher', 'yes'),
    ('internet', 'yes'),
    ('romantic', 'yes'),
    ]
for column_name, value_1 in binary_values:
    df[column_name] = df[column_name].apply(lambda x: 1 if x == value_1 else 0)

del_values = [
    'Mjob', 
    'Fjob',
    'reason',
    'guardian',
    'G1',
    'G2'
    ]
for column_name in del_values:
    del df[column_name]

# %%
def model_func(selected_columns, target_column):
    x = df[selected_columns].values
    y = df[[target_column]].values

    iteration_count = 10
    knn = 32
    output = f'{selected_columns}\n'
    f_scores = []
    for _ in range(iteration_count):
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.1)
        y_pred = []
        nn = NearestNeighbors(n_neighbors=knn, metric='euclidean', algorithm='auto')
        fit = nn.fit(x_train)
        for point in x_test:
            distances, indices = fit.kneighbors(point.reshape(1, -1), n_neighbors=knn)
            nbrs = y_train[indices]
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
            y_pred.append(prediction)
        p, r, f, s = precision_recall_fscore_support(y_test, y_pred, labels=[1])
        f_scores.append(f[0])
        output += f'Precision: {p[0]}, Recall: {r[0]}, F-Score: {f[0]}, Support: {s[0]}\n'
    average_f_score = mean(f_scores)
    output += f'AVERAGE F-SCORE: {average_f_score}\n\n'
    return average_f_score, output

# %%
possible_columns = [column for column in df.columns if column != target_column]
with open('student_results.txt', 'w+') as f:
    best = [(0, []) for _ in range(32)]
    for column_count in range(1, 5):
        for combination in combinations(possible_columns, column_count):
            print(list(combination))
            average_f_score, output = model_func(list(combination), target_column)
            for i in range(len(best)):
                if average_f_score > best[i][0]:
                    best[i] = (average_f_score, combination, output)
                    break
    f.write('BEST F-SCORES:\n')
    for entry in best:
        f.write(f'{entry[1]} => {entry[0]}\n')
        f.write(f'{entry[2] if len(entry) > 2 else None}')
