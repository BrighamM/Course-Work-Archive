# %%
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import statsmodels.formula.api as smf
from IPython import get_ipython
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import precision_recall_fscore_support
import random
from sklearn.linear_model import LogisticRegression

# %%
df = pd.read_csv('parkinsons.csv')

# %%
parkinsons = df.loc[df['status'] == 1]
healthy = df.loc[df['status'] == 0]

# %%


#stronger correlation for healthy
# sns.regplot(x="MDVP:Fo(Hz)", y="DFA", data=healthy)
# sns.regplot(x="MDVP:Fo(Hz)", y="DFA", data=parkinsons)

#stronger correlation for sick
# sns.regplot(x="spread1", y="spread2", data=healthy, label="Healthy")
# sns.regplot(x="spread1", y="spread2", data=parkinsons, label="Parkinsons")
# plt.legend()

# sns.scatterplot(x="spread1", y="PPE", data=healthy, label="Healthy")
# sns.scatterplot(x="spread1", y="PPE", data=parkinsons, label="Parkinsons")
# plt.legend()
# plt.title("Non-linear frequencies")
# plt.savefig("Nonlinear Frequencies")
sns.scatterplot(x="MDVP:Flo(Hz)", y="MDVP:Fhi(Hz)", data=healthy, label="Healthy")
sns.scatterplot(x="MDVP:Flo(Hz)", y="MDVP:Fhi(Hz)", data=parkinsons, label="Parkinsons")
plt.legend()
plt.title("Min vs Max Fundamental Frequency")
# plt.savefig("Min vs Max Fundamental Frequency")
# horrible for both
#sns.regplot(x="MDVP:Fhi(Hz)", y="MDVP:Flo(Hz)", data=healthy)
#sns.regplot(x="MDVP:Fhi(Hz)", y="MDVP:Flo(Hz)", data=parkinsons)



# %%
print("spread 1 and 2")
X = df[['spread1' ,'spread2']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))
# %%
print("spread 1 and PPE")
X = df[['spread1' ,'PPE']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))

# %%
print("mdvp fo hz and dfa")
X = df[['MDVP:Fo(Hz)', 'DFA']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))

# %% 
print("nhr & hnr")
X = df[['NHR', 'HNR']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))
# %% 
print("DFA & HNR")
X = df[['DFA', 'HNR']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))
# %%
print("D2 & PPE")
X = df[['PPE', 'PPE']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))
# %%
print("mdvp fhi hz and mdvp fhlo hz")
X = df[['MDVP:Fhi(Hz)', 'MDVP:Flo(Hz)']]
y = df.status
lm = LogisticRegression()
lm.fit(X, y)
y_pred = lm.predict(X)
display('predicted range: [{0:.2f},{1:.2f}]'.format(min(y_pred), max(y_pred)))

p, r, f, s = precision_recall_fscore_support(y, y_pred)
display('precision = {}'.format(p))
display('recall = {}'.format(r))
display('f-score = {}'.format(f))



# %%

print("mdvp fhi hz and mdvp fhlo hz")
X = df[['MDVP:Fhi(Hz)', 'MDVP:Flo(Hz)']]
y = df.status

num = 10
fs = [0, 0]
for i in range(num):
  lm = LogisticRegression()
  lm.fit(X, y)
  y_pred = lm.predict(X)

  p, r, f, s = precision_recall_fscore_support(y, y_pred)
  fs[0] += f[0]/num 
  fs[1] += f[1]/num
print(fs)




# %%
# %%

print("spread 1 and PPE")
X = df[['spread1' ,'PPE']]
y = df.status

num = 10
fs = [0, 0]
for i in range(num):
  lm = LogisticRegression()
  lm.fit(X, y)
  y_pred = lm.predict(X)

  p, r, f, s = precision_recall_fscore_support(y, y_pred)
  fs[0] += f[0]/num 
  fs[1] += f[1]/num
print(fs)
# %%
