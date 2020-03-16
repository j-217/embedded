'''
@Author: Ru_j
@Date: 2020-03-11 17:50:07
@LastEditors: Ru_j
@LastEditTime: 2020-03-12 09:39:46
@Description:
'''


import os
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import MinMaxScaler


def std_scalar(data):
    ss = StandardScaler()
    data = ss.fit_transform(data)
    print(data)


def min_max_scalar(data):
    mms = MinMaxScaler(feature_range=(-1, 1))
    data = mms.fit_transform(data)
    print(data)


if __name__ == "__main__":
    file_path = os.path.dirname(__file__)
    dating = pd.read_csv(file_path + '/dating.txt')
    data = dating[['milage', 'Liters', 'Consumtime', 'target']]
    data2 = dating[['milage', 'Liters', 'Consumtime']]
    std_scalar(data)
    min_max_scalar(data2)
