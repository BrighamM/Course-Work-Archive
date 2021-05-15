# %%
import numpy as np
import statsmodels.formula.api as smf
# from sklearn.linear_model import LinearRegression
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# %%
masterDataFrame = pd.read_csv('RRCA_baseflow.csv', index_col=0).reset_index()
masterDataFrame['DateFormat'] = pd.to_datetime(
    (masterDataFrame['Date'] - 719164) * 86400, unit='s')
masterDataFrame['day'] = masterDataFrame['DateFormat'].dt.dayofyear
masterDataFrame['NormalizedDate'] = masterDataFrame['Date']
masterDataFrame['NormalizedDate'] = masterDataFrame['Date'].astype(
    'int') - masterDataFrame['Date'].astype('int').min()
# fig, axs = plt.subplots(1, 3, sharey=True)
# masterDataFrame.plot(kind='scatter', x='TV', y='sales', ax=axs[0], figsize=(16, 8))
# masterDataFrame.plot(kind='scatter', x='radio', y='sales', ax=axs[1])
# masterDataFrame.plot(kind='scatter', x='newspaper', y='sales', ax=axs[2])


# %%
masterDataFrame.head()


# %%
UniqueXYLocations = []
for index, row in masterDataFrame.iterrows():
    uniquePoint = []
    xValue = int(row['x'])
    yValue = int(row['y'])
    uniquePoint.append(xValue)
    uniquePoint.append(yValue)
    if not uniquePoint in UniqueXYLocations:
        UniqueXYLocations.append(uniquePoint)

# %%
print("heck no")
subDataFrame = masterDataFrame[(masterDataFrame.x == UniqueXYLocations[0][0]) & (
    masterDataFrame.y == UniqueXYLocations[0][1])]
display(subDataFrame)
lm = smf.ols(formula='Observed ~ NormalizedDate', data=subDataFrame).fit()
lm.rsquared


# %%
print('There are ' + str(len(UniqueXYLocations)) + ' Unique X-Y locations!')
dataFrameXYCollection = []
for eachLocation in UniqueXYLocations:
    subDataFrame = masterDataFrame[(masterDataFrame.x == eachLocation[0]) & (
        masterDataFrame.y == eachLocation[1])]
    dataFrameXYCollection.append(subDataFrame)
    lm = smf.ols(formula='Observed ~ NormalizedDate', data=subDataFrame).fit()
    subDataFrame.plot(
        kind='line', x='NormalizedDate', y='Observed', style='-o').set_title(str(eachLocation) + " rValue: " + str(lm.rsquared))
    sns.regplot(x='NormalizedDate', y='Observed', data=subDataFrame)


# %%
UniqueSegmentLocations = []
for index, row in masterDataFrame.iterrows():
    if not int(row['Segment_id']) in UniqueSegmentLocations:
        UniqueSegmentLocations.append(int(row['Segment_id']))

# %%
print('There are ' + str(len(UniqueSegmentLocations)) +
      ' Unique Segment locations!')
dataFrameSegmentCollection = []
for eachLocation in UniqueSegmentLocations:
    subSegmentDataFrame = masterDataFrame[(
        masterDataFrame.Segment_id == eachLocation)]
    dataFrameSegmentCollection.append(subSegmentDataFrame)
    lm = smf.ols(formula='Observed ~ NormalizedDate',
                 data=subSegmentDataFrame).fit()
    subSegmentDataFrame.plot(
        kind='line', x='NormalizedDate', y='Observed', style='-o').set_title(str(eachLocation) + " rValue: " + str(lm.rsquared))
    sns.regplot(x='NormalizedDate', y='Observed', data=subSegmentDataFrame)


# %%
# someDataFrame = dataFrameXYCollection[0].copy(deep=True)
# someDataFrame.plot(kind='scatter', x='Date', y='Observed')
# dataFrameXYCollection[0].plot(kind='scatter', x='Date', y='Observed')
# masterDataFrame.plot(kind='scatter', x='x', y='y')

# %%
