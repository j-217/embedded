'''
@Author: Ru_j
@Date: 2020-03-09 19:19:50
@LastEditors: Ru_j
@LastEditTime: 2020-03-09 19:54:24
@Description:
'''


from sklearn.model_selection import train_test_split
from sklearn.datasets import load_iris, load_boston, fetch_20newsgroups
import os


def print_infos(data_type, ratio):
    x_train, x_test, y_train, y_test = \
        train_test_split(data_type.data, data_type.target, test_size=ratio)
    return '-' * 100 + '\nX_TRAIN: \n{}\nY_TRAIN: {}\n' \
           .format(x_train, y_train)


if __name__ == "__main__":
    iris = load_iris()
    boston = load_boston()
    news = fetch_20newsgroups()
    path = os.path.dirname(__file__)
    with open(path + '/res.txt', 'a+') as file:
        file.write(print_infos(iris, .3) + print_infos(boston, .25) +
                   print_infos(news, .2))
