# %%
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import statsmodels.formula.api as smf
import numpy as np
from sklearn.metrics import precision_recall_fscore_support
import random
from sklearn.linear_model import LogisticRegression

# %%
df = pd.read_csv('./adultdata.csv')
df.head()

# %%
df2 = pd.get_dummies(df['workclass'], prefix="workclass").astype('int')
df = df.join(df2, how="outer")

df2 = pd.get_dummies(df['education'], prefix="education").astype('int')
df = df.join(df2, how="outer")

df2 = pd.get_dummies(df['maritalstatus'],
                     prefix="maritalstatus").astype('int')
df = df.join(df2, how="outer")

df2 = pd.get_dummies(df['occupation'], prefix="occupation").astype('int')
df = df.join(df2, how="outer")

df2 = pd.get_dummies(df['relationship'], prefix="relationship").astype('int')
df = df.join(df2, how="outer")

df2 = pd.get_dummies(df['race'], prefix="race").astype('int')
df = df.join(df2, how="outer")

df['income'] = df['income'].astype('int')
df['sex'] = df['sex'].astype('int')

# df = df.drop(['workclass', 'education', 'maritalstatus', 'occupation',
#               'relationship', 'race', 'native-country'], axis=1)


# %%
pd.set_option('display.max_columns', None)
df.head()
# %%
X = df[['age', 'hoursperweek']]
y = df.income
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))

# %%
color = ['r' if y_ == 0 else 'b' for y_ in y]

plt.plot(Xdb, ydb)

plt.scatter(df.educationnum, df.age, c=color, s=3)
plt.xlabel('educationnum')
plt.ylabel('age')

# %%
color = ['r' if y_ == 0 else 'b' for y_ in y]
plt.scatter(df.educationnum, df.hoursperweek, c=color, s=3)
plt.xlabel('educationnum')
plt.ylabel('hoursperweek')

# %%
color = ['r' if y_ == 0 else 'b' for y_ in y]
plt.scatter(df.age, df.hoursperweek, c=color, s=3)
plt.xlabel('age')
plt.ylabel('hoursperweek')

# %%
