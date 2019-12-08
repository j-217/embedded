/*
 * @Author: rujin 
 * @Date: 2019-11-20 17:27:11 
 * @Last Modified by: rujin
 * @Last Modified time: 2019-11-20 17:40:10
 */
#include <stdio.h>

int main(){
    float pi = 3.141592, r = 0.0, L = 0.0, S = 0.0;

    printf("input a r: ");
    scanf("%f", &r);
    if(r < 0){
        printf("ERROR: Wrong number, try again.\n");
        return 0;
    }

    L = 2 * pi * r;
    S = pi * r * r;

    printf("result: L = %f, S = %f\n", L, S);

    return 0;
}