# %%
import math
from sklearn.metrics import precision_recall_fscore_support
from sklearn.model_selection import train_test_split
import pandas as pd
import numpy as np
from sklearn.neighbors import NearestNeighbors
import random
import itertools
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns
import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
# sklearn.model_selection.train_test_split

# %%
# Comma-separated values
df = pd.read_csv('output.csv')
df.columns = ['Precision', 'Recall', 'F1_Score', 'k-neighbors']

# Rename 'num' column to 'disease' and change 1,2,3,4 to 1
df['p'] = df['p'].astype('float64')
df['r'] = df['r'].astype('float64')
df['f'] = df['f'].astype('float64')
df['k'] = df['k'].astype('float64')
df.head()

# %%
sns.set(rc={'figure.figsize': (20, 16)})
sns.set(font_scale=3)
sns.regplot(data=df, x='k-neighbors',
            y='F1_Score').set_title("F1_Score per k-neighbors")
plt.savefig('goodfig.png')
# %%
sns.set(rc={'figure.figsize': (20, 16)})
sns.set(font_scale=3)
sns.regplot(data=df, x='Precision',
            y='Recall').set_title("Other")
plt.savefig('goodfig.png')
