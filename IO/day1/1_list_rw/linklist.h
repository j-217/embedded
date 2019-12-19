#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum opt{
    TAIL = -1,
    HEAD
};

enum status{
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

typedef int data_type;

typedef struct link{
    data_type data;
    struct link * next;
}linknode;

/**
 * @name: create_link
 * @msg: 创建链表
 * @param: void
 * @return: 返回链表首地址 
 */
linknode * create_link();

/**
 * @name: is_empty
 * @msg: 链表是否为空
 * @param: linknode *p_head 链表首地址
 * @return: 返回函数调用状态
 */
int is_empty(linknode *p_head);

/**
 * @name: insert_link
 * @msg: 在指定位置后插入数据(-1: 尾结点, 0: 头结点, 1: 首结点)
 * @param: 1. linknode *p_head 链表首地址
 *         2. int pos 插入位置
 *         3. data_type new_data 要插入的数据
 * @return: 返回调用后的状态status
 */
int insert_link(linknode *p_head, int pos, data_type new_data);

/**
 * @name: get_link
 * @msg: 打印链表
 * @param: linknode *p_head 链表首地址
 * @return: void
 */
void get_link(linknode *p_head);

/**
 * @name: delete_link
 * @msg: 在指定位置删除数据, 通过返回参数返回被删除数据 (-1: 尾结点, 0: 头结点, 1: 首结点)
 * @param: 1. linknode *p_head 链表首地址
 *         2. int pos 删除数据的位置
 *         3. data_type *d_data 返回参数被删除的数据
 * @return: 返回调用后的状态status
 */
int delete_data(linknode *p_head, int pos, data_type *d_data);

/**
 * @name: destory_link
 * @msg: 销毁链表
 * @param: linknode **p_head 链表首地址的地址
 * @return: 返回调用后的状态status
 */
int destory_link(linknode **p_head);

/**
 * @name: reverse_link
 * @msg: 逆序链表
 * @param: linknode **p_head 链表首地址的地址
 * @return: 返回调用后的状态status
 */
int reverse_link(linknode **p_head);

/**
 * @name: save_linklist
 * @msg: 将链表的数据依次读取并存入指定文件内
 * @param: 1. linknode *p_head 链表首地址
 *         2. const char *pathname 文件名称
 * @return: 返回调用后的状态 status
 */
int save_linklist(linknode *p_head, const char *pathname);

/**
 * @name: load_linklist
 * @msg: 从指定文件读取数据按照头插法存入链表
 * @param: 1. linknode *p_head 链表首地址
 *         2. const char *pathname 文件名称
 * @return: 返回调用后的状态 status
 */
int load_linklist(linknode *p_head, const char *pathname);

#endif