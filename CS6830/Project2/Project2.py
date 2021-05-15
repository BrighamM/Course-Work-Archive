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
reducedCrimeTable = crimeTable[["Key", "Zip_Code_Crime", "Highest_NIBRS_UCR_Offense_Description",
                                "Report_Date", "Populationbelowpovertylevel", "Medianhouseholdincome", "Medianhomevalue"]]
reducedCrimeTable['Medianhomevalue'] = reducedCrimeTable['Medianhomevalue'].str.replace('$', '').astype('float')
reducedCrimeTable['Medianhouseholdincome'] = reducedCrimeTable['Medianhouseholdincome'].str.replace('$', '').astype('float')
reducedCrimeTable['Populationbelowpovertylevel'] = reducedCrimeTable['Populationbelowpovertylevel'].str.replace('%', '').astype('float')
reducedCrimeTable['Zip_Code_Crime'] = reducedCrimeTable['Zip_Code_Crime'].astype('float')
reducedCrimeTable.head()

# %%
crimeBuckets = reducedCrimeTable[["Key", "Highest_NIBRS_UCR_Offense_Description"]]
badCrimeCounts = crimeBuckets.groupby("Highest_NIBRS_UCR_Offense_Description").agg({'count'}).reset_index()
badCrimeCounts.columns = ['Highest_NIBRS_UCR_Offense_Description','Count']
print(badCrimeCounts)

# %%
crimeZips = reducedCrimeTable[["Key", "Zip_Code_Crime"]]
crimeZipsCounts = crimeZips.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
crimeZipsCounts.columns = ['Zip_Code_Crime','TotalCrimes']
print(crimeZipsCounts)

# %%
aggAssaultsByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Agg Assault')]
aggAssaultsByZip = aggAssaultsByZip[["Key","Zip_Code_Crime"]]
aggAssaultsByZip = aggAssaultsByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
aggAssaultsByZip.columns = ["Zip_Code_Crime", "AggAssaults"]

autoTheftsByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Auto Theft')]
autoTheftsByZip = autoTheftsByZip[["Key","Zip_Code_Crime"]]
autoTheftsByZip = autoTheftsByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
autoTheftsByZip.columns = ["Zip_Code_Crime", "AutoThefts"]

burglariesByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Burglary')]
burglariesByZip = burglariesByZip[["Key","Zip_Code_Crime"]]
burglariesByZip = burglariesByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
burglariesByZip.columns = ["Zip_Code_Crime", "Burglaries"]

murdersByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Murder')]
murdersByZip = murdersByZip[["Key","Zip_Code_Crime"]]
murdersByZip = murdersByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
murdersByZip.columns = ["Zip_Code_Crime", "Murders"]

rapesByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Rape')]
rapesByZip = rapesByZip[["Key","Zip_Code_Crime"]]
rapesByZip = rapesByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
rapesByZip.columns = ["Zip_Code_Crime", "Rapes"]

robberiesByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Robbery')]
robberiesByZip = robberiesByZip[["Key","Zip_Code_Crime"]]
robberiesByZip = robberiesByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
robberiesByZip.columns = ["Zip_Code_Crime", "Robberies"]

theftsByZip = reducedCrimeTable[(reducedCrimeTable.Highest_NIBRS_UCR_Offense_Description == 'Theft')]
theftsByZip = theftsByZip[["Key","Zip_Code_Crime"]]
theftsByZip = theftsByZip.groupby("Zip_Code_Crime").agg({'count'}).reset_index()
theftsByZip.columns = ["Zip_Code_Crime", "Thefts"]

megaTable = pd.merge(crimeZipsCounts, aggAssaultsByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, autoTheftsByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, burglariesByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, murdersByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, rapesByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, robberiesByZip, on='Zip_Code_Crime', how='outer')
megaTable = pd.merge(megaTable, theftsByZip, on='Zip_Code_Crime', how='outer')
megaTable = megaTable.fillna(0)

cashTable = reducedCrimeTable[["Zip_Code_Crime","Populationbelowpovertylevel", "Medianhouseholdincome", "Medianhomevalue"]].drop_duplicates().dropna()
megaTable = pd.merge(megaTable, cashTable, on='Zip_Code_Crime', how='outer')
megaTable = megaTable.dropna()
megaTable.Medianhomevalue = megaTable.Medianhomevalue.astype('int')
megaTable.Medianhouseholdincome = megaTable.Medianhouseholdincome.astype('int')
megaTable.Zip_Code_Crime = megaTable.Zip_Code_Crime.astype('int')
megaTable.Burglaries = megaTable.Burglaries.astype('int')
megaTable.Murders = megaTable.Murders.astype('int')
megaTable.Rapes = megaTable.Rapes.astype('int')
megaTable.Robberies = megaTable.Robberies.astype('int')
megaTable.Thefts = megaTable.Thefts.astype('int')
megaTable.AggAssaults = megaTable.AggAssaults.astype('int')
megaTable.AutoThefts = megaTable.AutoThefts.astype('int')
megaTable.head(66)

# %%
def appendStandardizedColumnToDataframe(dataframe, nameOfColToStandardize):
    mean = dataframe[str(nameOfColToStandardize)].mean()
    std = dataframe[str(nameOfColToStandardize)].std()
    standardizedColumn = []
    for index, value in dataframe[str(nameOfColToStandardize)].items():
        standardizedValue = (value-mean)/(std)
        standardizedColumn.append(standardizedValue)
    dataframe['standardized_'+str(nameOfColToStandardize)] = standardizedColumn

# %%
appendStandardizedColumnToDataframe(megaTable, 'Medianhomevalue')
appendStandardizedColumnToDataframe(megaTable, 'Medianhouseholdincome')
appendStandardizedColumnToDataframe(megaTable, 'Populationbelowpovertylevel')
appendStandardizedColumnToDataframe(megaTable, 'TotalCrimes')
appendStandardizedColumnToDataframe(megaTable, 'Thefts')
appendStandardizedColumnToDataframe(megaTable, 'Burglaries')
appendStandardizedColumnToDataframe(megaTable, 'Robberies')
megaTable.head()




# %%
def produceDataAndPlots(dataFrame, x_axisData, y_axisData):
    sns.set(rc={'figure.figsize':(20,16)})
    sns.set(font_scale=3)
    sns.scatterplot(x=x_axisData, y=y_axisData, data=dataFrame).set_title(str(x_axisData) + " x " + str(y_axisData))
    plt.savefig("./SavedFigs/" + "ScatterPlot_" + str(x_axisData) + "_" + str(y_axisData) + ".png")
    plt.savefig("./SavedFigs/" + "ScatterPlot_" + str(x_axisData) + "_" + str(y_axisData) + ".pdf")
    sns.regplot(x=x_axisData, y=y_axisData, data=dataFrame).set_title(str(x_axisData) + " x " + str(y_axisData))
    plt.savefig("./SavedFigs/" + "RegressionPlot_" + str(x_axisData) + "_" + str(y_axisData) + ".png")
    plt.savefig("./SavedFigs/" + "RegressionPlot_" + str(x_axisData) + "_" + str(y_axisData) + ".pdf")
    print("Pearsons Correlation Coefficients for " + str(x_axisData) + " and " + str(y_axisData) + ": ")
    print(stats.pearsonr(dataFrame[str(x_axisData)], dataFrame[str(y_axisData)]))
    print('')
    print(str(x_axisData) + " mean: " + str(dataFrame[str(x_axisData)].mean()))
    print(str(x_axisData) + " std: " + str(dataFrame[str(x_axisData)].std()))
    print(str(y_axisData) + " mean: " + str(dataFrame[str(y_axisData)].mean()))
    print(str(y_axisData) + " std: " + str(dataFrame[str(y_axisData)].std()))
    print('')
    print("Ttest results for " + str(x_axisData) + " and " + str(y_axisData) + ": ")
    print(stats.ttest_ind(dataFrame[str(x_axisData)], dataFrame[str(y_axisData)]))
    print('')




# %%
'''
You must include:
Pearson correlations (be sure to report the p-value),
scatterplots, 
means, 
standard deviations, 
scatterplots of standardized data (standardized to mean and standard deviation, not normalized to min/max), 
and a t-test (or Mann-Whitney-U test).
'''

'''
Pearson correlation coefficient and p-value for testing non-correlation.
The Pearson correlation coefficient [1] measures the linear relationship between two datasets. 
The calculation of the p-value relies on the assumption that each dataset is normally distributed. 
(See Kowalski [3] for a discussion of the effects of non-normality of the input on the distribution of the correlation coefficient.) 
Like other correlation coefficients, this one varies between -1 and +1 with 0 implying no correlation. 
Correlations of -1 or +1 imply an exact linear relationship. Positive correlations imply that as x increases, so does y. 
Negative correlations imply that as x increases, y decreases.
The p-value roughly indicates the probability of an uncorrelated system producing datasets that have a Pearson correlation at least as extreme as the one computed from these datasets.
'''

'''
 The test measures whether the average (expected) value differs significantly across samples. 
 If we observe a large p-value, for example larger than 0.05 or 0.1, then we cannot reject the null hypothesis of identical average scores. 
 If the p-value is smaller than the threshold, e.g. 1%, 5% or 10%, then we reject the null hypothesis of equal averages.
'''
produceDataAndPlots(megaTable, 'Medianhomevalue', 'Medianhouseholdincome')

# %%
produceDataAndPlots(megaTable, 'Thefts', 'Medianhouseholdincome')

# %%
produceDataAndPlots(megaTable, 'Medianhomevalue', 'Thefts')

# %%
produceDataAndPlots(megaTable, 'Thefts', 'Populationbelowpovertylevel')

# %%
produceDataAndPlots(megaTable, 'TotalCrimes', 'Populationbelowpovertylevel')

# %%
produceDataAndPlots(megaTable, 'Rapes', 'Medianhouseholdincome')

# %%
produceDataAndPlots(megaTable, 'Burglaries', 'Medianhouseholdincome')

# %%
produceDataAndPlots(megaTable, 'Burglaries', 'Medianhomevalue')

# %%
produceDataAndPlots(megaTable, 'Burglaries', 'Robberies')
megaTable.head(66)

# %%
produceDataAndPlots(megaTable, 'standardized_Burglaries', 'standardized_Robberies')
# %%
produceDataAndPlots(megaTable, 'standardized_Medianhomevalue', 'standardized_TotalCrimes')

# %%
