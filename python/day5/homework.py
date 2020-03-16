'''
@Author: Ru_j
@Date: 2020-03-06 20:33:30
@LastEditors: Ru_j
@LastEditTime: 2020-03-06 21:25:59
@Description:
'''
import random


class SweetPotato(object):
    __condiments = ['tomato sauce', 'sesame', 'sugar', 'mustard']

    def __init__(self, degree=0):
        self.name = 'sweet potato'
        self.degree = degree
        self.condiments = ''

    def cooked_string(self):
        degrees = ['raw', 'half-raw', 'cooked', 'burnt']
        if 4 <= self.degree <= 5:
            res = degrees[1]
        elif 5 < self.degree <= 8:
            res = degrees[2]
        elif 8 < self.degree:
            res = degrees[3]
        else:
            res = degrees[0]
        return res

    def cook(self):
        self.degree = self.degree + random.randrange(1, 4)

    def add_condiments(self, *args):
        lst = []
        for n in args:
            if n < len(self.__condiments):
                lst = lst + [self.__condiments[n]]
        if len(self.condiments) and len(lst):
            self.condiments = self.condiments + ', '
        self.condiments = self.condiments + ', '.join(lst)

    def __str__(self):
        return 'Product: {name}\nDegreee: {degree}\nFlavors: {condiment}' \
                .format(name=self.name,
                        degree=self.cooked_string(),
                        condiment=self.condiments)


if __name__ == "__main__":
    my_potato = SweetPotato()
    my_potato.cook()
    my_potato.cook()
    my_potato.add_condiments(0, 2, 3)
    my_potato.add_condiments(1, 2)
    print(my_potato)
