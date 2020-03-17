/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-10 18:29:37
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-11 09:36:16
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_list.h"

// 创建
b_list * create_list(){
    b_list *p_list = NULL;
    p_list = (b_list *)malloc(sizeof(b_list));
    if(p_list == NULL){
        printf("ERROR: Memory is full!\n");
        return p_list;
    }

    // init list
    memset(p_list, '\0', sizeof(p_list->books));
    p_list->count = 0;

    return p_list;
}

// 判空
int is_empty(b_list *list){
    return list == NULL ? ERROR_S : list->count == 0 ? TRUE_S : FLASE_S;
}

// 判满
int is_full(b_list *list){
    return list == NULL ? ERROR_S : list->count == SIZE ? TRUE_S : FLASE_S;
}

// 打印
void get_list(b_list *list){
    if(list == NULL){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ;
    }

    printf("********Book List********\r\n");
    for(int i = 0; i < list->count; i++){
        printf("%d: %s ", i+1, list->books[i]);
    }
    printf("\r\n");

    return ;
}

// 销毁
int destory_list(b_list *list){
    if(list == NULL){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ERROR_S;
    }

    free(list);
    list = NULL;

    return TRUE_S;
}

// 插入数据
int insert_data(b_list *list, int pos, data_type new_data){
    if(list == NULL || pos < 0 || pos > list->count || strlen(new_data) > NAME_SIZE){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ERROR_S;
    }
    if(is_full(list) == TRUE_S){
        printf("ERROR: LIST IS FULL\r\n");
        return FLASE_S;
    }

    for(int i = list->count - 1; i >= pos; i--){
        strcpy(list->books[i+1], list->books[i]);
    }
    strcpy(list->books[pos], new_data);
    list->count++;

    return TRUE_S;
}

// 删除数据
int delete_data(b_list *list, int pos, data_type deleted_data){
    if(list == NULL  || pos < 0 || pos > list->count || strlen(deleted_data) > NAME_SIZE){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ERROR_S;
    }
    if(is_empty(list) == TRUE_S){
        printf("ERROR: LIST IS EMPTY\r\n");
        return FLASE_S;
    }

    strcpy(deleted_data, list->books[pos]);
    for(int i = pos; i < list->count-1; i++){
        strcpy(list->books[i], list->books[i+1]);
    }
    list->count--;

    return TRUE_S;
}

// 修改数据
int update_data(b_list *list, data_type old_data, data_type new_data){
    if(list == NULL  || strlen(new_data) > NAME_SIZE || strlen(old_data) > NAME_SIZE){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ERROR_S;
    }

    for(int i = 0; i < list->count; i++){
        if(strcmp(old_data, list->books[i]) == 0){
            strcpy(list->books[i], new_data);
            printf("%s UPDATED\r\n", old_data);
            return TRUE_S;
        }
    }

    printf("NOT FOUND\r\n");
    return FLASE_S;
}

// 查找数据
int search_data(b_list *list, data_type search_data){
    if(list == NULL || strlen(search_data) > NAME_SIZE){
        printf("ERROR: INVALID PARAMETER\r\n");
        return ERROR_S;
    }

    for(int i = 0; i < list->count; i++){
        if(strcmp(search_data, list->books[i]) == 0){
            printf("FOUND %s\n", search_data);
            return TRUE_S;
        }
    }

    printf("NOT FOUND\r\n");
    return FLASE_S;
}