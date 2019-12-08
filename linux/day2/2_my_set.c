/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-03 18:19:13
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-03 20:38:56
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

/**
 * @name: my_set
 * @msg: 返回一个字符串的字符的集合
 * @param: 1.集合的指针， 2.字符串的指针
 * @return: 该字符串的集合
 */
char *my_set(char *set, const char *str);

char *my_set(char *set, const char *str){
    // 遍历str
    for(int i = 1; str[i] != '\0'; i++){
        // 遍历set，如果发现相同，跳出本次遍历
        int j = 0;
        for(j = 0; set[j] != '\0'; j++){
            if(str[i] == set[j]){
                break;
            }
        }
        // 判断是否遍历完set
        if(j == strlen(set)){
            set[j] = str[i];
        }    
    }

    return set;
}

int main(int argc, char const *argv[]){
    char str[N] = {'\0'};

    printf("input a string: ");
    fgets(str, N, stdin);

    unsigned long len = strlen(str);
    // 去除fgets在输入内容后添加的\n
    str[len-1] = '\0';
    char *set = malloc(sizeof(char) * len);
    if(set == NULL){
        printf("allocate failed\n");
        return 0;
    }
    memset(set, '\0', len);

    // 设置set首位与str首位相同
    set[0] = str[0];

    my_set(set, str);

    // 打印集合，集合长度
    printf("set is: %s, set length is: %ld\n", set, strlen(set));

    free(set);
    set = NULL;

    return 0;
}
