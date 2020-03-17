/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-16 20:18:11
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-17 08:43:33
 */
#include "huffman_tree.h"

// 初始化哈夫曼树结点数组
int init_tree_node(tree_node *p_tnode[], int size){
    node_weight wt = 0;
    for(int i = 0; i<size; i++){
        printf("INPUT A WEIGHT: ");
        scanf("%d", &wt);
        while(getchar() != '\n'){
            continue;
        }

        tree_node *new_node = (tree_node *)malloc(sizeof(tree_node));
        if(new_node == NULL){
            perror("MALLOC");
            return ERROR_S;
        }
        new_node->weight = wt;
        new_node->parent = NULL;
        new_node->l_child = NULL;
        new_node->r_child = NULL;

        p_tnode[i] = new_node;
    }

    return TRUE_S;
}

// 寻找最小权重值和次小权重值的结点
int find_leaves(tree_node *p_tnode[], int size, int *min, int *next_min){
    // 定义最小值和次小值的下标, 假设最小值是第一个父结点为空的结点, 次小值是第二个父结点为空的结点
    int min_flag = 2;

    for(int i = 0; i<size && p_tnode[i] != NULL; i++){
        if(p_tnode[i]->parent == NULL && min_flag == 2){
            *min = i;
            min_flag--;
            continue;
        }
        if(p_tnode[i]->parent == NULL && min_flag == 1){
            *next_min = i;
            min_flag--;
            break;
        }
    }

    // 只有一个父结点为空时返回失败信息
    if(min_flag == 1){
        printf("FAILED: THERE IS NO LEAVES\n");
        return FALSE_S;
    }

    // 假设值如有错误, 交换
    if(p_tnode[*min]->weight > p_tnode[*next_min]->weight){
        *min = *min + *next_min;
        *next_min = *min - *next_min;
        *min = *min - *next_min;
    }

    // 遍历更新最小值和次小值
    for(int i = 0; i<size && p_tnode[i] != NULL; i++){
        if(i == *min || i == *next_min){
            continue;
        }
        if(p_tnode[i]->weight < p_tnode[*next_min]->weight && p_tnode[i]->parent == NULL){
            if(p_tnode[i]->weight < p_tnode[*min]->weight){
                *next_min = *min;
                *min = i;
            }else{
                *next_min = i;
            }
        }
    }

    return TRUE_S;
}

// 创建哈夫曼树
int create_huffman_tree(tree_node *p_tnode[], int size, huffman_tree *p_htree){
    // 生成哈夫曼树, 每次寻找最小值和次小值的结点, 求和生成新的根结点, 关联新结点和最小值次小值结点的关系, 将新结点添加到数组最后, 重新计算包含新结点在内的所有结点(排除有父结点的结点)
    int i_min = -1,
        i_next_min = -1;
    
    // 从(size+1)/2 位开始遍历, 前面为初始化结点数组
    for(int i = (size+1)/2; i<size; i++){
        if(find_leaves(p_tnode, size, &i_min, &i_next_min) == FALSE_S){
            break;
        }
        tree_node *new_node = (tree_node *)malloc(sizeof(tree_node));
        if(new_node == NULL){
            perror("MALLOC");
            return ERROR_S;
        }

        // 初始化新结点
        new_node->weight = p_tnode[i_min]->weight + p_tnode[i_next_min]->weight;
        new_node->l_child = p_tnode[i_min];
        new_node->r_child = p_tnode[i_next_min];
        // 最小值和次小值作为新结点的左右子树
        p_tnode[i_min]->parent = new_node;
        p_tnode[i_next_min]->parent = new_node;

        p_tnode[i] = new_node;
    }

    for(int i=0; i<size; i++){
        if(p_tnode[i]->parent == NULL){
            *p_htree = p_tnode[i];
        }
    }

    return TRUE_S;
}

// 前序遍历
int pre_order(huffman_tree p_htree){
    if(p_htree != NULL){
        printf("%d ", p_htree->weight);
        pre_order(p_htree->l_child);
        pre_order(p_htree->r_child);
    }

    return TRUE_S;
}

// 中序遍历
int in_order(huffman_tree p_htree){
    if(p_htree != NULL){
        in_order(p_htree->l_child);
        printf("%d ", p_htree->weight); 
        in_order(p_htree->r_child);
    }

    return TRUE_S; 
}

// 后序遍历
int post_order(huffman_tree p_htree){
    if(p_htree != NULL){
        post_order(p_htree->l_child);
        post_order(p_htree->r_child);
        printf("%d ", p_htree->weight); 
    }

    return TRUE_S;  
}