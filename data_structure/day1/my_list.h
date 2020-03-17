#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#define SIZE 5
#define NAME_SIZE 20

enum e_status {
    ERROR_S = -1,
    FLASE_S,
    TRUE_S
};

typedef char book[NAME_SIZE];
typedef book data_type;

typedef struct {
    data_type books[SIZE];
    int count;
}b_list;

/**
 * @name: create_list
 * @msg: 生成顺序表
 * @param: 空
 * @return: 顺序表的首地址
 */
b_list * create_list();

/**
 * @name: is_empty
 * @msg: 判断顺序表是否为空
 * @param: b_list *list 顺序表的首地址
 * @return: 操作状态 e_status
 */
int is_empty(b_list *list);

/**
 * @name: is_full
 * @msg: 判断顺序表是否为满
 * @param: b_list *list 顺序表的首地址
 * @return: 操作状态 e_status
 */
int is_full(b_list *list);

/**
 * @name: destory_list
 * @msg: 销毁顺序表
 * @param: b_list *list 顺序表的首地址
 * @return: 操作状态 e_status
 */
int destory_list(b_list *list);

/**
 * @name: get_list
 * @msg: 打印顺序表
 * @param: b_list *list 顺序表的首地址
 * @return: 空
 */
void get_list(b_list *list);

/**
 * @name: insert_data
 * @msg: 在顺序表指定位置插入新数据
 * @param: 1.b_list *list 顺序表的首地址 
 *         2.int pos 插入位置 
 *         3.data_type new_data 要插入的数据
 * @return: 操作状态 e_status
 */
int insert_data(b_list *list, int pos, data_type new_data);

/**
 * @name: delete_data
 * @msg: 删除指定位置的数据
 * @param: 1.b_list *list 顺序表的首地址 
 *         2.int pos 删除数据的位置 
 *         3.data_type new_data 要插入的数据
 * @return: 操作状态 e_status
 */
int delete_data(b_list *list, int pos, data_type deleted_data);

/**
 * @name: update_data
 * @msg: 修改指定的数据
 * @param: 1.b_list *list 顺序表的首地址 
 *         2.data_type old_data 修改前的数据
 *         3.data_type new_data 修改后的数据
 * @return: 操作状态 e_status
 */
int update_data(b_list *list, data_type old_data, data_type new_data);

/**
 * @name: search_data
 * @msg: 查找指定的数据
 * @param: 1.b_list *list 顺序表的首地址
 *         2.data_type search_data 要查找的数据
 * @return: 找到返回数据下标， 失败返回 e_status
 */
int search_data(b_list *list, data_type search_data);

#endif