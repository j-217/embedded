/*
 * @Author: rujin 
 * @Date: 2019-11-20 17:18:34 
 * @Last Modified by: rujin
 * @Last Modified time: 2019-11-20 17:45:04
 */
#include <stdio.h>

int main(){
    int a = 4, b = 8, c = 10;
    
    printf("before switch: a = %d, b = %d, c = %d\n", a, b, c);

    a = a + b + c;
    b = a - b - c;
    c = a - b - c;
    a = a - b - c;

    printf("after switch: a = %d, b = %d, c = %d\n", a, b, c);

    return 0;
}