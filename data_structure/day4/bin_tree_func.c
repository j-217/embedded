/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-13 18:04:49
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-16 13:51:30
 */
#include "bin_tree.h"
#include "queue.h"

// 先序创建普通二叉树
int init_b_tree(b_tree *p_btree){
    printf("INPUT A NUMBER(-1 EXIT): ");
    data_type item = 0;
    scanf("%d", &item);
    while(getchar() != '\n')
        continue;

    // 循环退出条件
    if(item == -1){
        *p_btree = NULL;
    }else{
        // 申请空间, 放置新元素
        *p_btree = (b_tree)malloc(sizeof(tree_node));
        if(*p_btree == NULL){
            printf("FAILD: MEMORY IS FULL\n");
            return FALSE_S;
        }

        // 先序递归生成二叉树
        (*p_btree)->data = item;
        init_b_tree(&(*p_btree)->l_child);
        init_b_tree(&(*p_btree)->r_child);
    }

    return TRUE_S;
}

// 创建有序二叉树时插入结点的方法
int set_item(b_tree p_btree, data_type item){
    if(item < p_btree->data){
        if(p_btree->l_child == NULL){
            // 左子结点不存在， 生成新左子结点, 存入数据
            b_tree p_new = (b_tree)malloc(sizeof(tree_node));
            p_new->data = item;
            p_new->l_child = NULL;
            p_new->r_child = NULL;

            p_btree->l_child = p_new;
            
            return TRUE_S;
        }else{
            // 左子结点存在， 递归继续判断
            set_item(p_btree->l_child, item);
        }
    }else{
        if(p_btree->r_child == NULL){
            // 右子结点不存在，生成新右子结点, 存入数据
            b_tree p_new = (b_tree)malloc(sizeof(tree_node));
            p_new->data = item;
            p_new->l_child = NULL;
            p_new->r_child = NULL;

            p_btree->r_child = p_new;
            
            return TRUE_S;
        }else{
            // 右子结点存在， 递归继续判断
            set_item(p_btree->r_child, item);
        }
    }

    return TRUE_S;
}

// 创建有序二叉树
int init_order_b_tree(b_tree *p_btree){
    // 先创建有序二叉树的根，根据根的元素进行比较放置后续元素, 每次从根结点进行判断
    data_type item = 0;
    printf("INPUT ROOT: ");
    scanf("%d", &item);
    while(getchar() != '\n')
        continue;

    *p_btree = (b_tree)malloc(sizeof(tree_node));
    if(*p_btree == NULL){
        printf("FAILED: MEMORY IS FULL\n");
        return FALSE_S;
    }
    (*p_btree)->data = item;
    (*p_btree)->l_child = NULL;
    (*p_btree)->r_child = NULL;

    // 循环输入新结点元素， 调用插入数据的方法
    while (1){
        printf("INPUT A NUMBER(-1 EXIT): ");
        scanf("%d", &item);
        while(getchar() != '\n')
            continue;

        // 循环退出条件
        if(item == -1){
            break;
        }

        set_item(*p_btree, item);
    }
    
    return TRUE_S;
}

// 先序遍历二叉树
int pre_order(b_tree p_btree){
    if(p_btree != NULL){
        printf("%d ", p_btree->data);
        pre_order(p_btree->l_child);
        pre_order(p_btree->r_child);
    }

    return TRUE_S;
}

// 中序遍历二叉树
int in_order(b_tree p_btree){
    if(p_btree != NULL){
        in_order(p_btree->l_child);
        printf("%d ", p_btree->data);
        in_order(p_btree->r_child);
    }

    return TRUE_S;
}

// 后序遍历二叉树
int post_order(b_tree p_btree){
    if(p_btree != NULL){
        post_order(p_btree->l_child);
        post_order(p_btree->r_child);
        printf("%d ", p_btree->data);
    }

    return TRUE_S;
}

// 销毁二叉树
int destory_b_tree(b_tree *p_btree){
    // 递归退出条件
    if(*p_btree == NULL){
        return TRUE_S;
    }

    // 先递归调用, 如果将递归放在判断叶子结点后， 调用结束无法再次判断当前是否变成叶子结点
    destory_b_tree(&(*p_btree)->l_child);
    destory_b_tree(&(*p_btree)->r_child);

    // 再判断是否是叶子结点
    if(((*p_btree)->l_child == NULL) && ((*p_btree)->r_child == NULL)){
        free(*p_btree);
        *p_btree = NULL;

        printf("TREE NODE HAS BEEN FREED\n");
        return TRUE_S;
    }

    return TRUE_S;
}

// 深度遍历
int level_order(b_tree p_btree){
    queue *p_q = NULL;
    if(init_queue(&p_q) == FALSE_S){
        return FALSE_S;
    }

    tree_node t_node;

    enqueue(p_q, *p_btree);
    while(is_empty(p_q) != TRUE_S){
        dequeue(p_q, &t_node);
        printf("%d ", t_node.data);
        if(t_node.l_child != NULL){
            enqueue(p_q, *(t_node.l_child));
        }
        if(t_node.r_child != NULL){
            enqueue(p_q, *(t_node.r_child));
        }
    }

    destory_queue(&p_q);

    return TRUE_S;
}