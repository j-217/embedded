#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

enum status{
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

typedef int data_type;
typedef struct {
    data_type data[SIZE];
    int top;
}stack;

/**
 * @name: init_stack
 * @msg: 初始化栈 
 * @param: void
 * @return: 栈的首地址
 */
stack * init_stack();

/**
 * @name: is_empty
 * @msg: 判断栈是否为空 
 * @param: 栈的首地址 
 * @return: status (-1: 错误 0:否 1:是)
 */
int is_empty(stack *s);

/**
 * @name: is_full
 * @msg: 判断栈是否为满 
 * @param: stack *s 栈的首地址 
 * @return: status (-1: 错误 0:否 1:是)
 */
int is_full(stack *s);

/**
 * @name: push_stack
 * @msg: 入栈 
 * @param: 1. stack *s 栈的首地址
 *         2. data_type in_item 输入元素
 * @return: status (-1: 错误 0:失败 1:成功)
 */
int push_stack(stack *s, data_type in_item);

/**
 * @name: pop_stack 
 * @msg: 出栈 
 * @param: 1. stack *s 栈的首地址
 *         2. data_type *out_item 输出元素的首地址
 * @return: status (-1: 错误 0:失败 1:成功)
 */
int pop_stack(stack *s, data_type *out_item);

/**
 * @name: destory_stack 
 * @msg: 销毁栈
 * @param: stack *s 栈的首地址
 * @return: status (-1: 错误 0:失败 1:成功)
 */
int destory_stack(stack **p_ps);

#endif