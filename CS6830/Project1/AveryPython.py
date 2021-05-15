# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns

# %%
# What decade are most Hall of Famers born in? Don't count players more than once
hTable = pd.read_csv("./core/HallOfFame.csv")
hTable.head()
pTable = pd.read_csv("./core/People.csv")
pTable.head()
phTable = pd.merge(hTable, pTable, on="playerID")
phTable.head()
phTable.columns
phTable = phTable[['playerID','birthYear', 'nameFirst', 'nameLast']]
phTable = phTable.groupby('playerID').agg({'birthYear':'first'}).reset_index()
phTable.head()

# make decades from 1820-1990
bins = [1820+i*10 for i in range(18)]
sns.distplot(phTable.birthYear, bins=bins, kde=False, axlabel="Birth year", color="r").set_title("# of Hall of Famers born in each decade")
# make ticks every other decade
ticks = [1820+i*20 for i in range(9)]
plt.xticks(ticks)

# plt.xlim(1800, 2000)
plt.savefig("ThirdAnalysis/halloffame.pdf")
