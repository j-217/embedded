#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status {
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

typedef int data_type;

typedef struct tree{
    data_type data;
    struct tree * l_child,
                  * r_child;
}tree_node, *b_tree;

/**
 * @name: init_b_tree
 * @msg: 先序创建普通二叉树
 * @param: b_tree *p_btree 二叉树的指针的地址
 * @return: 函数是否调用成功 status
 */
extern int init_b_tree(b_tree *p_btree);

/**
 * @name: set_item
 * @msg: 创建有序二叉树时插入结点的方法
 * @param: 1. b_tree p_btree 二叉树的指针
 *         2. data_type item 要插入的元素
 * @return: 函数是否调用成功 status
 */
extern int set_item(b_tree p_btree, data_type item);

/**
 * @name: init_order_b_tree
 * @msg: 创建有序二叉树
 * @param: b_tree *p_btree 二叉树的指针的地址
 * @return: 函数是否调用成功 status
 */
extern int init_order_b_tree(b_tree *p_btree);

/**
 * @name: pre_order
 * @msg: 先序遍历二叉树
 * @param: b_tree p_btree 二叉树的指针
 * @return: 函数是否调用成功 status
 */
extern int pre_order(b_tree p_btree);

/**
 * @name: in_order
 * @msg: 中序遍历二叉树
 * @param: b_tree p_btree 二叉树的指针
 * @return: 函数是否调用成功 status
 */
extern int in_order(b_tree p_btree);

/**
 * @name: post_order
 * @msg: 后序遍历二叉树
 * @param: b_tree p_btree 二叉树的指针
 * @return: 函数是否调用成功 status
 */
extern int post_order(b_tree p_btree);

/**
 * @name: destory_b_tree
 * @msg: 销毁二叉树
 * @param: b_tree *p_btree 二叉树的指针的地址
 * @return: 函数是否调用成功 status
 */
extern int destory_b_tree(b_tree *p_btree);

/**
 * @name: level_order
 * @msg: 二叉树的层次遍历
 * @param: b_tree p_btree 二叉树的指针的地址
 * @return: 函数是否调用成功 status
 */
int level_order(b_tree p_btree);

#endif