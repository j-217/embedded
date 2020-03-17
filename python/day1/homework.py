'''
@Author: Ru_j
@Date: 2020-03-02 17:21:24
@LastEditors: Ru_j
@LastEditTime: 2020-03-02 17:54:41
@Description: finger-guessing game
'''

import random

def func(n):
    n %= 3
    computer = random.randrange(0, 3)
    res = "Draw Game" if n == computer else "You Win" if n == (computer + 1) % 3 else "You Loss, Try Again"
    return res

if __name__ == "__main__":
    num = int(input("Your Choice: Scissor(0) / Rock(1) / Paper(2) \n"))
    print(func(num))