/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-28 10:54:39
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-28 11:17:49
 */
#include <stdio.h>
#include <string.h>
#define N 50

// 函数声明
char *my_strcpy(char *str_1, char *str_2);
char *my_strcat(char *str_1, char *str_2);

/**
 * @name: my_strcpy
 * @msg: 将str_2中字符复制到str_1中，返回str_1的首地址
 * @param: 1. str_1首地址, 2. str_2首地址
 * @return: str_1首地址
 */
char *my_strcpy(char *str_1, char *str_2){
    int i = 0;
    for(; str_2[i] != '\0'; i++){
        str_1[i] = str_2[i];
    }
    str_1[i] = '\0';

    return str_1;
}

/**
 * @name: my_strcat
 * @msg: 将str_2中字符连接到str_1后，返回str_1的首地址
 * @param: 1. str_1首地址, 2. str_2首地址
 * @return: str_1首地址
 */
char *my_strcat(char *str_1, char *str_2){
    unsigned long len = strlen(str_1);
    int i = 0;
    for(; str_2[i] != '\0'; i++){
        str_1[len + i] = str_2[i];
    }
    str_1[len + i] = '\0';

    return str_1;
}

int main(int argc,char *argv[]){
    char str_1[N] = {'\0'},
         *str_2 = "hellow xian";
    
    my_strcpy(str_1, str_2);
    printf("use my_strcpy: %s\n", str_1);

    my_strcat(str_1, str_2);
    printf("use my_strcat: %s\n", str_1);

    return 0;
}