#include "queue.h"

struct q_node{
	NODE *item;
	struct q_node *next;
	struct q_node *previous;
};

struct queue{
	struct q_node *sentry;
	int size;
};

Q_NODE *create_q_node(NODE *item){
	Q_NODE *new_q_node = NULL;
	if(item != NULL){
		new_q_node = malloc(sizeof(Q_NODE));
		if(new_q_node != NULL && item != NULL){
			new_q_node->item = item;
			new_q_node->next = new_q_node;
			new_q_node->previous = new_q_node;
		}
	}

	return new_q_node;
}

int delete_q_node(Q_NODE **q_node){
	if(q_node != NULL){
		if((*q_node) != NULL){
			free(*q_node);
			(*q_node) = NULL;
		}
	}
	return 2;
}

QUEUE *create_queue(void){
	QUEUE *queue = malloc(sizeof(QUEUE));
	Q_NODE *sentry = create_q_node(create_node(create_item('\0')));
	if(sentry != NULL && queue != NULL){
		queue->sentry = sentry;
		queue->size = 0;
	}else{
		if(queue != NULL){
			free(queue);
			queue = NULL;
		}
		if(sentry != NULL) delete_q_node(&sentry);
	}

	return queue;
}

int empty_queue(QUEUE *queue){
	if(queue != NULL && queue->size > 0) return 0;
	else return 1;
}

int enqueue(QUEUE *queue, NODE *item){
	if(queue != NULL && item != NULL){
		Q_NODE *q_node = create_q_node(item);
		if(q_node != NULL){
			q_node->previous = queue->sentry->previous;
			q_node->next = queue->sentry;
			q_node->previous->next = q_node;
			q_node->next->previous = q_node;
			queue->size++;

			return 0;
		}
		return 1;
	}
	return 2;
}

int dequeue(QUEUE *queue){
	if(queue != NULL){
		if(!empty_queue(queue)){
			Q_NODE *aux = queue->sentry->next;
			aux->next->previous = aux->previous;
			aux->previous->next = aux->next;
			delete_q_node(&aux);
			queue->size--;

			return 0;
		}
		return 1;
	}
	return 2;
}

NODE *front_queue(QUEUE *queue){
	if(!empty_queue(queue))	return queue->sentry->next->item;
	else return NULL;
}

int delete_queue(QUEUE **queue){
	if(queue != NULL){
		if((*queue) != NULL){
			while(!empty_queue(*queue)) dequeue(*queue);
			delete_item(&(*queue)->sentry->item->item);
			free((*queue)->sentry->item);
			delete_q_node( &((*queue)->sentry) );
			free(*queue);
			(*queue) = NULL;

			return 0;
		}
		return 1;
	}
	return 2;
}

void print_queue(QUEUE *queue){
	if(queue != NULL){
		Q_NODE *aux = queue->sentry->next;
		while(aux != queue->sentry){
//			print_item(aux->item);
			aux = aux->next;
		}
		printf("||queue size = %d||\n", queue->size);
	}
}
