/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 12:09:59
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 12:46:28
 */
#include <stdio.h>
#include <string.h>

/**
 * @name: my_strcmp
 * @msg: compare two string from first letter till the end, if equal check next letter, otherwise subtract the letter of str2 from the letter of str1, return the result.
 * @param: 1.const char *str1, 2.const char *str2
 * @return: int result
 */
int my_strcmp(const char *str1, const char *str2){
    int i = 0, result = 0;
    while (str1[i] != '\0' || str2[i] != '\0'){
        if(str1[i] != str2[i]){
            result = str1[i] - str2[i];
            return result;
        }
        i++;
    }
    
    return result;
}

// mock testing
// int main(){
//     char str1[] = "hello", str2[] = "world";
//     int i = my_strcmp(str1, str2);
//     printf("%d\n", i);
    
//     return 0;
// }