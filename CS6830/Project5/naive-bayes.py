# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %% [markdown]
# This example is taken from the gender identification example at https://www.nltk.org/book/ch06.html

# %%
from sklearn.model_selection import train_test_split
import nltk
from nltk.corpus import names
import random
from sklearn.metrics import precision_recall_fscore_support

# %% [markdown]
# # A first try at Naive Bayes classification using NLTK
# %% [markdown]
# ### Feature extractor
# We will use one feature from a name: the last letter

# %%
def gender_features(word):
    return {'last_letter': word[-1]}
gender_features('Stanley')

# %% [markdown]
# ### Examples
# Prepare a list of examples with corresponding class labels

# %%
# display(names.words('male.txt'))

male = [(name, 'male') for name in names.words('male.txt')]
female = [(name, 'female') for name in names.words('female.txt')]
labeled_names = male + female

random.shuffle(labeled_names)
labeled_names

# %% [markdown]
# ### Training/test data
# Use the feature extractor to prepare training and testing data

# %%
featuresets = [(gender_features(name), gender) for (name, gender) in labeled_names]
# train_set, test_set = featuresets[500:], featuresets[:500]
train_set, test_set = train_test_split(featuresets)
# display(train_set[:3])

# Uses multinomial naive Bayes classifier
classifier = nltk.NaiveBayesClassifier.train(train_set)

#%%
featuresets

# %% [markdown]
# ### Try it out on a few names

# %%
print(classifier.classify(gender_features('Neo')))
print(classifier.classify(gender_features('Trinity')))
print(classifier.classify(gender_features('Amy')))
print(classifier.classify(gender_features('Andy')))
print(classifier.classify(gender_features('Laren')))

# %% [markdown]
# ### Check precision/recall

#%%
list(zip(*test_set[:5]))
# %%

y_true = list(list(zip(*test_set))[1])
test_features = list(list(zip(*test_set))[0])
y_predict = [classifier.classify(features) for features in test_features]


(p,r,f,s) = precision_recall_fscore_support(y_true, y_predict, labels=['male'])
print(p,r,f,s)

# %% [markdown]
# ### Likelihood ratios
# Names in the training set that end in "a" are female 34 times more often than they are male.

# %%
classifier.show_most_informative_features(5)

# %% [markdown]
# # Can we do better?
# Update the feature extractor to see if we can do better.

# %%
from nltk.metrics.scores import (precision, recall)

def gender_features(name):
    features = {}
    features["first_letter"] = name[0].lower()
    features["last_letter"] = name[-1].lower()
    for letter in 'abcdefghijklmnopqrstuvwxyz':
        features["count({})".format(letter)] = name.lower().count(letter)
        features["has({})".format(letter)] = (letter in name.lower())
    return features

gender_features('Hephzibah')


# %%
featuresets = [(gender_features(name), gender) for (name, gender) in labeled_names]
train_set, test_set = train_test_split(featuresets)
classifier = nltk.NaiveBayesClassifier.train(train_set)

print(classifier.classify(gender_features('Neo')))
print(classifier.classify(gender_features('Trinity')))
print(classifier.classify(gender_features('Amy')))
print(classifier.classify(gender_features('Andy')))


# %%
# print(nltk.classify.accuracy(classifier, test_set))
y_true = list(list(zip(*test_set))[1])
test_features = list(list(zip(*test_set))[0])
y_predict = [classifier.classify(features) for features in test_features]
(p,r,f,s) = precision_recall_fscore_support(y_true, y_predict)
print(p,r,f,s)

# Names with the last letter of 'k' are 34.8 times more likely to be male names than female.
classifier.show_most_informative_features(15)

# %% [markdown]
# # Gaussian Naive Bayes Classifer
# This type of classifer works with quantitative variables (numbers)
# 
# ## We'll do it with sklearn
# 
# Adapted from https://scikit-learn.org/stable/modules/naive_bayes.html

# %%
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_recall_fscore_support
from sklearn import datasets
from sklearn.naive_bayes import GaussianNB

iris = datasets.load_iris()
print(iris.keys())

# Use Gaussian for datasets with quantitative variables
clf = GaussianNB()

X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.25)
clf.fit(X_train, y_train)
y_pred = clf.predict(X_test)
p,r,f,s = precision_recall_fscore_support(y_test, y_pred)
print(p, r, f, s)


# %%
X_train
y_train

# %% [markdown]
# ## What if we have categorical and quantitative data? Then we use a label encoder to convert
# categorical variables to quantitative "dummy" variables.
# This is known as one-hot encoding

# %%
from sklearn import preprocessing
import numpy as np
alphabet = 'abcdefghijklmnopqrstuvwxyz'
le = preprocessing.LabelEncoder()

# Initialize the label encoder
le.fit([l for l in alphabet])

# Create a feature vector with all zeros, one for each letter of the alphabet
# a b c d ... x y z
# 0 0 0 0 ... 0 0 0
features = np.zeros(len(alphabet))
features


# %%
# Use the label encoder to get the index of the feature
var_index = le.transform(['c'])
var_index


# %%
# Mark the 'c' feature as present
# a b c d ... x y z
# 0 0 1 0 ... 0 0 0
features[var_index] = 1
display(features)


# %%
# Mark the 'd' and 'x' features as present
# a b c d ... x y z
# 0 0 1 1 ... 1 0 0
features[le.transform(['d'])] = 1
features[le.transform(['x'])] = 1

features[le.transform(['a','b'])] = 1

display(features)

# %% [markdown]
# Do the name example again with a Gaussian Naive Bayes Classifier, using dummy variables to account for the categorical variables.

# %%
from sklearn.naive_bayes import GaussianNB
from sklearn.naive_bayes import MultinomialNB
from sklearn import preprocessing
from sklearn.metrics import precision_recall_fscore_support
import numpy
import numpy as np

alphabet = 'abcdefghijklmnopqrstuvwxyz'
le = preprocessing.LabelEncoder()
le.fit([l for l in alphabet])

def gender_features(name):
    features = []
    first = name[0].lower()
    last = name[-1].lower()

    a = np.zeros(len(alphabet))
    a[le.transform([first])[0]] = 1
    features.extend(a)

    a = np.zeros(len(alphabet))
    if alphabet.find(last) > -1:
        a[le.transform([last])[0]] = 1
    features.extend(a)

    for letter in 'abcdefghijklmnopqrstuvwxyz':
        features.append(name.lower().count(letter))
        features.append(letter in name.lower())
    return features


# display(gender_features("Hank"))

random.shuffle(labeled_names)
X = [gender_features(name) for (name, _) in labeled_names]
y = [gender for (_, gender) in labeled_names]
X

X_train, X_test = X[500:], X[:500]
y_train, y_test = y[500:], y[:500]

clf = GaussianNB()
# clf = MultinomialNB() # Use multinomial for text classification

clf.fit(X_train, y_train).predict(X_test)
y_pred = clf.predict(X_test)

p,r,f,s = precision_recall_fscore_support(y_test, y_pred)
print(p, r, f)                                                

# %% [markdown]
# # OneHotEncoder from sklearn

# %%
from sklearn.preprocessing import OneHotEncoder

enc = OneHotEncoder(handle_unknown='ignore')
# The dataset. There are two features: gender and years of postsecondary education
X = [['Male', 1], ['Female', 3], ['Female', 2], ['Female', 6]]
enc.fit(X)

# features are [female, male, 1, 2, 3, 6]
print(enc.categories_)


# %%
# Encode three data points. Note that the last data point doesn't have any entry for 1, 2, or 3
feature_vectors = enc.transform([['Female', 1], ['Male', 2], ['Male', 4]]).toarray()
print(feature_vectors)

# Get the semantic meaning for two encoded data points
enc.inverse_transform([[0, 1, 1, 0, 0, 0], [1, 0, 0, 1, 0, 0]])


