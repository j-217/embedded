/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-03 17:53:16
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-03 20:38:01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

/**
 * @name: most_ch
 * @msg: 返回字符串出现最多的字符并返回其第一次出现的位置的地址
 * @param: 字符串
 * @return: 字符串中出现最多的字符第一次出现的地址
 */
char *most_ch(char *str);

char *most_ch(char *str){
    unsigned long len = strlen(str);
    // 申请与字符串长度相同的数组，初始化为0
    int *count_ch = malloc(sizeof(int) * len);
    if(count_ch == NULL){
        printf("allocate failed\n");
        return str;
    }
    memset(count_ch, 0, len);

    // 遍历字符串,找到每个字符出现的次数,存放在数组对应位置
    for(int i=0; i<len; i++){
        for(int j=i; j<len; j++){
            if(str[j] == str[i]){
                count_ch[i]++;
            }
        }
    }

    // 遍历数组,找到最大值,返回其下标
    int max = 0;
    for(int i=1; i<len; i++){
        if(count_ch[i] > count_ch[max]){
            max = i;
        }
    }

    // 释放空间及指针
    free(count_ch);
    count_ch = NULL;

    return str + max;
}

int main(int argc, char const *argv[]){
    char str[N] = {'\0'};
    // char *str;

    printf("input a string: ");
    fgets(str, N, stdin);
    unsigned long len = strlen(str);
    str[len - 1] = '\0';

    char *res = most_ch(str);

    // 打印出现最多的字符，第一次出现的位置，出现后剩余的字符串
    printf("character is: %c, the first occured position is: %ld, remaining string: %s\n", \
        res[0], (res - str)/sizeof(char), res
    );

    return 0;
}
