# %%
from sklearn.model_selection import train_test_split
import nltk
from nltk.corpus import names
import random
from sklearn.metrics import precision_recall_fscore_support
import math
from sklearn.metrics import precision_recall_fscore_support
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
from sklearn.neighbors import NearestNeighbors
import random
import itertools
from sklearn.naive_bayes import GaussianNB
# %%
# Go to this link to learn more stuff. https://www.nltk.org/book/ch06.html
df = pd.read_csv('./Data/cardata.csv')
df.head()

# %%
df.loc[(df.buying == 'vhigh'), 'buying'] = '4'
df.loc[(df.buying == 'high'), 'buying'] = '3'
df.loc[(df.buying == 'med'), 'buying'] = '2'
df.loc[(df.buying == 'low'), 'buying'] = '1'
df.loc[(df.maint == 'vhigh'), 'maint'] = '4'
df.loc[(df.maint == 'high'), 'maint'] = '3'
df.loc[(df.maint == 'med'), 'maint'] = '2'
df.loc[(df.maint == 'low'), 'maint'] = '1'
df.loc[(df.trunk_size == 'big'), 'trunk_size'] = '3'
df.loc[(df.trunk_size == 'med'), 'trunk_size'] = '2'
df.loc[(df.trunk_size == 'small'), 'trunk_size'] = '1'
df.loc[(df.safety == 'high'), 'safety'] = '3'
df.loc[(df.safety == 'med'), 'safety'] = '2'
df.loc[(df.safety == 'low'), 'safety'] = '1'
df.loc[(df.deal_index == 'vgood'), 'deal_index'] = '3'  # was 3
df.loc[(df.deal_index == 'good'), 'deal_index'] = '2'  # was 2
df.loc[(df.deal_index == 'acc'), 'deal_index'] = '1'
df.loc[(df.deal_index == 'unacc'), 'deal_index'] = '0'

df['Seats2'] = np.where(df['persons'] == '2', 1, 0)
df['Seats4'] = np.where(df['persons'] == '4', 1, 0)
df['Seats4_plus'] = np.where(df['persons'] == 'more', 1, 0)
df['2doors'] = np.where(df['doors'] == '2', 1, 0)
df['3doors'] = np.where(df['doors'] == '3', 1, 0)
df['4doors'] = np.where(df['doors'] == '4', 1, 0)
df['5_plusdoors'] = np.where(df['doors'] == '5more', 1, 0)
df = df.drop('doors', 1)
df = df.drop('persons', 1)

df['buying'] = df['buying'].astype('int')
df['maint'] = df['maint'].astype('int')
df['trunk_size'] = df['trunk_size'].astype('int')
df['safety'] = df['safety'].astype('int')
df['deal_index'] = df['deal_index'].astype('int')
df['Seats2'] = df['Seats2'].astype('int')
df['Seats4'] = df['Seats4'].astype('int')
df['Seats4_plus'] = df['Seats4_plus'].astype('int')
df['2doors'] = df['2doors'].astype('int')
df['3doors'] = df['3doors'].astype('int')
df['4doors'] = df['4doors'].astype('int')
df['5_plusdoors'] = df['5_plusdoors'].astype('int')

df.head(23)

# %%
# print("hi")
# statTable = df
# statTable[(statTable.buying == 1) & (statTable.maint == 1)
#           & (statTable.deal_index == 3)]

# %%
clf = GaussianNB()
theData = df.drop('deal_index', 1)
theKeys = df['deal_index']

X_train, X_test, y_train, y_test = train_test_split(
    theData, theKeys)
clf.fit(X_train, y_train).predict(X_test)
y_pred = clf.predict(X_test)
p, r, f, s = precision_recall_fscore_support(y_test, y_pred)
print(p, r, f, s)

# %%
