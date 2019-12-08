/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-04 16:58:34
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-04 18:54:25
 */
#include <stdio.h>
#define N 100

/**
 * @name: str_split
 * @msg: 输入字符串和分割符，将该字符串分割
 * @param: 1.指针数组，保存字符串分割后的各字符首地址 2.被分割的字符串 3.分割符
 * @return: 存放各字符首地址的指针数组
 */
char **str_split(char *arr[], char *str, const char c);
char **str_split(char *arr[], char *str, const char c){
    // flag = 1 arr可以存储
    int flag = 1, i_arr = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == c){
            str[i] = '\0';
            flag = 1;
            continue;
        }
        if(str[i] != c && flag){
            arr[i_arr] = str + i;
            flag = 0;
            i_arr++;
        }
    }

    return arr;
}

int main(int argc, char const *argv[])
{
    // mock testing
    char str[] = "  hello world guess who am i   ";

    char *arr[N] = {NULL};
    str_split(arr, str, ' ');

    for(int i=0; arr[i] != NULL; i++){
        printf("%s\n", arr[i]);
    }

    return 0;
}

