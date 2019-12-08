/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-26 15:06:14
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-26 17:10:53
 */
#include <stdio.h>

void swap_1(int a, int b);
void swap_2(int *a, int *b);

void swap_1(int a, int b){
    a = a + b;
    b = a - b;
    a = a - b;

    return ;
}

void swap_2(int *p_a, int *p_b){
    int temp;
    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;

    return ;
}

int main(){
    int a = 5, b = 8;

    printf("a = %d, b = %d\n", a, b);
    swap_1(a, b);
    printf("use swap_1(no change): a = %d, b = %d\n", a, b);

    swap_2(&a, &b);
    printf("use swap_2: a = %d, b = %d\n", a, b);

    return 0;
}