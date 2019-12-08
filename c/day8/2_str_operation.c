/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-27 20:00:42
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-27 21:42:43
 */
#include <stdio.h>

// 函数声明
int my_strlen(char *str);
char *my_strchr(char *str, char c);
char *my_strlstchr(char *str, char c);
int my_strcmp(char *str1, char *str2);
char *most_appeared_char(char *str);

// 函数定义
// my_strlen: 计算字符串长度
int my_strlen(char *str){
    char *p = str;
    while(*p != '\0'){
        p++;
    }

    return p - str;
}

// my_strchr: 查找字符在字符串中第一次出现的位置
char *my_strchr(char *str, char c){
    char *p = NULL;
    while(*str != '\0'){
        if(*str == c){
            p = str;
            return p;
        }
        str++;
    }
    return p;
}

// my_strlstchr: 查找字符在字符串中最后一次出现的位置
char *my_strlstchr(char *str, char c){
    char *p = NULL;
    // 正序查找
    while(*str != '\0'){
        if(*str == c){
            p = str;
        }
        str++;
    }

    return p;
}

// my_strcmp: 比较两个字符串的大小
int my_strcmp(char *str1, char *str2){
    while(*str1 != '\0' && *str2 != '\0'){
        if(*str1 != *str2){
            break;
        }
        str1++; 
        str2++;
    }
    return *str1 - *str2;
}

// most_appeared_char: 找到字符串中出现次数最多的字符，返回该字符第一次出现的位置
char *most_appeared_char(char *str){
    int len = my_strlen(str);
    int arr[100] = {0};
    // 逐一计算字符串中出现的数字
    for(int i=0; i<len; i++){
        for(int j=i; j<len; j++){
            if(str[j] == str[i]){
                arr[i]++;
            }
        }
    }

    int max_index = 0;
    for(int i=0; i<len; i++){
        if(arr[max_index] < arr[i]){
            max_index = i;
        }
    }
    
    return str + max_index;
}

int main(int argc,char *argv[]){
    char *str = "hello world";
    
    // use my_strlen
    int len = my_strlen(str);
    printf("use my_strlen: %d\n", len);

    // use my_strchr
    char *p_c = my_strchr(str, 'e');
    if(p_c == NULL){
        printf("NOT FOUND\n");
        return 0;
    }
    printf("use my_strchr: %s\n", p_c);

    // use my_strlstchr
    char *p_lstc = my_strlstchr(str, 'l');
    if(p_lstc == NULL){
        printf("use my_strlstchr: NOT FOUND\n");
        return 0;
    }
    printf("use my_strlstchr: %s\n", p_lstc);

    // use my_strcmp
    int cmp_res = my_strcmp(str, "hello xian");
    // 判断cmp_res, 返回相应语句
    char *cmp_result = cmp_res == 0 ? "str_1 = str_2" : cmp_res > 0 ? "str_1 > str_2" : "str_1 < str_2";
    printf("use my_strcmp: %s\n", cmp_result);

    // use most_appeared_char
    char *p_most = most_appeared_char(str);
    printf("the most of appeared character is: %c, first appeared position: %s\n", *p_most, p_most);

    return 0;
}