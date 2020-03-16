'''
@Author: Ru_j
@Date: 2020-03-04 17:20:29
@LastEditors: Ru_j
@LastEditTime: 2020-03-04 19:59:48
@Description:
'''

import re


def get_pets():
    dict_1 = {'type': 'dog', 'name': 'litte-dot', 'host': 'Jack'}
    dict_2 = {'type': 'cat', 'name': 'tigerlike', 'host': 'Tom'}
    dict_3 = {'type': 'snake', 'name': 'long-long-long', 'host': 'Petter'}
    pets = [dict_1, dict_2, dict_3]
    keys = [key for key in pets[0].keys()]
    for pet in pets:
        print("{}'s pet is a/an {} which they call him {}".format(pet[keys[2]], pet[keys[0]], pet[keys[1]]))


def get_favorite_places():
    friends = {
        'LaoWang': ['Beijing', 'Shanghai', 'Guangzhou'],
        'XiaoLi': ['Xi\'an', 'Shenzhen'],
        'Sun': ['USA', 'JAPAN']
        }
    pat = re.compile(r',\s(\w+)$')
    for k, v in friends.items():
        str = ", ".join(v)
        res = re.search(pat, str)
        str = re.sub(pat, ' and ' + res.group(1), str) if res else str
        print('My friend {}, his favorite places is {}'.format(k, str))


def get_cities():
    cities = {
        'Xi\'an': {
            'country': 'China',
            'population': 1000,
            'fact': 'ancient capital'
            },
        'Tokyo': {'country': 'Japan', 'population': 1350, 'fact': 'not hot'},
        'New York': {
            'country': 'USA',
            'population': 850,
            'fact': 'a city of immigrants'
            }
        }
    for city, desc in cities.items():
        print("Country: {} City: {} Population: {} Fact: {}"
              .format(desc['country'], city, desc['population'], desc['fact']))


def get_menu(menu):
    for item in menu:
        print("%s\t" % (item))
    print()


def update_menu(old, new, menu):
    menu = list(menu)
    if old in menu:
        menu.remove(old)
        menu.append(new)
    return tuple(menu)


if __name__ == "__main__":
    get_pets()
    get_favorite_places()
    get_cities()
    menu = ('noodle', 'rice', 'hamburger', 'milk', 'beer')
    get_menu(menu)
    get_menu(update_menu('noodle', 'new_noodle', menu))
