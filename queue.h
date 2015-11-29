#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>
#include "item.h"

// A struct node precisa ser declarada em queue.h pois será necessário acessar seu conteúdo tanto em queue.c quanto em huffman_tree.c
typedef struct node{
	ITEM *item;
	struct node *left_child;
	struct node *right_child;
}NODE;
typedef struct q_node Q_NODE;
typedef struct queue QUEUE;

NODE *create_node(ITEM*);
QUEUE *create_queue(ITEM**, int);
int empty_queue(QUEUE*);
int enqueue(QUEUE*, NODE*);
int dequeue(QUEUE*);
NODE *front_queue(QUEUE*);
int delete_queue(QUEUE**);
void print_queue(QUEUE*);

#endif
