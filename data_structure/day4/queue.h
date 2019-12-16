#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin_tree.h"

#define SIZE 15 

typedef tree_node q_data_type;
typedef struct {
    q_data_type data[SIZE];
    int front,
        rear;
}queue;

extern int init_queue(queue **pp_q);
extern int is_empty(queue *p_q);
extern int is_full(queue *p_q);
extern int enqueue(queue *p_q, q_data_type item);
extern int dequeue(queue *p_q, q_data_type *item);
extern int clear_queue(queue *p_q);
extern int destory_queue(queue **p_q);
extern int get_queue(queue *p_q); 

#endif
