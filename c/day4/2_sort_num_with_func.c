/*
 * @Author: rujin 
 * @Date: 2019-11-21 21:53:33 
 * @Last Modified by: rujin
 * @Last Modified time: 2019-11-21 22:06:03
 */
#include <stdio.h>

// insert sort
int insert_sort(char *arr, int len){

    for(int i = 0; i < len; i++){
        int min_index = i;
        for(int j = i + 1; j < len; j++){
            // find minimum position
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        if(min_index != i){
            // set minimum to lowest position
            char temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
    return 0;
}

int main(){
    int n = 0, i = 0;
    char arr[4] = {0};
    char *p = arr;
    unsigned long len = sizeof(arr)/sizeof(char);
    TRY_AGAIN:
    printf("input a number(1000-9999): ");
    scanf("%d", &n);

    if(n > 999 && n < 10000){
        // split number and save in arr
        while(n > 0){
            arr[i] = n % 10;
            n /= 10;
            i++;
        }
        // call insert sort function
        insert_sort(p, len);
        // output sorted number
        for(int x = 0; x<len; x++){
            printf("%d", p[x]);
        }
        printf("\n");
    }else{
        printf("ERROR: Wrong range of numbers, try again.\n");
        goto TRY_AGAIN;
        // return 0;
    }

    return 0;
}