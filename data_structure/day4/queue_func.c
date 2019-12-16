#include "queue.h"

int init_queue(queue **pp_q){
    *pp_q = (queue *)malloc(sizeof(queue));
    if (*pp_q == NULL){
        printf("FAILED: MEMORY IS FULL\n");
        return FALSE_S;
    }

    memset(*pp_q, 0, sizeof(queue));
    (*pp_q)->front = SIZE - 1;
    (*pp_q)->rear = SIZE - 1;

    return TRUE_S;
}

int is_empty(queue *p_q){
    return p_q == NULL ? ERROR_S : p_q->front == p_q->rear ? TRUE_S : FALSE_S;
}
int is_full(queue *p_q){
    return p_q == NULL ? ERROR_S : p_q->front == (p_q->rear+1)%SIZE ? TRUE_S : FALSE_S;
}
int enqueue(queue *p_q, q_data_type item){
    if (p_q == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    if (is_full(p_q) == TRUE_S){
        printf("FAILED: QUEUE IS FULL\n");
        return FALSE_S;
    }

    p_q->rear = (p_q->rear + 1) % SIZE;
    p_q->data[p_q->rear] = item;

    // printf("%d enqueue\n", item.data);

    return TRUE_S;
}

int dequeue(queue *p_q, q_data_type *item){
    if (p_q == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    if (is_empty(p_q) == TRUE_S){
        printf("FAILED: QUEUE IS EMPTY\n");
        return FALSE_S;
    }

    *item = p_q->data[(p_q->front + 1) % SIZE];
    p_q->front = (p_q->front + 1) % SIZE;

    // printf("%d dequeue\n", (*item).data);

    return TRUE_S;
}

int clear_queue(queue *p_q){
    if (p_q == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    if (is_empty(p_q) == TRUE_S){
        printf("FAILED: QUEUE IS ALREADY EMPTY\n");
        return TRUE_S;
    }

    p_q->front = p_q->rear;

    return TRUE_S;
}

int destory_queue(queue **pp_q){
    if(*pp_q == NULL || pp_q == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    free(*pp_q);
    *pp_q = NULL;

    return TRUE_S;
}

int get_queue(queue *p_q){
    if (p_q == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    if (is_empty(p_q) == TRUE_S){
        printf("FAILED: QUEUE IS EMPTY\n");
        return FALSE_S;
    }

    int i = 1;
    for(; (p_q->front + i)%SIZE != p_q->rear; i++){
        printf("%d ", p_q->data[(p_q->front + i)%SIZE].data);
    }
    printf("%d\n", p_q->data[(p_q->front + i)%SIZE].data);

    return TRUE_S;
}