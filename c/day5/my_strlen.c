/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 10:43:43
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 11:20:04
 */
#include <stdio.h>

/**
 * @name: my_strlen
 * @msg: calculate length of string
 * @param: char *
 * @return: unsigned long
 */
unsigned long my_strlen(const char *str){
    unsigned long len = 0;
    while(str[len] != '\0') {
        len++;
    }

    return len;
}

// mock testing
// int main(){
//     char arr[] = "hello world";
//     unsigned long len = my_strlen(arr);

//     printf("%lu", len);

//     return 0;
// }