/*
 * @Author: Ru_j
 * @Date: 2020-02-04 16:00:15
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-04 18:01:50
 * @Description:
 * @    1. GET_SUM 输入n，求 1/1! - 1/2! + 1/3! - 1/4! ... 1/n!;
 * @    2. COUNT_LIGHT 一条长廊里依次装有n盏电灯，从头到尾编号1、2、3、…n-1、n。每盏电灯由一个拉线开关控制。开始，电灯全部关着。有n个学生从长廊穿过。第一个学生把号码凡
 * @       是1的倍数的电灯的开关拉一下；接着第二个学生把号码凡是2的倍数的电灯的开关拉一下；接着第三个学生把号码凡是3的倍数的电灯的开关拉一下；如此继续下去，最后第n个学生
 * @       把号码凡是n的倍数的电灯的开关拉一下。n个学生按此规定走完后，长廊里电灯有几盏亮着。注：电灯数和学生数一致。
 */
#include <iostream>

using namespace std;

#if GET_SUM
size_t get_fac(size_t n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * get_fac(n - 1);
}

float get_sum(int n) {
    if (n < 0) {
        string e_msg = "ERROR: argument must be positive number";
        throw e_msg;
    }

    if (n == 0) {
        return 1.0f;
    }

    float sum = 0.0f;
    for (int i = 1; i <= n; ++i) {
        sum += (i & 1) ? (1.0 / get_fac(i)) : -(1.0 / get_fac(i));
    }

    return sum;
}
#endif

#if COUNT_LIGHT
int count_light(const int n) {
    int *p = new int[n]();
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            p[j - 1] = (p[j - 1] + 1) % 2;
        }
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] == 1) {
            ++count;
        }
    }

    delete[] p;
    return count;
}
#endif

int main() {
#if GET_SUM
    float ret = get_sum(5);
    cout << ret << endl;
#endif

#if COUNT_LIGHT
    cout << count_light(10000000) << endl;
#endif

    return 0;
}