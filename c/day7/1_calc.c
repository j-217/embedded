/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-26 11:12:00
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-26 11:37:48
 */
#include <stdio.h>

char cal_syb(void);

char cal_syb(void){
    char c = '\0';
    
    printf("input a symbol(+-*/): ");
    scanf("%*c%c", &c);
    
    return c;
}

int main(){
    float x, y, result;
    printf("input two numbers: ");
    scanf("%f%f", &x, &y);

    char symbol = '\0';

    symbol = cal_syb();

    switch (symbol)
    {
        case '+':
            result = x + y;
            break;
        
        case '-':
            result = x - y;
            break;

        case '*':
            result = x * y;
            break;

        case '/':
            if(y != 0){
                result = x / y;
                break;
            }
            printf("ERROR: y can not be zero\n");
            return 0;
            
        default:
            printf("ERROR: incorrect symbol\n");
            return 0;
    }

    printf("result is : %.2f\n", result);

    return 0;
}