/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-04 18:34:47
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-04 20:09:01
 */
#include <stdio.h>
#include <string.h>
#define N 100

/**
 * @name: my_atol
 * @msg: 输入字符串，转换为整型数字，遇到其他字符停止
 * @param: 字符串指针
 * @return: 转换后的长整型数字
 */
long my_atol(const char *str);
long my_atol(const char *str){
    // 0: + , 1: -
    int sign_flag = 0;
    long result = 0;

    // 判断第一位是否为'-'或'+'
    if(str[0] == '-' || str[0] == '+'){
        sign_flag = str[0]/44;
    }else if(str[0] >= '0' && str[0] <= '9'){
        result = result*10 + str[0]%48;
    }else{
        return result;
    }
    // 遍历后续字符串
    for(int i = 1; str[i] >= '0' && str[i] <= '9'; i++){
        result = result*10 + str[i]%48;
    }

    return sign_flag ? 0 - result : result;
}

int main(int argc, char const *argv[])
{
    char str[N] = {'\0'};

    printf("input a string: ");
    fgets(str, N, stdin);
    unsigned long len = strlen(str);
    str[len - 1] = '\0';
    
    long a = my_atol(str);
    printf("%ld\n", a);

    return 0;
}
