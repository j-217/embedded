#include <stdio.h>
#include <string.h>

#define N 10

/**
 * @name: quick_sort
 * @msg: 快速排序
 * @param: 1.int arr[] 要排序的数组首地址
 *         2.int low 数组下界下标
 *         3.int high 数组上界下标
 * @return: 函数调用的状态 1: 成功 -1: 失败
 */
int quick_sort(int arr[], int low, int high){
    // 判断是否越界或在区间为1
    if(low >= high){
        return -1;
    }

    int pivot = arr[low],
        i_low = low,
        i_high = high;

    while(1){
        if(i_low == i_high){
            arr[i_low] = pivot;
            break;
        }

        while(i_low < i_high && arr[i_high] >= pivot){
            i_high--;
        }
        if(i_low < i_high){
            arr[i_low] = arr[i_high];
            i_low++; 
        }
        

        while(i_low < i_high && arr[i_low] <= pivot){
            i_low++;
        }
        if(i_low < i_high){
            arr[i_high] = arr[i_low];
            i_high--;
        }
    }

    quick_sort(arr, low, i_low - 1);
    quick_sort(arr, i_low + 1, high);

    return 1;
}

/**
 * @name: get_arr
 * @msg: 打印输出数组
 * @param: 1.int arr[] 数组的首地址
 *         2.int len 数组的长度 
 * @return: void
 */
void get_arr(int arr[], int len){
    for(int i = 0; i<len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return ;
}

int main(int argc, char const *argv[])
{
    int arr[N] = {20, 31, 12, 5, 79, 88, 31, 27, 9, 10};

    printf("BEFORE SORTED: ");
    get_arr(arr, N);

    quick_sort(arr, 0, N-1);

    printf("AFTER SORTED: ");
    get_arr(arr, N);
    
    return 0;
}
