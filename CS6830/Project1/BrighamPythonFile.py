# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns

# %%
# What countries do Hall Of Famers come from? (Besides the U.S.)
hTable = pd.read_csv("core/HallOfFame.csv")
hTable.head()
pTable = pd.read_csv("core/People.csv")
pTable.head()
phTable = pd.merge(hTable, pTable, on="playerID")
phTable.head()
phTable.columns
phTable = phTable[['playerID', 'birthCountry', 'nameFirst', 'nameLast']]

phTable = phTable[(phTable.birthCountry != 'USA')]
phTable.head()
sns.countplot(y='birthCountry',data = phTable, order = phTable['birthCountry'].value_counts().index)
plt.savefig("births.pdf")

# %%
# How do team salaries compare through the years since 1985?
salaryTable = pd.read_csv('core/Salaries.csv')
salaryTable.yearID = salaryTable.yearID.astype('int')
salaryTable = salaryTable.groupby(['yearID','teamID']).agg({'salary':'sum'}).reset_index()
allDaTeams = salaryTable['teamID'].drop_duplicates()
plt.figure(figsize=(14, 6))
someInt = -1
# New York Yankees, Houston Astros, Los Angeles Dodgers, Philedelphia Phillies, New York Mets
# San Diego Padres, Texas Rangers, 
teamIDs = ['NYA','HOU','PHI','NYN','LAN','SDN','TEX']
for team in allDaTeams:
    someInt += 1
    if someInt >= 0 and someInt <= 38:
        if str(team) in teamIDs:
            currTeam = salaryTable[salaryTable.teamID == team]
            firstRow = currTeam.iloc[0] 
            someData = '{}, {}, {}'.format(firstRow.yearID, firstRow.teamID, firstRow.salary)
            sns.lineplot('yearID', 'salary', data=currTeam, label=someData)
            plt.savefig("./SecondAnalysis/Interesting.pdf")
    else:
        continue
