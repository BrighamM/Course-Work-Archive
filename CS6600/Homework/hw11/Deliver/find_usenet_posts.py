#!/usr/bin/python

#######################################
# module: find_usenet_posts.py
# description: indexing and searching usenet posts.
# bugs to vladimir kulyukin in canvas
#######################################

import os
import sys
import sklearn.datasets
import scipy as sp
import pickle
from sklearn.feature_extraction.text import CountVectorizer
import nltk.stem

## define the stemmer
english_stemmer = nltk.stem.SnowballStemmer('english')
## define the vectorizer
class StemmedCountVectorizer(CountVectorizer):
    def build_analyzer(self):
        analyzer = super(StemmedCountVectorizer, self).build_analyzer()
        return lambda doc: (english_stemmer.stem(w) for w in analyzer(doc))

## define two distances
def euclid_dist(v1, v2):
    diff = v1 - v2
    return sp.linalg.norm(diff.toarray())

def norm_euclid_dist(v1, v2):
    """ Normalized Euclid distance b/w vectors v1 and v2 """
    v1_normalized = v1/sp.linalg.norm(v1.toarray())
    v2_normalized = v2/sp.linalg.norm(v2.toarray())
    diff = v1_normalized - v2_normalized
    return sp.linalg.norm(diff.toarray())

def pickle_save(obj, file_name):
    with open(file_name, 'wb') as fp:
        pickle.dump(obj, fp)

def pickle_load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

## load the texts of usenet newsgroups
def load_usenet_data():
    """ Load USENET data """
    print('Loading USENET data...')
    usenet_data = sklearn.datasets.fetch_20newsgroups()
    assert len(usenet_data.target_names) == 20
    print('USENET data loaded...')
    return usenet_data

def vocab_normalize_usenet_data(usenet_data):
    """
    Normalize the vocabulary of USENET newsgoup posts with NLTK stemming 
    and stoplisting.
    """
    vectorizer = StemmedCountVectorizer(min_df=1, stop_words='english')
    feat_mat = vectorizer.fit_transform(usenet_data.data)
    ## the next two lines are for debugging purposes only.
    num_samples, num_features = feat_mat.shape
    print('number of posts: {}, number of features: {}'.format(num_samples, num_features))
    return vectorizer, feat_mat

def pickle_usenet_feat_mat(feat_mat, path):
    pickle_save(feat_mat, path)

def unpickle_usenet_feat_mat(path):
    return pickle_load(path)

def pickle_usenet_vectorizer(vectorizer, path):
    pickle_save(vectorizer, path)

def unpickle_usenet_vectorizer(path):
    return pickle_load(path)

## find the closest USENET posts.
def find_top_n_posts(vectorizer, user_query, doc_feat_mat, dist_fun, top_n=10):
# def find_top_n_posts():

    # vectorizer = unpickle_usenet_vectorizer('usenet_vectorizer.pck')
    # user_query = 'is fuel injector cleaning necessary?'
    # # feat_mat = unpickle_usenet_feat_mat('usenet_feat_mat.pck')
    # doc_feat_mat = unpickle_usenet_feat_mat('usenet_feat_mat.pck')
    # dist_fun = norm_euclid_dist
    # top_n = 5


    # 1. compute feature vector of user_query
    user_query_vec = vectorizer.transform([user_query])
    print('user query: {}'.format(user_query))
    print('user query feat vector:\n {}'.format(user_query_vec))
    print('Searching USENET posts..')
    
    doc_match_scores = {}
    best_dist = sys.maxsize
    num_docs, _ = doc_feat_mat.shape
    for i in range(0, num_docs):
        # print(str(doc_feat_mat[i]))
        
        # 2. get the i-th feature mat (i-th row in doc_feat_math).
        ithFeatureMat = doc_feat_mat.getrow(i)
        # input(str(ithFeatureMat))
        
        
        # 3. compute the distance b/w user_query_vector and document vector
        #    with dist_fun
        # your code here
        distanceThing = dist_fun(user_query_vec,ithFeatureMat)
        # input("here" + str(distanceThing))

        # 4. Store the similarity coefficient in doc_match_scores dictinary
        #    that maps post vector vector numbers (i.e., i's) to the
        #    similarity scores.
        # your code here
        doc_match_scores[i] = distanceThing

    # after the for-loop is done    
    # 5. convert the doc_math_scores dictionary into a list of key-val pairs,
    # your code here
    someList = []
    for key, value in doc_match_scores.items():
        temp = [key, value]
        someList.append(temp)
    

    # 6. sort it from smallest to largest by the second element in each pair.    
    # your codee here
    someList.sort(key = lambda x: x[1])
        
    print('Searching over...')
    
    # 7. return the first top_n elements from the sorted list.
    # your code here
    return someList[0:top_n]

if __name__ == "__main__":
    find_top_n_posts()