/*
 * @Author: Ru_j
 * @Date: 2020-02-03 16:04:42
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-05-05 17:44:14
 * @Description:
 * @    1. GET_MAX 找出数组中最大的数;
 * @    2. GET_GCD_LCM 求2个数的最大公约数、最小公倍数
 * @    3. GET_PRIME 100~200间的素数
 * @    4. GET_NUMBERS 100以不能被3整除的数
 */
#include <iostream>
#include <cmath>

using namespace std;

#if GET_MAX
enum ARR_SIZE {
    SIZE = 10,
};

const int & get_max(const int (&arr)[ARR_SIZE::SIZE]) {
    size_t size = sizeof(arr)/sizeof(int);
    int max_index = 0;
    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    cout << &arr[max_index] << endl;                // test reference

    return arr[max_index];
}
#endif

#if GET_GCD_LCM
int get_gcd(int x, int y) {         // 更相减损法
    if (x <= 0 || y <= 0) {
        string e_msg = "ERROR: arguments must be positive number";
        throw e_msg;
    }

    if (x == y) {
        return x;
    }

    int count = 0;
    while (x % 2 == 0 && y % 2 == 0) {
        x >>= 1;
        y >>= 1;
        ++count;
    }

    int large = x > y ? x : y;
    int small = x < y ? x : y;

    while (large != 2 * small) {
        int tmp = large - small;
        large = tmp > small ? tmp : small;
        small = tmp < small ? tmp : small;
    }

    return small * (int)pow(2, count);
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
#endif

#if GET_PRIME
void get_prime() {
    int count = 0;                  // count primes
    for (int n = 100; n <= 200; ++n) {
        int i = 2;
        for (; i <= (int)sqrt(n); ++i) {
            if (n % i == 0) {
                break;
            }
        }
        if (i > (int)sqrt(n)) {
            count++;
            cout << n << " ";
        }
    }

    cout << endl;

    cout << count << endl;

    return ;
}
#endif

#if GET_NUMBERS
void get_numbers() {
    int count = 0;
    for (int i = 0; i <= 100; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        cout << i << " ";
        ++count;
    }
    cout << endl;
    cout << count << endl;

    return ;
}
#endif

int main() {

#if GET_MAX
    int arr_1[ARR_SIZE::SIZE] = {23, -7, 8, 50, 10, 11, 78, 89};
    const int &ret = get_max(arr_1);
    cout << &ret << endl;                           // test reference
    cout << "The max number in array is: " << ret << endl;
    cout << &arr_1[7] << endl;                      // test reference
#endif

#if GET_GCD_LCM
    try {
        int ret = get_gcd(260, 104);
        cout << "GCD: " << ret << endl;
        ret = get_lcm(36, 270);
        cout << "LCM: " << ret << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
#endif

#if GET_PRIME
    get_prime();
#endif

#if GET_NUMBERS
    get_numbers();
#endif

    return 0;
}