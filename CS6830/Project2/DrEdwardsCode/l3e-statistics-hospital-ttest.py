# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
import pandas as pd
import seaborn as sns
from scipy import stats

# %% [markdown]
# Data downloaded from [Medicare website](https://data.medicare.gov/data/hospital-compare)

# %%
df = pd.read_csv('hospital.csv')

df.Score = pd.to_numeric(df.Score, errors='coerce')
df = df.dropna(subset=['Score'])
df.head()
# sns.distplot(df.Score)

# sns.distplot(df[df.State == 'UT'].Score, label='UT', hist=False)
# sns.distplot(df[df.State == 'AL'].Score, label='AL', hist=False)
sns.distplot(df[df.State == 'MI'].Score, label='MI', hist=False)
sns.distplot(df[df.State == 'CA'].Score, label='CA', hist=False)

# display(stats.ttest_ind(df[df.State == 'UT'].Score, df[df.State == 'AL'].Score))
display(stats.ttest_ind(df[df.State == 'MI'].Score, df[df.State == 'CA'].Score))


