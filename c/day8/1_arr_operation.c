/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-27 20:45:27
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-28 08:41:51
 */
#include <stdio.h>
#define N 5

// 函数声明
void arr_input(int *arr, int n);
void arr_output(int *arr, int n);
int *cal_p_max(int *arr, int n);
int *cal_p_min(int *arr, int n);
void bubble_sort(int *arr, int n);
void swap_max_min(int *arr, int n);

// 函数定义
// 输入数组
void arr_input(int *arr, int n){
    printf("input %d numbers: ", n);

    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    while(getchar() != '\n')
        continue;

    return ;
}

// 输出数组
void arr_output(int *arr, int n){
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return ;
}

// 返回数组中最大值的指针
int *cal_p_max(int *arr, int n){
    int *p_max = arr;
    for(int i = 0; i<n; i++){
        if(arr[i] > *p_max){
            p_max = &arr[i];
        }
    }

    return p_max;
}

// 返回数组中最小值的指针
int *cal_p_min(int *arr, int n){
    int *p_min = arr;
    for(int i = 0; i<n; i++){
        if(arr[i] < *p_min){
            p_min = &arr[i];
        }
    }

    return p_min;
}

// 交换最大值最小值位置
void swap_max_min(int *arr, int n){
    int *p_max = cal_p_max(arr, n),
        *p_min = cal_p_min(arr, n);
    int temp = *p_max;
    *p_max = *p_min;
    *p_min = temp;
}

// 冒泡排序(升序)
void bubble_sort(int *arr, int n){
    for(int i = 0; i<n-1; i++){
        for(int j = 0; j<n-i-1; j++){
            if(arr[j] > arr[j+1]){
                arr[j] = arr[j] + arr[j+1];
                arr[j+1] = arr[j] - arr[j+1];
                arr[j] = arr[j] - arr[j+1];
            }
        }
    }
    return ;
}

int main(int argc,char *argv[]){
    int arr[N] = {0};
    int operation = -1, *p_max = NULL, *p_min = NULL;

    while(1){
        printf("*****Menu*****\n");
        printf("1: input array\n");
        printf("2: output array\n");
        printf("3: cal_p_max\n");
        printf("4: cal_p_min\n");
        printf("5: bubble sort(ascending)\n");
        printf("6: swap max and min\n");
        printf("0: quit\n");
        printf("**************\n");
        printf("Choose your operation: ");
        scanf("%d", &operation);
        // 消除'\n'
        while(getchar() != '\n')
            continue;  
    
        switch (operation)
        {
            case 1:
                arr_input(arr, N);
                break;

            case 2:
                arr_output(arr, N);
                break;

            case 3:
                p_max = cal_p_max(arr, N);
                printf("the maximum is: %d\n", *p_max);
                break;

            case 4:
                p_min = cal_p_min(arr, N);
                printf("the minimum is: %d\n", *p_min);
                break;

            case 5:
                bubble_sort(arr, N);
                printf("sorted array: ");
                for(int i = 0; i<N; i++){
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;

            case 6:
                swap_max_min(arr, N);
                break;
                
            case 0:
                printf("Quit!\n");
                return 0;
            
            default:
                printf("ERROR: incorrect input, try again.\n");
                break;
        }
    }
    return 0;
}