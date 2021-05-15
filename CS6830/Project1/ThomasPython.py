# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns


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
