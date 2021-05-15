# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns
from scipy import stats

# %% [markdown]
# ## Read Iris data

# %%
iris = pd.read_csv('iris.csv')
# iris
iris.species.unique()

# %% [markdown]
# ## Show a scatterplot and regression line
# "The line minimizes the sum of squared differences between observed values (the y values) and predicted values (the ŷ values computed from the regression equation)" (https://stattrek.com/regression/linear-regression.aspx).
# 
# Seaborn can also show the confidence interval of the regression, calculated using either bootstrapping or the binned standard deviation.

# %%
setosa = iris[iris.species == 'Iris-setosa']
# sns.scatterplot('sepal_length', 'sepal_width', data=setosa)
# sns.regplot('sepal_length', 'sepal_width', data=setosa)
sns.regplot('sepal_length', 'sepal_width', data=setosa, ci=None)


# %%
colors = {'Iris-setosa':'blue','Iris-virginica':'red','Iris-versicolor':'black'}

fig, ax = plt.subplots(2, 2, figsize=(10,10))

ax = plt.subplot(2,2,1)
for species in iris.species.unique():
    data = iris[iris.species == species]
    ax.scatter(x=data.sepal_length, y=data.sepal_width, c=colors[species], label=species)
ax.set_xlabel('sepal_length')    
ax.set_ylabel('sepal_width')    
ax.legend()

ax = plt.subplot(2,2,2)
for species in iris.species.unique():
    data = iris[iris.species == species]
    ax.scatter(x=data.petal_length, y=data.petal_width, c=colors[species], label=species)
ax.set_xlabel('petal_length')    
ax.set_ylabel('petal_width')    
ax.legend()

ax = plt.subplot(2,2,3)
for species in iris.species.unique():
    data = iris[iris.species == species]
    ax.scatter(x=data.petal_length, y=data.sepal_length, c=colors[species], label=species)
ax.set_xlabel('petal_length')    
ax.set_ylabel('sepal_length')    
ax.legend()

ax = plt.subplot(2,2,4)
for species in iris.species.unique():
    data = iris[iris.species == species]
    ax.scatter(x=data.petal_length, y=data.sepal_width, c=colors[species], label=species)
ax.set_xlabel('petal_length')    
ax.set_ylabel('sepal_width')    
ax.legend()

# %% [markdown]
# ## Compute Pearson's correlation coefficient
# See [here](https://en.wikipedia.org/wiki/Pearson_correlation_coefficient#/media/File:Correlation_examples2.svg) for some examples. scipy's implementation returns two values: Pearson's correlation coefficient $r$ and the $p$ value, or the statistical significance of the correlation.

# %%
setosa = iris[iris.species == 'Iris-setosa']

display(stats.pearsonr(setosa.petal_length, setosa.petal_width))
display(stats.pearsonr(setosa.petal_length, setosa.sepal_length))
display(stats.pearsonr(setosa.petal_length, setosa.sepal_width))

display(stats.pearsonr(iris.petal_length, iris.petal_width))
display(stats.pearsonr(iris.petal_length, iris.sepal_width))
# display(iris.corr())
# display(iris[iris.species=='Iris-setosa'].corr())


