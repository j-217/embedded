/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-11 18:24:55
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-12 19:51:36
 */
#include "linklist.h"

// 判空
int is_empty(linknode *p_head){
    return p_head == NULL ? ERROR_S : p_head->next == NULL ? TRUE_S : FALSE_S;
}

// 创建链表头结点
linknode * create_link(){
    linknode * p_head = NULL;
    if((p_head = (linknode *)malloc(sizeof(linknode))) == NULL){
        printf("FAILED: ALLOCATE FAILED\n");
        return p_head;
    }

    memset(&p_head->data, 0, sizeof(p_head->data));
    p_head->next = NULL;

    return p_head;
}

// 链表插入数据
int insert_link(linknode *p_head, int pos, data_type new_data){
    if(p_head == NULL || pos < -1){
        printf("ERROR: INVAILD PARAMETER\n");
        return ERROR_S;
    }
    
    linknode *p_move = p_head;

    linknode *new_node = (linknode *)malloc(sizeof(linknode));
    if(new_node == NULL){
        return ERROR_S;
    }
    new_node->data = new_data;
    new_node->next = NULL;

    switch (pos){
        // case HEAD:
        //     new_node->next = p_head->next;
        //     p_head->next = new_node;
        //     break;
        case TAIL:
            while(p_move->next != NULL){
                p_move = p_move->next;
            }
            p_move->next = new_node;
            break;
        default:
            while(pos > 0){
                if(p_move->next == NULL){
                    printf("FAILED: INSERT OVERFLOW\n");
                    // 插入失败释放新节点
                    free(new_node);
                    new_node = NULL;

                    return FALSE_S;
                }
                p_move = p_move->next;
                pos--;
            }
            new_node->next = p_move->next;
            p_move->next = new_node;
            break;
    }

    return TRUE_S;
}

// 打印链表
void get_link(linknode *p_head){
    if(p_head == NULL){
        printf("FAILED: INVALID PARAMETER\n");
        return ;
    }
    linknode *p_move = p_head->next;
    while (p_move->next != NULL)
    {
        printf("%d ", p_move->data);
        p_move = p_move->next;
    }
    printf("%d %p\n", p_move->data, p_move->next);

    return ;
}

// 删除链表数据
int delete_data(linknode *p_head, int pos, data_type *d_data){
    // pos不能指向头结点
    if(p_head == NULL || pos < -1 || pos == 0){
        printf("ERROR: INVAILD PARAMETER\n");
        return ERROR_S;
    }
    if(is_empty(p_head) == TRUE_S){
        printf("FAILED: VOID LINKLIST\n");
        return FALSE_S;
    }

    linknode *p_del = p_head, *p_prev = p_head;
    linknode *p_tmp = p_del;

    switch(pos){
        case TAIL:
            while(p_del->next != NULL){
                p_prev = p_del;
                p_del = p_del->next;
            }
            p_tmp = p_del;
            *d_data = p_del->data;
            p_prev->next = NULL;

            break;
        default:
             while(pos > 0){
                if(p_del->next == NULL){
                    printf("FAILED: DELETE OVERFLOW\n");
                    return FALSE_S;
                }
                p_prev = p_del;
                p_del = p_del->next;
                pos--;
            }
            p_tmp = p_del;
            *d_data = p_del->data;
            
            if(p_del->next == NULL){
                // 删除尾节点
                p_prev->next = NULL;
            }else{
                // 删除中间节点  
                p_prev->next = p_del->next;
            }

            break;
    }

    free(p_tmp);
    p_tmp = NULL;

    return TRUE_S;
}

// 销毁链表
int destory_link(linknode **p_head){
    if(*p_head == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    // 链表仅有头结点
    if(is_empty(*p_head) == TRUE_S){
        free(*p_head);
        *p_head = NULL;

        return TRUE_S;
    }

    linknode *p_del = (*p_head)->next, *p_next = (*p_head)->next;
    while(p_next != NULL){
        p_del = p_next;
        p_next = p_next->next;

        free(p_del);
        p_del = NULL;
    }

    free(*p_head);
    *p_head = NULL;

    return TRUE_S;
}

// 逆序链表
int reverse_link(linknode **p_head){
    // 将原链表头结点置空，原链表结点数据使用头插法重新插入链表，释放原结点
    if(*(p_head) == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    // 链表仅有头结点
    if(is_empty(*p_head) == TRUE_S){
        printf("No need to reverse\n");
        return TRUE_S;
    }

    // 遍历位置, 当前位置
    linknode *p_next = (*p_head)->next, 
             *p_current = (*p_head)->next;
    
    (*p_head)->next = NULL;
    while(p_next != NULL){
        // p_current = p_next;
        // insert_link(*p_head, HEAD, p_current->data);
        // // 释放原链表结点
        // free(p_current);
        // p_current = NULL;
        // p_next = p_next->next;
        p_current = p_next;
        p_next = p_next->next;
        p_current->next = (*p_head)->next;
        (*p_head)->next = p_current;
    }

    return TRUE_S;
}

// 按升序插入
int insert_in_order(linknode *p_head, data_type new_data){
    if(p_head == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    linknode *p_move = p_head,
             *p_prev = p_head;

    linknode *new_node = (linknode *)malloc(sizeof(linknode));
    new_node->data = new_data;
    new_node->next = NULL;

    // 头结点数据为0, 先判断当前是否在头结点, 否则插入负数时异常, 或者在p_move初始化时指向p_head->next
    while(p_move == p_head || (p_move != NULL && new_data >= p_move->data)){
        p_prev = p_move;
        p_move = p_move->next;
    }
    new_node->next = p_prev->next;
    p_prev->next = new_node;

    return TRUE_S;
}

// 合并有序链表
linknode *merge_link(linknode *p_head_1, linknode *p_head_2){
    if(p_head_1 == NULL || p_head_2 == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return NULL;
    }

    linknode *l_1 = p_head_1->next,
             *l_2 = p_head_2->next,
             *new_link = (linknode *)malloc(sizeof(linknode));
    if(new_link == NULL){
        printf("ERROR: MEMORY IS FULL\n");
        return NULL;
    }
    new_link->data = 0;
    new_link->next = NULL;

    linknode *new_move = new_link;

    while(1){
        if(l_1 == NULL){
            new_move->next = l_2;
            break;
        }
        if(l_2 == NULL){
            new_move->next = l_1;
            break;
        }
        if(l_1->data < l_2->data){
            new_move->next = l_1;
            l_1 = l_1->next;
        }else{
            new_move->next = l_2;
            l_2 = l_2->next;
        }
        new_move = new_move->next;
    }

    return new_link;
}