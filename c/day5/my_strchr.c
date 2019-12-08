/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 10:50:28
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 13:12:31
 */
#include <stdio.h>
#include <string.h>

/**
 * @name: my_strchr
 * @msg: see if char is in string, if found it return a pointer to the first occurrence of the char, else return a pointer to NULL
 * @param: 1.const char *, 2.int
 * @return: char *
 */
char *my_strchr(const char *str, int c){
    int i = 0;
    char *p = (char *)str;
    while (str[i] != '\0'){
        if(str[i] == c){
            return p+i;
        }
        i++;
    }
    return NULL;
}

// mock testing
// int main(){
//     char str[] = "hellow world";
//     char *p;
//     p = strchr(str, 'e');
//     if(p == NULL){
//         printf("not found");
//         return 0;
//     }
//     printf("%c\n", p[0]);

//     return 0;
// }