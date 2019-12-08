/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 11:52:58
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 12:17:07
 */
#include <stdio.h>
#include <string.h>

/**
 * @name: my_strcat
 * @msg: concat source string to destination string, then return destination string.
 * @param: 1.char *dest, 2.const char *src
 * @return: char *dest
 */
char *my_strcat(char *dest, const char *src){
    unsigned long len_d = strlen(dest);
    int i = 0;
    for(; src[i] != '\0'; i++){
        dest[len_d + i] = src[i];
    }
    dest[len_d + i] = '\0';

    return dest;
}

// mock testing
// int main(){
//     char str1[] = "hello", str2[] = "world";
//     my_strcat(str1, str2);
//     printf("%s", str1);

//     return 0;
// }