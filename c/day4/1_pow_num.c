/*
 * @Author: rujin 
 * @Date: 2019-11-21 17:14:51 
 * @Last Modified by: rujin
 * @Last Modified time: 2019-11-21 17:35:48
 */
#include <stdio.h>

int main(){
    // q for quotient, r for reminder
    int n = 0, sum = 0, r = 0;
    TRY_AGAIN:
    printf("input a number(1000-9999): ");
    scanf("%d", &n);

    if(n > 999 && n < 10000){
        while(n > 0){
            r = n % 10;
            n = n / 10;  
            sum += r * r;
        }   
    }else{
        printf("ERROR: Wrong range of numbers, try again.\n");
        goto TRY_AGAIN;
        // return 0;
    }
    
    printf("%d\n", sum);

    return 0;
}
