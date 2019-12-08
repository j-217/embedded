/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 14:32:11
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 15:07:25
 */
#include <stdio.h>
#include "my_string.h"

int main(){
    // 使用my_strcat
    char str1[] = "hello", str2[] = "world";
    my_strcat(str1, str2);
    printf("use my_strcat: %s\n", str1);

    // 使用my_strcpy
    char str3[] = "hello", str4[] = "welcome";
    my_strcpy(str3, str4);
    printf("use my_strcpy: %s\n", str3);

    // 使用my_strlen
    char str5[] = "calculate my length";
    int len = my_strlen(str5);
    printf("use my_strlen: %d\n", len);

    // 使用my_strcmp
    char str6[] = "big", str7[] = "small";
    int cmp = my_strcmp(str1, str2);
    printf("use my_strcmp: %d\n", cmp);
    
    // 使用my_strchr
    char str8[] = "find character from me";
    char *p_c = my_strchr(str8, 'n');
    if(p_c == NULL){
        printf("use my_strchr: NOT FOUND\n");
    }else{
        printf("use my_strchr: %c\n", p_c[0]);
    }
    
    // 使用my_strstr
    char str9[] = "I'm a long sentence, you can find string from me", str10[] = "long";
    char *p_s = my_strstr(str9, str10);
    printf("use my_strstr: %s\n", p_s);

    return 0;
}