'''
@Author: Ru_j
@Date: 2020-03-12 21:22:22
@LastEditors: Ru_j
@LastEditTime: 2020-03-12 21:59:29
@Description:
'''

from sklearn.datasets import fetch_20newsgroups
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB

import os
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler
from sklearn.neighbors import KNeighborsClassifier

from sklearn.datasets import load_iris
from sklearn.model_selection import GridSearchCV


def count_news():
    # 获取数据
    news = fetch_20newsgroups()
    x = news.data
    y = news.target
    # 分割
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.3)
    # 特征化
    cnt = CountVectorizer()
    train_x = cnt.fit_transform(train_x)
    test_x = cnt.transform(test_x)
    # 朴素贝叶斯算法学习
    mnb = MultinomialNB(alpha=1.0)
    mnb.fit(train_x, train_y)
    # 评估准确度、预测数据
    score = mnb.score(test_x, test_y)
    predict_y = mnb.predict(test_x)
    print("score: {}".format(score))
    print("predict: {}".format(predict_y[:100]))
    print("test: {}".format(test_y[:100]))
    return None


def min_max_knn_fb():
    # 获取数据并筛选
    path = os.path.dirname(__file__)
    data = pd.read_csv(path + '/train.csv')
    data = data.query('x > 1.0 & x < 1.25 & y > 2.5 & y < 2.75')
    x = data[['x', 'y', 'accuracy', 'time']]
    y = data[['place_id']]
    # 数据归一化
    mm = MinMaxScaler()
    x = mm.fit_transform(x)
    # 分割数据
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.25)
    # knn算法训练
    knn = KNeighborsClassifier(n_neighbors=9)
    knn.fit(train_x, train_y)
    # 评估准确度、预测数据
    score = knn.score(test_x, test_y)
    predict_y = knn.predict(test_x[:100])
    print("score: {}".format(score))
    print("predict:\n{}".format(predict_y[:100]))
    print("test:\n{}".format(test_y[:100]))
    return None


def min_max_knn_iris():
    iris = load_iris()
    x = iris.data
    y = iris.target
    mm = MinMaxScaler(feature_range=(-1, 1))
    x = mm.fit_transform(x)
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.25)
    knn = KNeighborsClassifier()
    # 使用网格搜索对knn算法调优
    params = {'n_neighbors': [3, 5, 7, 9, 11]}
    gscv = GridSearchCV(knn, param_grid=params, cv=10)
    # 算法训练
    gscv.fit(train_x, train_y)
    score = gscv.score(test_x, test_y)
    bst_scr = gscv.best_score_
    bst_estm = gscv.best_estimator_
    cv_rst = gscv.cv_results_
    # 打印调优结果
    print('score: {}\nbest_score: {}\nbest_estimator: {}\ncv_result: {}'
          .format(score, bst_scr, bst_estm, cv_rst))


def std_knn_iris():
    iris = load_iris()
    x = iris.data
    y = iris.target
    std_s = StandardScaler()
    x = std_s.fit_transform(x)
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.3)
    knn = KNeighborsClassifier()
    params = {'n_neighbors': [3, 5, 7, 9, 11, 13]}
    gscv = GridSearchCV(knn, param_grid=params, cv=15)
    gscv.fit(train_x, train_y)
    score = gscv.score(test_x, test_y)
    predict_y = gscv.predict(test_x)
    print("score: {}".format(score))
    print("predict:\n{}".format(predict_y[:100]))
    print("test:\n{}".format(test_y[:100]))


if __name__ == "__main__":
    count_news()
    min_max_knn_fb()
    min_max_knn_iris()
    std_knn_iris()
