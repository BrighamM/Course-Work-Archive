# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %% [markdown]
# # Are players named Juan better than players named John?
# And if so, is it because of their name?

# %%
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import scipy.stats as stats
import seaborn as sns


# %%
people = pd.read_csv('People.csv')
people = people[['playerID', 'nameFirst', 'nameLast']]
batting = pd.read_csv('Batting.csv')
batting = batting[['playerID', 'AB', 'H', 'HR', 'yearID']]
playerHits = people.join(batting.set_index('playerID'), on='playerID')

johnjuan = playerHits[(playerHits.nameFirst=='Juan') | (playerHits.nameFirst=='John')]
johnjuan = johnjuan.dropna(subset=['H'])
juan = johnjuan[johnjuan.nameFirst=='Juan']
john = johnjuan[johnjuan.nameFirst=='John']

plt.figure()
plt.bar([1,2],[juan.H.mean(), john.H.mean()], tick_label=['Juan', 'John'])
plt.title('Average number of hits per year')

display('N = {} (Juan) {} (John)'.format(len(juan), len(john)))

# %% [markdown]
# So, why are players named Juan better? It isn't because of their name (there's correlation, but it doesn't mean causation). It could be because players named Juan come from other countries, and Major League Baseball isn't going to go to the trouble of importing a player unless he is really good.
# %% [markdown]
# # Are you a better hitter because you get more at-bats?

# %%
batting['avg'] = batting.H/batting.AB
sns.regplot(batting.AB, batting.avg, ci=None, marker='o', color='red',
            scatter_kws={'s':1}, line_kws={'color':'blue'})

# %% [markdown]
# No, actually it's probably the opposite: you get more at-bats because you are a better hitter.
# %% [markdown]
# # T distribution
# 
# The t test computes t, which measures the spread between means. What are the chances that we re-sampled from a population and got the same value of t? This is what the p value is important for.
# 
# http://blog.minitab.com/blog/statistics-and-quality-data-analysis/what-are-t-values-and-p-values-in-statistics

# %%
# t distribution
from scipy.stats import t
import matplotlib.pyplot as plt
fig, ax = plt.subplots(1, 1)

df = 2.74335149908
mean, var, skew, kurt = t.stats(df, moments='mvsk')
x = np.linspace(t.ppf(0.01, df), t.ppf(0.99, df), 100)
ax.plot(x, t.pdf(x, df), 'k-', lw=2, alpha=0.6, label='t pdf')
ax.set_title('t pdf')


