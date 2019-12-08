/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 14:19:27
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 15:01:05
 */
#include <stdio.h>
// #include <string.h>

/**
 * @name: my_strcpy
 * @msg: copy string to str_cpy
 * @param: 1.char *str_cpy, 2.const char *src
 * @return: char *
 */
char *my_strcpy(char *str_cpy, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        str_cpy[i] = src[i];
        i++;
    }
    str_cpy[i] = '\0';

    return str_cpy;
}

// mock testing;
// int main(){
//     char str[] = "hello", str_cpy[200];
//     my_strcpy(str_cpy, str);
//     printf("%s\n", str_cpy);

//     return 0;
// }