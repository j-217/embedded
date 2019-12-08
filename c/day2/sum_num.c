#include <stdio.h>

int main(){
    int sum = 0, n = 0;
    printf("input a number: ");
    scanf("%d", &n);
    while(n){
        sum += n;
        n--;
    }
    printf("sum is %d\n", sum);
    return 0;
}
