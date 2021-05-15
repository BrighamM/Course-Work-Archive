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


# %%
# What decade are most Hall of Famers born in? Don't double count
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


# %%
# What colleges get people to the Hall of Fame?

# First, we need hall of fame people attached to their school.
hTable = pd.read_csv("./core/HallOfFame.csv")
hTable = hTable[['playerID']]
hTable.head()

pTable = pd.read_csv("./core/CollegePlaying.csv")
pTable = pTable[['playerID', 'schoolID']]
pTable.head()

sTable = pd.read_csv("./core/Schools.csv")
sTable = sTable[['schoolID', 'name_full']]
sTable.head()

phTable = pd.merge(hTable, pTable, on="playerID")
collegeTable = pd.merge(phTable, sTable, on="schoolID")
collegeTable.head()

# get rid of duplicate people
collegeTable = collegeTable.drop_duplicates()
collegeTable.head()

# Count the college's hall of fame players
collegeCounts = collegeTable.groupby(['name_full']).agg({'schoolID':'count'}).reset_index()
collegeCounts.head(100)
# Weed out the lame colleges
collegeCounts = collegeCounts[collegeCounts.schoolID > 4]
collegeCounts.head()

collegeCounts = collegeCounts.rename(columns={'name_full':'College', 'schoolID':'# of Players'})
#Plot!
sns.barplot(y='College', x='# of Players', data = collegeCounts).set_title("How many players made the Hall of Fame by college attended")

plt.savefig("FourthAnalysis/CollegeHallOfFame.pdf")

# %%
'''
Schools that had 10 or more
players who played in the majors after graduating
since 2010
'''
schoolsTable = pd.read_csv("core/CollegePlaying.csv")
schoolNamesTable = pd.read_csv("core/Schools.csv")
salaryTable = pd.read_csv("core/Salaries.csv")
pTable = pd.read_csv("core/People.csv")
studentsTable = pd.merge(schoolsTable, pTable, on="playerID")
studentsTable = pd.merge(studentsTable, schoolNamesTable, on="schoolID")
studentsTable = pd.merge(studentsTable, salaryTable, on="playerID")
studentsTable.yearID_y.astype('int')
studentsTable = studentsTable[studentsTable.yearID_y >= 2010]
studentsTable = studentsTable.drop_duplicates(subset=['playerID'], keep='first')
schoolCounts = studentsTable.schoolID.value_counts()
studentsTable = studentsTable[studentsTable.schoolID.isin(schoolCounts.index[schoolCounts.gt(10)])]
studentsTable.columns
sns.countplot(y='schoolID', data = studentsTable, order = studentsTable['schoolID'].value_counts().index)
plt.savefig("schools.png")

# %%
