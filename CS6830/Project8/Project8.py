# %%
import colorsys
import networkx as nx
from sklearn import tree
from sklearn.tree import DecisionTreeClassifier
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import classification_report, confusion_matrix
import pandas as pd
import numpy as np
from sklearn.neighbors import NearestNeighbors
import random
from sklearn.tree import export_graphviz
from IPython.display import SVG
from graphviz import Source
import matplotlib.pyplot as plt


# %%
df = pd.read_csv('./cardata.csv')
df.head()

# %%
df.loc[(df.buying == 'vhigh'), 'buying'] = '4'
df.loc[(df.buying == 'high'), 'buying'] = '3'
df.loc[(df.buying == 'med'), 'buying'] = '2'
df.loc[(df.buying == 'low'), 'buying'] = '1'
df.loc[(df.maint == 'vhigh'), 'maint'] = '4'
df.loc[(df.maint == 'high'), 'maint'] = '3'
df.loc[(df.maint == 'med'), 'maint'] = '2'
df.loc[(df.maint == 'low'), 'maint'] = '1'
df.loc[(df.trunk_size == 'big'), 'trunk_size'] = '3'
df.loc[(df.trunk_size == 'med'), 'trunk_size'] = '2'
df.loc[(df.trunk_size == 'small'), 'trunk_size'] = '1'
df.loc[(df.safety == 'high'), 'safety'] = '3'
df.loc[(df.safety == 'med'), 'safety'] = '2'
df.loc[(df.safety == 'low'), 'safety'] = '1'
df.loc[(df.deal_index == 'vgood'), 'deal_index'] = '3'  # was 3
df.loc[(df.deal_index == 'good'), 'deal_index'] = '2'  # was 2
df.loc[(df.deal_index == 'acc'), 'deal_index'] = '1'
df.loc[(df.deal_index == 'unacc'), 'deal_index'] = '0'

df['Seats2'] = np.where(df['persons'] == '2', 1, 0)
df['Seats4'] = np.where(df['persons'] == '4', 1, 0)
df['Seats4_plus'] = np.where(df['persons'] == 'more', 1, 0)
df['2doors'] = np.where(df['doors'] == '2', 1, 0)
df['3doors'] = np.where(df['doors'] == '3', 1, 0)
df['4doors'] = np.where(df['doors'] == '4', 1, 0)
df['5_plusdoors'] = np.where(df['doors'] == '5more', 1, 0)
df = df.drop('doors', 1)
df = df.drop('persons', 1)

df['buying'] = df['buying'].astype('int')
df['maint'] = df['maint'].astype('int')
df['trunk_size'] = df['trunk_size'].astype('int')
df['safety'] = df['safety'].astype('int')
# df['deal_index'] = df['deal_index'].astype('int')
df['Seats2'] = df['Seats2'].astype('int')
df['Seats4'] = df['Seats4'].astype('int')
df['Seats4_plus'] = df['Seats4_plus'].astype('int')
df['2doors'] = df['2doors'].astype('int')
df['3doors'] = df['3doors'].astype('int')
df['4doors'] = df['4doors'].astype('int')
df['5_plusdoors'] = df['5_plusdoors'].astype('int')

df.head(23)

# %%
df.columns


# %%
# heart = pd.read_csv('./RRCA_baseflow.csv')
feature_cols = ['buying', 'maint', 'trunk_size', 'safety', 'Seats2',
                'Seats4', 'Seats4_plus', '2doors', '3doors', '4doors', '5_plusdoors']
X = df[feature_cols]
y = df.deal_index
treeclf = DecisionTreeClassifier(max_depth=5, random_state=1)
treeclf.fit(X, y)
# # # create a Graphviz file
# # with open("heart.dot", 'w') as f:
# #     f = export_graphviz(treeclf, out_file=f, feature_names=feature_cols, class_names=['0', '1'], filled = True)

graph = Source(tree.export_graphviz(treeclf, out_file=None,
                                    feature_names=feature_cols,
                                    #                                     class_names=['0', '1'], filled = True))
                                    class_names=['0', '1', '2', '3', '4'], filled=True))
svg = SVG(graph.pipe(format='svg'))
display(svg)
n = df.shape[0]
# i = random.randint(0, n)
# i = 254 # an interesting case
i = 15  # an interesting case
sample = df.iloc[i]
print('Sample patient {} to test on. Tree classified as {}'.format(
    i, treeclf.predict([sample[feature_cols]])))
display(sample)


# # %%
# heart = pd.read_csv('./RRCA_baseflow.csv')
# feature_cols = ['Date', 'Segment_id', 'x', 'y',
#                 'Evapotranspiration', 'Precipitation', 'Irrigation_pumping']
# # Date,Segment_id,x,y,Evapotranspiration,Precipitation,Irrigation_pumping,Observed

# %%
# X = heart[feature_cols]
# y = heart.Observed
X_train, X_test, y_train, y_test = train_test_split(X, y)
X.columns
y.unique()

# %%
scaler = StandardScaler()
scaler.fit(X_train)
X_train = scaler.transform(X_train)
X_test = scaler.transform(X_test)
X_train

# %%
# mlp = MLPClassifier(hidden_layer_sizes=(3), max_iter=5000)
# mlp = MLPClassifier(hidden_layer_sizes=(6, 6), max_iter=5000)
mlp = MLPClassifier(hidden_layer_sizes=(12, 12, 12), max_iter=5000)
mlp.fit(X_train, y_train)
predictions = mlp.predict(X_test)

# %%
print(confusion_matrix(y_test, predictions))
print(classification_report(y_test, predictions))


# %%
print('This dataset has {} input nodes and {} output node(s)'.format(
    len(X.columns), len(y.unique())))
print('There are {} 2D arrays of coefficients, one for each layer'.format(len(mlp.coefs_)))
print('The layers have the following number of coefficients: {}')
for l in range(len(mlp.coefs_)):
    m = len(mlp.coefs_[l])
    n = len(mlp.coefs_[l][0])
    print('  {}: {}x{} ({} nodes feeding into a layer of {} nodes)'.format(l, m, n, m, n))
# Print the actual coefficients
print(mlp.coefs_)
print()
print('There are {} 1D arrays of intercepts, one for each layer'.format(
    len(mlp.intercepts_)))
print('Each layer has {} intercepts, one for each node'.format(
    [len(mlp.intercepts_[l]) for l, _ in enumerate(mlp.intercepts_)]))


# %%
def show_ann(mlp):
    hidden_layers_n = len(mlp.coefs_)-1
    layers_n = hidden_layers_n + 2
    input_neurons_n = len(mlp.coefs_[0])
    hidden_neurons_n = [len(mlp.coefs_[i+1]) for i in range(hidden_layers_n)]
    output_neurons_n = len(mlp.coefs_[-1][0])
    G = nx.DiGraph()
    pos = {}
    # Create the neurons of the input layer
    for i in range(input_neurons_n):
        pos['Layer0_{}'.format(i)] = (i, layers_n-1)
    for j in range(hidden_layers_n):
        # Create the neurons of the j'th hidden layer
        prev_layer = j
        cur_layer = j+1
        if (j == 0):
            prev_size = input_neurons_n
        else:
            prev_size = hidden_neurons_n[j-1]
        for i in range(hidden_neurons_n[j]):
            pos['Layer{}_{}'.format(cur_layer, i)] = (i, layers_n-1-cur_layer)
            for k in range(prev_size):
                w = mlp.coefs_[prev_layer][k][i]
                G.add_edge('Layer{}_{}'.format(prev_layer, k),
                           'Layer{}_{}'.format(cur_layer, i), weight=w)
    # Create the neurons of the output layer
    prev_layer = hidden_layers_n
    cur_layer = hidden_layers_n+1
    for i in range(output_neurons_n):
        pos['Layer{}_{}'.format(cur_layer, i)] = (i, layers_n-1-cur_layer)
        for k in range(hidden_neurons_n[-1]):
            w = mlp.coefs_[prev_layer][k][i]
            G.add_edge('Layer{}_{}'.format(prev_layer, k),
                       'Layer{}_{}'.format(cur_layer, i), weight=w)
    edges = G.edges()
    colors = [colorsys.hsv_to_rgb(0 if G[u][v]['weight'] < 0 else 0.65,
                                  1,  # min(1, abs(G[u][v]['weight'])),
                                  1) for u, v in edges]
    weights = [abs(G[u][v]['weight'])*2 for u, v in edges]
    nx.draw(G, pos, node_color='y', node_size=450,
            width=weights, edge_color=colors)


show_ann(mlp)

# %%
