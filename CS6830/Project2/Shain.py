# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns
import pandas as pd
import numpy as np
from scipy import stats

# %%
crimeTable = pd.read_csv("Datasets/crime-housing-austin-2015.csv")
crimeTable.columns
zipTable = pd.read_csv("Datasets/AustinZipCodes.csv")
zipTable.columns

# %%
badCrimes = crimeTable[["Key", "Highest_NIBRS_UCR_Offense_Description"]]
badCrimes.columns
# badCrimes = badCrimes.drop_duplicates()
badCrimeCounts = badCrimes.groupby(
    "Highest_NIBRS_UCR_Offense_Description").agg({'count'}).reset_index()

print(badCrimeCounts)

# %%
crimeZips = crimeTable[["Key", "Zip_Code_Crime"]]
crimeZipsCounts = crimeZips.groupby(
    "Zip_Code_Crime").agg({'count'}).reset_index()
print(crimeZipsCounts)

# %%
# more options can be specified also
with pd.option_context('display.max_rows', None, 'display.max_columns', None):
    print(crimeTable.head(1))

# %%
reducedCrimeTable = crimeTable[["Key", "Zip_Code_Crime", "Highest_NIBRS_UCR_Offense_Description",
                                "Report_Date", "Populationbelowpovertylevel", "Medianhouseholdincome", "Medianhomevalue"]]
reducedCrimeTable.head()

# %%
reducedCrimeTable = reducedCrimeTable.dropna()
reducedCrimeTable.Zip_Code_Crime = reducedCrimeTable.Zip_Code_Crime.astype(
    'int')

# %%
reducedCrimeTable.head(56)
# %%

# %%
unique_zipcodes = reducedCrimeTable["Zip_Code_Crime"].unique()
crimes = reducedCrimeTable[["Zip_Code_Crime", "Highest_NIBRS_UCR_Offense_Description"]]
crimes["CrimeCount"] = 0
crimes_by_zip = crimes.groupby("Zip_Code_Crime").agg({'CrimeCount': 'count'}).reset_index()
population_df = pd.DataFrame(columns=['Zip_Code_Crime', 'Populationbelowpovertylevel'])
for i in unique_zipcodes:
    t = reducedCrimeTable[reducedCrimeTable.Zip_Code_Crime == i]
    population_df.loc[i] = [i] + [int(t["Populationbelowpovertylevel"].iloc[0].replace("%",""))] 

new_table = pd.merge(population_df,crimes_by_zip, on = "Zip_Code_Crime")
new_table
# %%
# %%

# %%

