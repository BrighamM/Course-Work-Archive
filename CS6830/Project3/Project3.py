# %%
import pandas as pd
from matplotlib import pyplot as plt
# Make sure you have seaborn version 0.9.
import seaborn as sns
import pandas as pd
import numpy as np
from scipy import stats
import requests
import re
from bs4 import BeautifulSoup
import html5lib  # pip3 install html5lib
import os


# def delete_line(original_file, line_number):
#     """ Delete a line from a file at the given line number """
#     is_skipped = False
#     current_index = 0
#     dummy_file = original_file + '.bak'
#     # Open original file in read only mode and dummy file in write mode
#     with open(original_file, 'r') as read_obj, open(dummy_file, 'w', encoding='utf8') as write_obj:
#         # Line by line copy data from original file to dummy file
#         for line in read_obj:
#             # If current line number matches the given line number then skip copying
#             if current_index != line_number:
#                 write_obj.write(line)
#             else:
#                 is_skipped = True
#             current_index += 1
#     # If any line is skipped then rename dummy file as original file
#     if is_skipped:
#         os.remove(original_file)
#         os.rename(dummy_file, original_file)
#     else:
#         os.remove(dummy_file)


# base_url = 'https://boardgamegeek.com/browse/boardgame/page/'
# sites = []
# for i in range(1, 11):
#     sites.append(requests.get(base_url+str(i)))
# list(sites[0])[0]


# %%
# for j in range(len(sites)):
#     num = j + 1
#     site = BeautifulSoup(sites[j].text, 'html.parser')
#     f = open(f'bgg{num}orig.txt', 'w+', encoding='utf8')
#     f.write(site.get_text())
#     f.close()
# for k in range(180):
#     for j in range(1,len(sites)+1):
#         delete_line(f'bgg{j}orig.txt', 0)

masterList = []
# for l in range(1, len(sites)+1):
for l in range(1,11):
    f = open(f'bgg{l}.txt', encoding='utf8')
    bgg = f.readlines()
    f.close()
    bgg = [x.strip() for x in bgg]
    bgg = [i for i in bgg if i]
    bgg = bgg[:-16]
    masterList += bgg

masterList = [i for i in masterList if i != '[Shop]']

# %%
masterTupleList = []
for x in range(1000):
    currTuple = (int(masterList[(7 * x) + 0]), masterList[(7 * x) + 1], masterList[(7 * x) + 2].replace('(', '').replace(')', ''), masterList[(
        7 * x) + 3], float(masterList[(7 * x) + 4]), float(masterList[(7 * x) + 5]), int(masterList[(7 * x) + 6]))
    masterTupleList.append(currTuple)
# display(masterList[2])

# %%
MasterDataFrame = pd.DataFrame(masterTupleList, columns=[
                               'BGGRank', 'Title', 'YearReleased', 'Description', 'GeekRating', 'AvgRating', 'NumVoters'])
MasterDataFrame

# %%

# sns.scatterplot(x="NumVoters", y="AvgRating", data=MasterDataFrame)
# sns.scatterplot(x="NumVoters", y="GeekRating", data=MasterDataFrame)
sns.regplot('NumVoters', 'AvgRating', MasterDataFrame, label="Average Rating")
sns.regplot('NumVoters', 'GeekRating', MasterDataFrame, label="Geek Rating")
plt.legend()
plt.ylabel("Rating")
plt.ylim(0, 10)
plt.title("Rating Based on Number of Voters")
plt.xlabel("Number of Voters")
plt.savefig("Number of voters linear regression.png")
# %% looking at bgg rank 
sns.regplot('BGGRank', 'AvgRating', MasterDataFrame, label="Average Rating")
sns.regplot('BGGRank', 'GeekRating', MasterDataFrame, label="Geek Rating")
plt.legend()
plt.ylabel("Rating")
plt.xlabel("Board Game Geek Ranking")
plt.ylim(0, 10)
plt.title("Board Game Geek Rank based on Rating")
plt.savefig("BGGRank linear regression.png")
# %% correlation between avg rating and num voters
print("correlation between average rating and number of voters (r/p)")
display(stats.pearsonr(MasterDataFrame.AvgRating, MasterDataFrame.NumVoters))
# %% correlation between geek rating and num voters
print("correlation between geek rating and number of voters (r/p)")
display(stats.pearsonr(MasterDataFrame.GeekRating, MasterDataFrame.NumVoters))
# %% correlation between avg rating and geek rating
print("correlation between average rating and geek rating (r/p)")
display(stats.pearsonr(MasterDataFrame.AvgRating, MasterDataFrame.GeekRating))
# %% correlation between geek rating and bgg rank
print("correlation between geek rating and bgg rank (r/p)")
display(stats.pearsonr(MasterDataFrame.GeekRating, MasterDataFrame.BGGRank))
# %% correlation between avg rating and bgg rank
print("correlation between average rating and bgg rank (r/p)")
display(stats.pearsonr(MasterDataFrame.AvgRating, MasterDataFrame.BGGRank))
# %% std dev and mean of avg rating
print("The mean dev of AvgRating is " + str(MasterDataFrame.AvgRating.mean()) + " and the std dev is " + str(MasterDataFrame.AvgRating.std()))
print("The mean dev of GeekRating is " + str(MasterDataFrame.GeekRating.mean()) + " and the std dev is " + str(MasterDataFrame.GeekRating.std()))

# %%
'''
1. If the geekrating is generally lower than the average rating
2. Is there a correlation between the numvoters and the average rating?

Additional 

3. Which rating system is more important for BGGRank? -> show correlation 




# %% correlation between avg rating and num voters...
correlation between average rating and number of voters (r/p)
(0.031956613262828275, 0.3127105697739689)
[8]



# %% correlation between geek rating and num voters...
correlation between geek rating and number of voters (r/p)
(0.5404790809856677, 6.295436784630522e-77)
[9]



# %% correlation between avg rating and geek rating...
correlation between average rating and geek rating (r/p)
(0.6110832910897314, 2.021915786534713e-103)
[10]



# %% correlation between geek rating and bgg rank...
correlation between geek rating and bgg rank (r/p)
(-0.9397548184762416, 0.0)
[11]



# %% correlation between avg rating and bgg rank...
correlation between average rating and bgg rank (r/p)
(-0.54195936437963, 2.0265296124833608e-77)
[12]



# %% std dev and mean of avg rating...
The mean dev of AvgRating is 7.48405 and the std dev is 0.3986909228361638
The mean dev of GeekRating is 6.969975000000001 and the std dev is 0.371920425868462
[13]



1. If the geekrating is generally lower than the average rating...
'\n1. If the geekrating is generally lower than the average rating\n2. Is there a correlation between the numvoters and the average rating?\n\nAdditional \n\n3. Which rating system is more important for BGGRank? -> show correlation \n\n\n'

'''
