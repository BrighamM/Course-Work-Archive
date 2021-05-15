################################################
# Module: usenet_kmeans.py
# YOUR A#
# YOUR NAME
################################################

import os
import sys
import sklearn.datasets
import scipy as sp
import pickle
from sklearn.feature_extraction.text import TfidfVectorizer
import nltk.stem
from sklearn.cluster import KMeans

## define the stemmer and vectorizer
english_stemmer = nltk.stem.SnowballStemmer('english')
class StemmedTfidfVectorizer(TfidfVectorizer):

    def build_analyzer(self):
        analyzer = super(TfidfVectorizer, self).build_analyzer()
        return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))

def pickle_save(obj, file_name):
    with open(file_name, 'wb') as fp:
        pickle.dump(obj, fp)

def pickle_load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

def load_usenet_data():
    """ Load USENET data """
    print('Loading USENET data...')
    usenet_data = sklearn.datasets.fetch_20newsgroups()
    assert len(usenet_data.target_names) == 20
    print('USENET data loaded...')
    pickle_usenet_data(usenet_data, 'usenet_data.pck')
    return usenet_data

def tfidf_vocab_normalize_usenet_data(usenet_data):
    """
    Normalize the vocabulary of USENET newsgoup posts with NLTK stemming 
    and stoplisting and tfidf.
    """
    vectorizer = StemmedTfidfVectorizer(min_df=10,
                                    stop_words='english',
                                    decode_error='ignore')
    feat_mat = vectorizer.fit_transform(usenet_data.data)
    ## the next two lines are for debugging purposes only.
    num_posts, num_feats = feat_mat.shape
    print('# of posts: {}, # of features: {}'.format(num_posts, num_feats))
    return vectorizer, feat_mat

### Pickling and unpickling utils.
def pickle_usenet_data(data, path):
    pickle_save(data, path)

def unpickle_usenet_data(path):
    return pickle_load(path)
    
def pickle_usenet_feat_mat(feat_mat, path):
    pickle_save(feat_mat, path)

def unpickle_usenet_feat_mat(path):
    return pickle_load(path)

def pickle_usenet_vectorizer(vectorizer, path):
    pickle_save(vectorizer, path)

def unpickle_usenet_vectorizer(path):
    return pickle_load(path)

def pickle_usenet_kmeans(km, path):
    pickle_save(km, path)

def unpickle_usenet_kmeans(path):
    return pickle_load(path)
    
def fit_and_pickle_tfidf_kmeans(num_clusters):
    # 1. load the data.
    usenet_data = load_usenet_data()
    # 2. normalize the data
    usenet_vectorizer, usenet_feat_mat = tfidf_vocab_normalize_usenet_data(usenet_data)
    num_docs, num_feats = usenet_feat_mat.shape
    print('# of posts: {}, # of feats: {}'.format(num_docs, num_feats))
    # 3. Fit K Means with n clusters
    km = KMeans(n_clusters=num_clusters, n_init=1, verbose=1, random_state=3)
    km.fit(usenet_feat_mat)
    print('km.labels_=%s' % km.labels_)
    # after the clustering is done, each data item
    # has its own cluster label ranging from 0 to num_clusters
    print('km.labels_=%s' % km.labels_)
    print('len(km.labels_)=%d' % len(km.labels_))
    # there are 11314 posts and 11777 feats
    # each label is an integer 0 <= i <= n-1,
    # where n is the number of clusters.
    print('max label = %d' % max(km.labels_))
    print('min label = %d' % min(km.labels_))
    # 4. pickle K Means, vectorizer, and feat mat for future use.
    pickle_usenet_kmeans(km, 'tfidf_kmeans.pck')
    pickle_usenet_vectorizer(usenet_vectorizer, 'usenet_tfidf_vectorizer.pck')
    pickle_usenet_feat_mat(usenet_feat_mat, 'usenet_tfidf_feat_mat.pck')

#### Sample user query
user_query = """
Disk drive problems. Hi, I have a problem with my hard disk.
After 1 year it is working only sporadically now.
I tried to format it, but now it doesn't boot any more.
Any ideas? Thanks.
"""
    
def find_top_n_posts_with_kmeans(vectorizer, kmeans, user_query, usenet_data, usenet_feat_mat, dist_fun, top_n=10):
    ### your code here
    user_query_feat_mat = vectorizer.transform([user_query]).getrow(0).toarray()
    user_query_top_cluster_label = kmeans.predict(user_query_feat_mat)[0]
    posts_in_same_cluster = (kmeans.labels_ == user_query_top_cluster_label).nonzero()[0]

    distPTList = []

    # for postThing in posts_in_same_cluster:

    for i in range(len(posts_in_same_cluster)):
        smallNumber = dist_fun(user_query_feat_mat, usenet_feat_mat[posts_in_same_cluster[i]])
        someArr = []
        someArr.append(smallNumber)
        someArr.append(str(usenet_data.data[posts_in_same_cluster[i]]))
        distPTList.append(someArr)
    
    distPTList.sort()
    return distPTList[:top_n]

def feat_mat_dist(fm1, fm2):
    """ 
    Euclidean distance b/w two feat mats. 
    fm1 is <class 'numpy.ndarray'>;
    fm2 is <class 'scipy.sparse.csr.csr_matrix'>
    """
    return sp.linalg.norm(fm1 - fm2)

### test find_top_n_posts_with_kmeans()
def test_kmeans():
    usenet_vectorizer = unpickle_usenet_vectorizer('usenet_tfidf_vectorizer.pck')
    usenet_feat_mat = unpickle_usenet_vectorizer('usenet_tfidf_feat_mat.pck')
    usenet_tfidf_km = unpickle_usenet_kmeans('tfidf_kmeans.pck')
    usenet_data = unpickle_usenet_data('usenet_data.pck')
    dist_fun = feat_mat_dist
    usenet_posts = find_top_n_posts_with_kmeans(usenet_vectorizer,
                                                usenet_tfidf_km,
                                                user_query,
                                                usenet_data,
                                                usenet_feat_mat,
                                                dist_fun, top_n=5)
    for dist, post_text in usenet_posts:
        print(dist)
        print(post_text)

if __name__ == '__main__':
    test_kmeans()
    pass
