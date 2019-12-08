/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-11-28 15:25:50
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-11-29 08:41:33
 */
#include <stdio.h>
#include <string.h>
#define I_ROW 4
#define I_COL 3
#define S_ROW 5
#define S_COL 20

void set_arr_int(int arr_int[][I_COL]);
void get_arr_int(int arr_int[][I_COL]);
void set_arr_str(char arr_str[][S_COL]);
void get_arr_str(char arr_str[][S_COL]);
void strcmp_sort(char arr_str[][S_COL]);
void strlen_sort(char arr_str[][S_COL]);

// 输入整型二维数组
void set_arr_int(int arr_int[][I_COL]){
    printf("input %d numbers: ", I_ROW*I_COL);
    for(int row = 0; row<I_ROW; row++){
        for(int col = 0; col<I_COL; col++){
            scanf("%d", &arr_int[row][col]);
        }
    }
    while(getchar() != '\n')
        continue;

    return ;
}

// 输出整型二维数组
void get_arr_int(int arr_int[][I_COL]){
    for(int row = 0; row<I_ROW; row++){
        for(int col = 0; col<I_COL; col++){
            printf("%d ", arr_int[row][col]);
        }
    }
    printf("\n");

    return ;
}

// 输入字符串二维数组
void set_arr_str(char arr_str[][S_COL]){
    printf("input %d strings: ", S_ROW);
    for(int row = 0; row<S_ROW; row++){
        scanf("%s", arr_str[row]);
    }
    while(getchar() != '\n')
        continue;  

    return ;
}

// 输出字符串二维数组
void get_arr_str(char arr_str[][S_COL]){
    for(int row = 0; row<S_ROW; row++){
        printf("%s ", arr_str[row]);
    }
    printf("\n");

    return ;
}

// 根据字符串大小排序(升序)
void strcmp_sort(char arr_str[][S_COL]){
    for(int i = 0; i<S_ROW; i++){
        for(int j = 0; j<S_ROW-i-1; j++){
            if(strcmp(arr_str[j], arr_str[j+1]) > 0){
                char temp[S_COL] = {'\0'};
                strcpy(temp, arr_str[j+1]);
                strcpy(arr_str[j+1], arr_str[j]);
                strcpy(arr_str[j], temp);
            }
        }
    }

    return ;
}

// 根据字符串长度排序(升序)
void strlen_sort(char arr_str[][S_COL]){
    for(int i = 0; i<S_ROW; i++){
        for(int j = 0; j<S_ROW-i-1; j++){
            if(strlen(arr_str[j]) > strlen(arr_str[j+1])){
                char temp[S_COL] = {'\0'};
                strcpy(temp, arr_str[j+1]);
                strcpy(arr_str[j+1], arr_str[j]);
                strcpy(arr_str[j], temp);
            }
        }
    }

    return ;
}

int main(int argc,char *argv[]){
    int arr_int[I_ROW][I_COL] = {0};
    char arr_str[S_ROW][S_COL] = {'\0'};
    int operator = -1;

    while(1){
        printf("*****Menu*****\n");
        printf("1: input integer array\n");
        printf("2: output integer array\n");
        printf("3: input string array\n");
        printf("4: output string array\n");
        printf("5: sorting arr_str by character\n");
        printf("6: sorting arr_str by length\n");
        printf("0: quit\n");
        printf("**************\n");
        printf("Choose one operator: ");
        scanf("%d", &operator);
        // 消除到'\n'
        while(getchar() != '\n')
            continue;  

        switch (operator)
        {
            case 1:
                set_arr_int(arr_int);
                break;

            case 2:
                get_arr_int(arr_int);
                break;

            case 3:
                set_arr_str(arr_str);
                break;

            case 4:
                get_arr_str(arr_str);
                break;

            case 5:
                strcmp_sort(arr_str);
                printf("sorted: ");
                get_arr_str(arr_str);
                break;

            case 6:
                strlen_sort(arr_str);
                printf("sorted: ");
                get_arr_str(arr_str);
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