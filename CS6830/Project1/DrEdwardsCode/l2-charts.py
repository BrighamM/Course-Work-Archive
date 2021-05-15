# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %% [markdown]
# # Charts
# We'll use pandas, matplotlib, and seaborn

# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns


# %%
players = pd.read_csv('../core/People.csv')
players = players[['playerID', 'nameFirst', 'nameLast']]
batting = pd.read_csv('../core/Batting.csv')
batting = batting[['playerID', 'AB', 'H', 'HR', 'yearID']]
playerHits = pd.merge(players, batting, on='playerID')
playerHits.head()


# %%
playerHits = playerHits.dropna()
playerHits.yearID = playerHits.yearID.astype('int')

# %% [markdown]
# ### Display a scatterplot of year vs. hits

# %%
sns.scatterplot(x='yearID', y='H', data=playerHits.sample(frac=0.1), s=8)


# %%
batting = playerHits.groupby('yearID').agg({'H':'mean', 'AB':'mean'}).reset_index()
sns.lineplot('yearID', 'H', data=batting)
# batting.head()


# %%
batting.columns
sns.lineplot('yearID', 'AB', data=batting)


# %%
batting['avg'] = batting.H / batting.AB
# batting.head()
sns.lineplot('yearID', 'avg', data=batting)
plt.ylim((0, .31))

plt.figure()
sns.lineplot('yearID', 'avg', data=batting)
plt.xlim((1920, 1930))


# %%
playerHits.head()
display(playerHits.columns)
playerHits.yearID.astype('int')
playerHits1996 = playerHits[playerHits.yearID == 1996].copy()
# Show distribution of number of hits per player
sns.distplot(playerHits1996.H, kde=False)
# Show distribution of player batting average for all players with at least
# one at bat.
# Recall that batting average is H/AB.
playerHits1996.fillna(0)
playerHits1996 = playerHits1996[playerHits1996.AB > 0]
playerHits1996['battingAvg'] = playerHits1996.H / playerHits1996.AB
plt.figure()
sns.distplot(playerHits1996.battingAvg, kde=False)


# %%
playerHits1996[playerHits1996.battingAvg > 0.9]

# %% [markdown]
# ### Compute the "250 club", or all players who have at least one season with 250 or more hits. Chart their success over the years.
# 
# 

# %%
display(playerHits[playerHits.nameLast == 'Hornsby'])


# %%
club250 = playerHits[playerHits.H >= 250].playerID.unique()
# club250 = playerHits[(playerHits.H >= 250) & (playerHits.nameLast == 'Hornsby')].playerID.unique()
club250
plt.figure(figsize=(14, 6))
for playerID in club250:
    data = playerHits[playerHits.playerID == playerID]
    firstRow = data.iloc[0]
    name = '{}, {}'.format(firstRow.nameLast, firstRow.nameFirst)
#     print(name)
    sns.lineplot('yearID', 'H', data=data, label=name)
    
plt.xlim((1910, 1945))
    
plt.legend()

plt.savefig('club250.pdf')
plt.savefig('club250')


