#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "item.h"

typedef struct node{
	ITEM *item;
	struct node *left_child;
	struct node *right_child;
}NODE;
typedef struct q_node Q_NODE;
typedef struct queue QUEUE;

NODE *create_node(ITEM*);
Q_NODE *create_q_node(NODE*);
int delete_q_node(Q_NODE**);
QUEUE *create_queue(void);
int empty_queue(QUEUE*);
int enqueue(QUEUE*, NODE*);
int dequeue(QUEUE*);
NODE *front_queue(QUEUE*);
int delete_queue(QUEUE**);
void print_queue(QUEUE*);

#endif
