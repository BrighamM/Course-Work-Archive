# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %% [markdown]
# # Explore a baseball dataset using Pandas
# This is the first day of class. This is also good, clean fun.
# 
# Download the dataset [here](http://www.seanlahman.com/baseball-archive/statistics).
# 
# `df` means "data frame". It's basically a table.

# %%
import pandas as pd

# %% [markdown]
# ### Open players table

# %%
df = pd.read_csv('../core/People.csv')
df.head()


# %%
# display(df.columns)
# display(df.head())
columns = ['playerID', 'nameFirst', 'nameLast', 'weight', 'birthYear', 'birthCountry', 'finalGame']
players = df[columns]
players.head()


# %%
# players[(players.nameFirst == 'John') & (players.birthYear > 1972) & (players.birthYear < 1976)]

# countries = players[(players.birthCountry != 'USA') & (players.birthYear == players.birthYear)].sort_values('birthYear')
# countries.head(20)
# # countries.tail(20)


# players[(players.birthCountry != 'USA') & (players.nameFirst == 'John')]
players[(players.birthCountry != 'USA') & (players.nameFirst == 'John') & (players.birthYear > 1950)]

# %% [markdown]
# ### Load batting data
# We can see the explanation for the "Batting.csv" dataset in readme2014.txt. Here is the table:
# ```
# playerID       Player ID code
# yearID         Year
# stint          player's stint (order of appearances within a season)
# teamID         Team
# lgID           League
# G              Games
# AB             At Bats
# R              Runs
# H              Hits
# 2B             Doubles
# 3B             Triples
# HR             Homeruns
# RBI            Runs Batted In
# SB             Stolen Bases
# CS             Caught Stealing
# BB             Base on Balls
# SO             Strikeouts
# IBB            Intentional walks
# HBP            Hit by pitch
# SH             Sacrifice hits
# SF             Sacrifice flies
# GIDP           Grounded into double plays
# 
# ```

# %%
batting = pd.read_csv('../core/Batting.csv')
batting = batting[['playerID', 'H', 'yearID']]
batting.head()

# %% [markdown]
# ### Look at how players batted in 2014

# %%
batting[batting.yearID == 2014].sort_values('H')


# %%
batting[batting.playerID == 'abreubo01']

# %% [markdown]
# ### Merge (join) the players and batting tables (data frames)

# %%
playerHits = pd.merge(players, batting, on='playerID')
playerHits[playerHits.playerID == 'altuvjo01']

# %% [markdown]
# ### Find the best hitters

# %%
# playerHits[playerHits.H > 250]
playerHits.sort_values(by='H', ascending=False).head(20)


