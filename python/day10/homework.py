'''
@Author: Ru_j
@Date: 2020-03-13 19:50:16
@LastEditors: Ru_j
@LastEditTime: 2020-03-13 21:43:15
@Description:
'''

from sklearn.model_selection import train_test_split
from sklearn.datasets import load_boston
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import SGDRegressor, Ridge, RidgeCV
from sklearn.decomposition import PCA
import pandas as pd
import os
from sklearn.cluster import KMeans


def SGD_boston():
    boston = load_boston()
    x = boston.data
    y = boston.target
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.25)
    std_s = StandardScaler()
    train_x = std_s.fit_transform(train_x)
    test_x = std_s.fit_transform(test_x)

    sgd = SGDRegressor()
    sgd.fit(train_x, train_y)
    score = sgd.score(test_x, test_y)
    predict_y = sgd.predict(test_x)
    print(score)
    print(predict_y[:20])
    print(test_y[:20])
    # print(sgd.coef_)
    # print(sgd.intercept_)

    return None


def ridge_boston():
    boston = load_boston()
    x = boston.data
    y = boston.target
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.25)
    std_s = StandardScaler()
    train_x = std_s.fit_transform(train_x)
    test_x = std_s.fit_transform(test_x)

    # ridge = Ridge(alpha=1.5)
    ridge = RidgeCV(alphas=[1e-3, 1e-2, 1e-1, 1], cv=4)
    ridge.fit(train_x, train_y)
    score = ridge.score(test_x, test_y)
    predict_y = ridge.predict(test_x)
    print(score)
    print(predict_y[:20])
    print(test_y[:20])
    return None


def pca_kmeans():
    path = os.path.dirname(__file__) + \
        '/machine_learning_data/'
    products = pd.read_csv(path + 'products.csv')
    orders = pd.read_csv(path + 'orders.csv')
    aisles = pd.read_csv(path + 'aisles.csv')
    prior = pd.read_csv(path + 'order_products_prior.csv', iterator=True)
    prior = prior.get_chunk(10000)
    table_1 = pd.merge(prior, products, on=['product_id', 'product_id'])
    table_2 = pd.merge(table_1, orders, on=['order_id', 'order_id'])
    table = pd.merge(table_2, aisles, on=['aisle_id', 'aisle_id'])

    data = pd.crosstab(table['user_id'], table['aisle'])
    _pca = PCA(n_components=0.95)
    data = _pca.fit_transform(data)

    km = KMeans()
    km.fit(data)
    predict = km.predict(data)
    print(predict[:100])

    return None


if __name__ == "__main__":
    SGD_boston()
    ridge_boston()
    pca_kmeans()
