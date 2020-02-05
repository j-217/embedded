/*
 * @Author: Ru_j
 * @Date: 2020-02-05 16:52:21
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-05 19:58:15
 * @Description: 已知数组内容如下 s[]=[1,2,3,4,5,6,7,8,9],输入一个数n(1<=n<=9)，使得该数组内容顺序后移动n个位置。如n=3时，数组后移3个位置后的内容为{7,8,9,1,2,3,4,5,6}
 */
#include <iostream>

using namespace std;

enum ARR_SIZE {
    SIZE = 6,
};

void print_arr(int (&arr)[ARR_SIZE::SIZE]) {
    for (int i = 0; i < ARR_SIZE::SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return ;
}

int get_lcm(int x, int y) {         // 辗转相除法获取最大公约数，使用公式法x * y = gcd * lcm计算lcm
    if (x <= 0 || y <= 0) {
        string e_msg = "ERROR: arguments must be positive number";
        throw e_msg;
    }

    if (x == y) {
        return x;
    }

    int dividend = x < y ? x : y,
        divisor = x > y ? x : y,
        remain = dividend % divisor;
    while (remain != 0) {
        dividend = divisor;
        divisor = remain;
        remain = dividend % divisor;
    }

    return x * y / divisor;         // gcd = divisor
}

void resort_arr(int (&arr)[ARR_SIZE::SIZE], int offset) {
    if (offset < 0) {                                               // unimpliment offset < 0
        string e_msg = "ERROR: arguments must be positive number";
        throw e_msg;
    }

    offset %= ARR_SIZE::SIZE;

    if (offset == 0) {
        return ;
    }

    int tmp = arr[offset],                                  // 保存第一个数移动后的位置的数据
        n = 1,
        cur_i = offset,                                     // 当前的坑位
        prev_i = 0,                                         // 本次要移动的数的下标
        lcm = get_lcm(ARR_SIZE::SIZE, offset),
        count = lcm / offset;                               // 计算移动多少次需要重置偏移位置

    for (; n < ARR_SIZE::SIZE; ++n) {
        prev_i = (cur_i - offset < 0) ? (cur_i - offset + ARR_SIZE::SIZE) : (cur_i - offset);

        arr[cur_i] = arr[prev_i];

        --count;

        // 经过count次需要重新设置一次偏移位置，否则会造成循环遍历，无法完成数组的整体遍历
        // 如arr[6], offset = 3, 会重复遍历arr[3], arr[0]; offset = 4, 会重复遍历arr[4], arr[1]
        if (count == 0) {
            arr[cur_i] = tmp;
            prev_i = (cur_i + 1 >= ARR_SIZE::SIZE) ? (cur_i + 1 - ARR_SIZE::SIZE) : cur_i + 1;
            tmp = arr[prev_i];
            count = lcm / offset;
        }

        cur_i = prev_i;
    }

    arr[cur_i] = tmp;

    return ;
}

int main() {
    int arr[ARR_SIZE::SIZE];
    for (int i = 0; i < ARR_SIZE::SIZE; ++i) {
        arr[i] = i + 1;
    }

    cout << "Before resort: ";
    print_arr(arr);

    cout << "After resort: ";
    resort_arr(arr, 2);
    print_arr(arr);

    cout << "After resort: ";
    resort_arr(arr, 3);
    print_arr(arr);

    return 0;
}