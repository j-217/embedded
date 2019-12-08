/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-05 18:02:25
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-06 09:45:59
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 5

// DEF struct
typedef struct {
    char name[15];
    int height;
    struct {
        float chinese,
              english,
              mathematics;
    }scores;
    
}s_person;

// 数组是否输入 1:y 0:n
enum IS_SET{
    FALSE_S,
    TRUE_S
};

// >> DECLARE FUNC

/**
 * @name: set_arr
 * @msg: 输入结构体数组
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回int 1:添加成功 0:添加失败
 */
int set_arr(s_person arr[], int len);

/**
 * @name: get_arr
 * @msg: 打印结构体数组
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回体数组指针
 */
s_person *get_arr(s_person arr[], int len);

/**
 * @name: max_height
 * @msg: 打印身高最高的人员
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回身高最高人员的结构体
 */
s_person max_height(s_person arr[], int len);

/**
 * @name: max_total_score
 * @msg: 打印总分最高的人员
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回总分最高人员的结构体
 */
s_person max_total_scores(s_person arr[], int len);

/**
 * @name: sort_by_height
 * @msg: 根据身高排序（升序）
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回结构体数组指针
 */
s_person *sort_by_height(s_person arr[], int len);

/**
 * @name: sort_by_total_score
 * @msg: 根据总分排序（升序）
 * @param: 1.结构体数组指针 2.结构体数组长度
 * @return: 返回结构体数组指针
 */
s_person *sort_by_total_scores(s_person arr[], int len);

/**
 * @name: sum_scores
 * @msg: 计算总分
 * @param: 要计算总分的结构体
 * @return: 返回总分
 */
float sum_scores(s_person person);

// << END DECLARE FUNC

// >> DEFINE FUNC
float sum_scores(s_person person){
    float sum = 0.0;
    return sum = person.scores.chinese + person.scores.english + person.scores.mathematics;
}

int set_arr(s_person arr[], int len){
    for(int i = 0; i<len; i++){
        printf("%d. Input Name, Height, Scores(Chinese, English, Mathematics): \n", i+1);
        scanf("%s%d%f%f%f", arr[i].name, &arr[i].height,   \
            &arr[i].scores.chinese, &arr[i].scores.english, &arr[i].scores.mathematics
        );
        while(getchar() != '\n'){
            continue;
        }
        
        // 输入内容错误判断
        if(strlen(arr[i].name) > 14 || arr[i].height > 200 || arr[i].height < 0  \
            || arr[i].scores.chinese < 0 || arr[i].scores.chinese > 100          \
            || arr[i].scores.english < 0 || arr[i].scores.english > 100          \
            || arr[i].scores.mathematics < 0 || arr[i].scores.mathematics > 100  \
        ){
            printf("\nIncorrect Input!\n\n");
            return FALSE_S;
        }
    }

    printf("\nInput Done!\n\n");

    return TRUE_S;
}

s_person *get_arr(s_person arr[], int len){
    for(int i = 0; i<len; i++){
        printf("----[%d]----------------\n", i+1);
        printf("Name: %s\tHeight: %d\nScores: \nChinese: %.1f\tEnglish: %.1f\tMathematics: %.1f\n", \
            arr[i].name, arr[i].height, \
            arr[i].scores.chinese, arr[i].scores.english, arr[i].scores.mathematics
        );
        printf("\n");
    }

    printf("\nOutput Done!\n\n");

    return arr;
}

s_person max_height(s_person arr[], int len){
    int max_index = 0;
    for(int i = 1; i<len; i++){
        if(arr[i].height > arr[max_index].height){
            max_index = i;
        }
    }

    printf("--The Tallest One--------------\n");
    printf("Name: %s\tHeight: %d\nScores: \nChinese: %.1f\tEnglish: %.1f\tMathematics: %.1f\n", \
        arr[max_index].name, arr[max_index].height, \
        arr[max_index].scores.chinese, arr[max_index].scores.english, arr[max_index].scores.mathematics
    );
    printf("\n");

    return arr[max_index];
}

s_person max_total_scores(s_person arr[], int len){
    int max_index = 0;
    for(int i = 1; i<len; i++){
        if(sum_scores(arr[i]) > sum_scores(arr[max_index])){
            max_index = i;
        }
    }

    printf("--The Greatest One--------------\n");
    printf("Name: %s\tHeight: %d\nScores: \nChinese: %.1f\tEnglish: %.1f\tMathematics: %.1f\n", \
        arr[max_index].name, arr[max_index].height, \
        arr[max_index].scores.chinese, arr[max_index].scores.english, arr[max_index].scores.mathematics
    );
    printf("\n");

    return arr[max_index];
}

s_person *sort_by_height(s_person arr[], int len){
    for(int i = 0; i<len - 1; i++){
        for(int j=0; j<len - 1 -i; j++){
            if(arr[j].height > arr[j+1].height){
                s_person t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }

    return arr;
}

s_person *sort_by_total_scores(s_person arr[], int len){
    for(int i = 0; i<len - 1; i++){
        for(int j=0; j<len - 1 -i; j++){
            if(sum_scores(arr[j]) > sum_scores(arr[j+1])){
                s_person t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }

    return arr;
}

// << END DEFINE FUNC 

int main(int argc, char const *argv[])
{
    s_person *arr_per = (s_person *)malloc(sizeof(s_person)*N);
    if(arr_per == NULL){
        printf("Allocate Failed!\n");
        return 0;
    }
    int operator = 0,
        is_set_flag = FALSE_S;

    while (1){
        START:

        printf("+----------MENU---------+\n");
        printf("|  1: Input             |\n");
        printf("|  2: Output            |\n");
        printf("|  3: CalHmax           |\n");
        printf("|  4: CalSmax           |\n");
        printf("|  5: SortH             |\n");
        printf("|  6: SortS             |\n");
        printf("| -1: exit              |\n");
        printf("+-----------------------+\n");

        printf("Input one operator: ");
        scanf("%d",&operator);
        while (getchar() != '\n'){
            continue;
        }
        printf("\n");

        if(operator == 1){
            is_set_flag = set_arr(arr_per, N);
            if(!is_set_flag){
                goto START;
            }
        }else if(!is_set_flag  && operator >1 && operator <7){
            printf("Input Array First!\n\n");
            goto START;
        }else{
            switch (operator)
            {
                case 2:
                    get_arr(arr_per, N);
                    break;

                case 3:
                    max_height(arr_per, N);
                    break;

                case 4:
                    max_total_scores(arr_per, N);
                    break;

                case 5:
                    printf("---Sort By Height----------\n");
                    get_arr(sort_by_height(arr_per, N), N);
                    printf("\n");
                    break;

                case 6:
                    printf("---Sort By Total Scores-----\n");
                    get_arr(sort_by_total_scores(arr_per, N), N);
                    printf("\n");
                    break;

                case -1:
                    printf("Quit!\n");
                    free(arr_per);
                    arr_per = NULL;
                    return 0;
                
                default:
                    printf("Incorrect Operator, Try Again!\n\n");
                    break;
            }
        }     
    }

    return 0;
}
