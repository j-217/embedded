/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-10 18:38:25
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-10 23:29:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_list.h"

int main(int argc, char const *argv[]){
    int res = 0;
    // 创建顺序表
    printf("--------create---------\n\n");
    b_list * p_list = create_list();
    if(p_list == NULL){
        return 1;
    }

    // empty or full or error
    res = is_empty(p_list);
    printf("IS_EMPTY: %d\n", res);

    res = is_full(p_list);
    printf("IS_FULL: %d\n", res);

    res = is_empty(NULL);
    printf("IS_EMPTY: %d\n", res);

    // 空列表删除
    delete_data(p_list, 0, "testing");
    printf("\n---------end-----------\n");    

    // 插入数据
    printf("--------insert---------\n\n");
    data_type b1 = "first";
    data_type b2 = "second";
    data_type b3 = "third";
    data_type b4 = "fourth";
    data_type b5 = "fifth";
    insert_data(p_list, 0, b5);
    insert_data(p_list, 0, b4);
    insert_data(p_list, 0, b3);
    insert_data(p_list, 0, b2);
    insert_data(p_list, 0, b1);

    // 满顺序表添加
    insert_data(p_list, 0, "sixth");

    res = is_full(p_list);
    printf("IS_FULL: %d\n", res);

    res = is_empty(p_list);
    printf("IS_EMPTY: %d\n", res);
    printf("\n---------end-----------\n");

    // 打印数据
    printf("--------output---------\n\n");
    get_list(p_list);

    // 错误
    get_list(NULL);
    printf("\n---------end-----------\n");

    // 删除数据
    printf("--------delete---------\n\n");
    data_type del_data = {'\0'};
    // 成功
    res = delete_data(p_list, 1, del_data);
    printf("DELETE: %d\n", res);
    printf("DELETE DATA: %s\n", del_data);
    get_list(p_list);

    // 错误
    res = delete_data(p_list, 10, del_data);
    printf("DELETE: %d\n", res);
    get_list(p_list);
    printf("\n---------end-----------\n");

    // 修改数据
    printf("--------update---------\n\n");
    // 成功
    data_type b_new = "new one";
    res = update_data(p_list, b3, b_new);
    printf("UPDATE: %d\n", res);
    get_list(p_list);

    // 失败
    data_type b_old = "nothing";
    res = update_data(p_list, b_old, b_new);
    printf("UPDATE: %d\n", res);
    get_list(p_list);

    // 错误
    res = update_data(p_list, b_old, "aaaaaaaaaaaaabbbbbbbbbbbbbbbbbcccccccccccccddddddddddddddddcccccc");
    printf("UPDATE: %d\n", res);
    printf("\n---------end-----------\n");

    // 查找数据
    // 成功
    printf("--------search---------\n\n");
    res = search_data(p_list, "fifth");
    printf("SEARCH: %d\n", res);

    // 失败
    res = search_data(p_list, "nothing");
    printf("SEARCH: %d\n", res);
    printf("\n---------end-----------\n");

    // 销毁顺序表
    destory_list(p_list);

    return 0;
}
