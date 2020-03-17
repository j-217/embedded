'''
@Author: Ru_j
@Date: 2020-03-03 17:05:41
@LastEditors: Ru_j
@LastEditTime: 2020-03-03 17:52:55
@Description: 1. bubble_sort    2.multiplication table  3. print triangle based on input number
'''

def bubble_sort(lst):
    size = len(lst)

    for n in range(0, size - 1):
        for m in range(0, size - 1 - n):
            if lst[m + 1] < lst[m]:
                lst[m + 1], lst[m] = lst[m], lst[m + 1]

    return lst

def mul_table():
    for n in range(1, 10):
        for m in range(1, n + 1):
            print("{} * {} = {}".format(n, m, n*m), end="\t")
        print()

def draw_triangle(n):
    if n <= 1: return
    list(map(lambda x: print('*' * x), range(1, n)))


if __name__ == "__main__":
    lst = [n for n in range(10, 0, -1)]
    print(bubble_sort(lst))

    mul_table()

    draw_triangle(7)