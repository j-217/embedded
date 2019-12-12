/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-12 15:52:49
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-12 18:23:19
 */
#include "stack.h"

// 初始化栈
stack * init_stack(){
    stack *p_s = (stack *)malloc(sizeof(stack));
    if(p_s == NULL){
        printf("FAILED: MEMORY IS FULL\n");
        return p_s;
    }

    memset(p_s, 0, sizeof(stack));
    p_s->top = -1;

    return p_s;
}

// 判空
int is_empty(stack *s){
    return s == NULL ? ERROR_S : s->top == -1 ? TRUE_S : FALSE_S;
}

// 判满
int is_full(stack *s){
    return s == NULL ? ERROR_S : s->top == SIZE - 1 ? TRUE_S : FALSE_S;
}

// 入栈
int push_stack(stack *s, data_type in_item){
    if(s == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }
    if(is_full(s) == TRUE_S){
        printf("FAILED: STACK IS FULL\n");
        return FALSE_S;
    }

    s->data[++s->top] = in_item;
    printf("%d pushed in\n", in_item);

    return TRUE_S;
}

// 出栈
int pop_stack(stack *s, data_type *out_item){
    if(s == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }
    if(is_empty(s) == TRUE_S){
        printf("FAILED: STACK IS EMPTY\n");
        return FALSE_S;
    }

    *out_item = s->data[s->top--];

    printf("%d poped out\n", *out_item);
    return TRUE_S;
}

// 销毁栈
int destory_stack(stack **p_ps){
    if(p_ps == NULL || *p_ps == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    free(*p_ps);
    *p_ps = NULL;

    printf("INFO: STACK IS DESTORYED\n");
    return TRUE_S;
}