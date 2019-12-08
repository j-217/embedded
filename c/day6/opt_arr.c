/*
 * @Descripttion: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-25 17:28:19
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-25 17:45:21
 */
#include <stdio.h>

int main(){
    int arr[10] = {0}, len = sizeof(arr)/sizeof(int);

    // 输入10个数字存入数组
    printf("input 10 numbers: ");
    for(int i = 0; i<len; i++){
        scanf("%d", &arr[i]);
    }

    // 打印数组
    printf("arr is : ");
    for(int i = 0; i<len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 求最大值
    int max = arr[0];
    for(int i = 1; i<len; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    printf("maximum: %d\n", max);

    // 排序
    for(int i = 0; i < len - 1; i++){
        for(int j = 0; j<len-i-1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("sorted arr is : ");
    for(int i = 0; i<len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 打印次大值
    int next_max = arr[1];
        max = arr[0];
    // 如果假设的next_max > max,交换
    if(max < next_max){
        max = max + next_max;
        next_max = max - next_max;
        max = max - next_max;
    }

    for(int i = 2; i<len; i++){
        // 如果arr[i]比next_max大，确认arr[i]是否比max大
        if(arr[i] > next_max){
            if(arr[i] > max){
                next_max = max;
                max = arr[i];
            }else{
                next_max = arr[i];
            }  
        }
    }

    printf("next_max: %d\n", next_max);

    return 0;
}