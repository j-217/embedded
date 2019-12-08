/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 10:43:43
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-26 17:07:59
 */
#include <stdio.h>

/**
 * @name: my_strlen
 * @msg: calculate length of string
 * @param: char *
 * @return: int
 */
int my_strlen(const char *str){
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }

    return len;
}

// mock testing
int main(){
    char arr[] = "hello world";
    int len = my_strlen(arr);

    printf("%d\n", len);

    return 0;
}