#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N (6)

enum status {
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

typedef int node_weight;
typedef struct tree {
    node_weight weight;
    struct tree * parent,
                * l_child,
                * r_child;
}tree_node, *huffman_tree;

/**
 * @name:init_tree_node 
 * @msg:输入构成哈夫曼树的初始结点,最多数量为size 
 * @param: 
 * 1. tree_node *p_tnode[] 结点指针数组的首地址
 * 2. int size 数组的大小
 * @return: 函数调用的结果 status
 */
extern int init_tree_node(tree_node *p_tnode[], int size);

/**
 * @name:find_leaves 
 * @msg:找出结点中权重的最小值和次小值 
 * @param: 
 * 1. tree_node *p_tnode[] 结点指针数组的首地址
 * 2. int size 数组的大小
 * 3. int *min 传出参数: 数组中的最小值结点下标
 * 4. int *next_min 传出参数: 数组中的次小值结点下标
 * @return:函数调用的结果 status 
 */
extern int find_leaves(tree_node *p_tnode[], int size, int *min, int *next_min);

/**
 * @name: create_huffman_tree 
 * @msg: 构造哈夫曼树
 * @param: 
 * 1. tree_node *p_tnode[] 结点指针数组的首地址
 * 2. int size 数组的大小
 * 3. huffman_tree *p_htree 传出参数: 哈夫曼树
 * @return: 函数调用的结果 status
 */
extern int create_huffman_tree(tree_node *p_tnode[],int size, huffman_tree *p_htree);

/**
 * @name: pre_order
 * @msg: 先序遍历哈夫曼树
 * @param: huffman_tree p_htree 哈夫曼树的指针
 * @return: 函数是否调用成功 status
 */
extern int pre_order(huffman_tree p_htree);

/**
 * @name: in_order
 * @msg: 中序遍历哈夫曼树
 * @param: huffman_tree p_htree 哈夫曼树的指针
 * @return: 函数是否调用成功 status
 */
extern int in_order(huffman_tree p_htree);

/**
 * @name: post_order
 * @msg: 后序遍历哈夫曼树
 * @param: huffman_tree p_htree 哈夫曼树的指针
 * @return: 函数是否调用成功 status
 */
extern int post_order(huffman_tree p_htree);

#endif