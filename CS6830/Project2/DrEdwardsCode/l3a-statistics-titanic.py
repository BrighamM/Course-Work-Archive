# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

# %% [markdown]
# ## Load Titanic data
# 
# The Titanic dataset was obtained from https://github.com/awesomedata/awesome-public-datasets/blob/master/Datasets/titanic.csv.zip

# %%
titanic = pd.read_csv('titanic.csv')
titanic.head()

# %% [markdown]
# ## Plot histogram of fares and ages

# %%
# plt.figure()
# ax = titanic.Fare.plot.hist()
# ax.set_title('Fire histogram')
# ax.set_xlabel('Fare')

plt.figure()
ax = titanic.Age.plot.hist()

# %% [markdown]
# ## Look at summary statistics

# %%
display(titanic.Age)
print(titanic.Age.mean())
print(titanic.Age.median())
print(titanic.Age.mode())
print(titanic.Age.std())

# %% [markdown]
# ## Show a bar chart of the classes of passengers

# %%
sns.countplot(x='Pclass', data=titanic)


# %%
sns.catplot(x='Pclass', hue='Sex', data=titanic, kind='count')


# %%
sns.catplot(x='Pclass', hue='Sex', col='Survived', data=titanic, kind='count')


# %%
titanic.columns


# %%
titanic.head()


# %%
groupedByClass = titanic.groupby('Pclass')
# groupedByClass.size()
groupedByClass.agg({'Age':['mean', 'std'], 'Fare':'mean', 'Survived':['size','sum']})


