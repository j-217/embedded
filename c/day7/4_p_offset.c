/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-26 20:49:22
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-26 21:02:44
 */
#include <stdio.h>

int main(){
    char *p_c = "character pointer testing";
    int arr_int[] = {2, 3, 4, 5, 6, 7, 8, 9}, *p_i = arr_int;
    short arr_st[] = {11, 12, 13, 14, 15, 16}, *p_st = arr_st;
    float arr_f[] = {10.10, 11.11, 12.12, 13.13, 14.14}, *p_f = arr_f;
    double arr_db[] = {1.1, 2.2, 3.3, 4.4, 5.5}, *p_db = arr_db;

    printf("offset p_c: %ld, p_c[3]=%c\n", sizeof(char), *(p_c + 3));
    printf("offset p_i: %ld, p_i[4]=%d\n", sizeof(int), *(p_i + 4));
    printf("offset p_st: %ld, p_st[5]=%hd\n", sizeof(short), *(p_st + 5));
    printf("offset p_f: %ld, p_f[1]=%lf\n", sizeof(float), p_f[1]);
    printf("offset p_db: %ld, p_db[2]=%lf\n", sizeof(double), p_db[2]);

    return 0;
}