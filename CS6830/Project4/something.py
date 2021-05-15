# %%
import pandas as pd
import numpy as np
from sklearn.neighbors import NearestNeighbors
import random

import matplotlib.pyplot as plt
# %%
# Comma-separated values
df = pd.read_csv('cleveland.csv')

# Rename 'num' column to 'disease' and change 1,2,3,4 to 1
df = df.rename({'num':'disease'}, axis=1)
df['disease'] = df.disease.apply(lambda x: min(x, 1))
display(df.head(5))

# Plot histograms
fig, (ax1, ax2) = plt.subplots(2, 1)
# make a little extra space between the subplots
fig.subplots_adjust(hspace=0.5)

ax1.hist(df[df.disease == 0].age);
# ax1.set_xlabel('age');
ax1.set_ylabel('number of patients');
ax1.set_xlim(20, 80);
ax1.set_ylim(0, 50);
ax1.set_title('healthy');

ax2.hist(df[df.disease == 1].age, color='orange');
ax2.set_xlabel('age');
ax2.set_ylabel('number of patients');
ax2.set_xlim(20, 80);
ax2.set_ylim(0, 50);
ax2.set_title('has heart disease');