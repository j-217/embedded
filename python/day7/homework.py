'''
@Author: Ru_j
@Date: 2020-03-10 18:13:20
@LastEditors: Ru_j
@LastEditTime: 2020-03-11 09:47:18
@Description:
'''

"""
信息增益计算：

g(E) = -(6/15*log(6/15) + 9/15*log(9/15)) = 0.97096
g(D, has_job) = -(0*log0 + 5/5*log(5/5)) = 0
g(D, no_job) = -(6/10*log(6/10) + 4/10*log(4/10)) = 0.97096
g(D, job) = g(E) - 5/15*g(D, has_job) - 10/15*g(D, no_job) = 0.32365

g(D, has_house) = -(0 + 6/6*log(6/6)) = 0
g(D, no_house) = -(6/9*log(6/9) + 3/9*log(3/9)) = 0.918333
g(D, house) = g(E) - 6/15*g(D, has_house) - 9/15*g(D, no_house) = 0.41996

g(D, credit_l) = -(4/5*log(4/5) + 1/5*log(1/5)) = 0.7219
g(D, credit_m) = -(2/6*log(2/6) + 4/6*log(4/6)) = 0.918333
g(D, credit_h) = -(0 + 4/4*log(4/4)) = 0
g(D, credit) = g(E) - 5/15*g(D, credit_l) - 6/15*g(D, credit_m) - 4/15*g(D, credit_h) = 0.36299
"""


import pandas as pd
from sklearn.feature_extraction import DictVectorizer
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier


def decision_result():
    # 数据库
    file = "http://biostat.mc.vanderbilt.edu/wiki/pub/Main/DataSets/titanic.txt"
    titan = pd.read_csv(file)
    # 设置特征值 目标值
    x = titan[['pclass', 'age', 'sex']]
    y = titan['survived']
    # 填充特征值中缺失数据
    x['age'].fillna(x['age'].mean(), inplace=True)
    # 特征化特征值
    dic = DictVectorizer(sparse=False)
    x = dic.fit_transform(x.to_dict(orient='records'))
    # 分割训练集和测试集
    train_x, test_x, train_y, test_y = \
        train_test_split(x, y, test_size=.3)
    # 选择决策树算法
    dec_tree = DecisionTreeClassifier(max_depth=5)
    # 训练算法
    dec_tree.fit(train_x, train_y)
    # 获取预测值
    y_predict = dec_tree.predict([[30, 1, 0, 0, 1, 0]])
    print(dic.get_feature_names())
    print(y_predict)


if __name__ == "__main__":
    decision_result()
