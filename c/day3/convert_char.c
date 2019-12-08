/*
 * @Author: rujin 
 * @Date: 2019-11-20 17:18:50 
 * @Last Modified by: rujin
 * @Last Modified time: 2019-11-20 17:46:11
 */
#include <stdio.h>

int main(){
    char l = '0';
    char *p = &l;

    printf("input a char: ");
    scanf("%c", &l);

    printf("show %%c mode: %c\n", l);
    printf("show %%x mode: %x\n", l);
    printf("show %%d mode: %d\n", l);
    printf("show %%s mode: %s\n", p);

    return 0;
}