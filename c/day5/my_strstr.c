/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-23 12:35:31
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-23 15:04:39
 */
#include <stdio.h>
#include <string.h>

/**
 * @name: my_strstr
 * @msg: fint needle in haystack, return the pointer of first postion in haystack, otherwise return NULL.
 * @param: 1.const char* haystack, 2.const char *needle
 * @return: char *
 */
char *my_strstr(const char *haystack, const char *needle){
    char *p_h = (char *)haystack, *p_n = (char *)needle, *p = NULL;
    int i_h = 0, len_h = strlen(haystack), len_n = strlen(needle);

    // 如果needle长度大于haystack， 直接返回NULL
    if(len_h < len_n){
        return p;
    }

    while (p_h[i_h] != '\0'){
        // 找到needle[0]在haystack中的位置
        if(p_h[i_h] == p_n[0]){
            int i_n = 1;
            // 遍历needle, 逐一与haystack对比, 存在不同break本次循环
            for(; i_n<len_n; i_n++){
                if(p_h[i_h + i_n] != p_n[i_n]){
                    break;
                }
            }
            // 如果循环完成,表示找到完整的needle,返回此时的haystack指针位置
            if(i_n == len_n){
                return p_h + i_h;
            }
        }
        i_h++;
    }

    return p;
}

// mock testing
// int main(){
//     char str1[] = "hi everyone this is Joey speaking", str2[] = "haha", str3[] = "Joey";
//     char *p = my_strstr(str1, str3);

//     printf("%s", p);

//     return 0;
// }