#include "queue.h"

#define left_child(x) ((2*x)+1)
#define right_child(x) ((2*x)+2)
#define parent(x) ((x-1)/2)

struct queue{
	struct node **vector;
	int size;
};

QUEUE *create_queue(void){
	QUEUE *queue = malloc(sizeof(QUEUE));
	if(queue != NULL){
		queue->vector = NULL;
		queue->size = 0;
	}

	return queue;
}

int empty_queue(QUEUE *queue){
	if(queue != NULL && queue->vector != NULL) return 0;
	else return 1;
}

void min_heapify(int n, NODE **vector, int top){
	if(top < n){
		int min = top;
//		int left_child = left_child(top);
//		int right_child = right_child(top);
		if(left_child(top) < n && compare(vector[top]->item, vector[left_child(top)]->item, 1)  == 1) min = left_child(top);
		if(right_child(top) < n && compare(vector[top]->item, vector[right_child(top)]->item, 1)  == 1) min = right_child(top);
		if(min != top){
			NODE *aux = vector[top];
			vector[top] = vector[min];
			vector[min] = aux;
			min_heapify(n, vector, min);
		}
	}
}

int enqueue(QUEUE *queue, NODE *node){
	if(queue != NULL && node != NULL){
		int i;
		queue->size++;
		queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);
		queue->vector[queue->size-1] = node;
		for(i = parent(queue->size-1); i >= 0; i--)
			min_heapify(queue->size, queue->vector, i);

		return 0;
	}
	return 1;
}

int dequeue(QUEUE *queue){
	if(queue != NULL){
		if(!empty_queue(queue)){
			queue->size--;
			queue->vector[0] = queue->vector[queue->size];
			if(queue->size <= 0){
				free(queue->vector);
				queue->vector = NULL;
			}else{
				queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);
			}

			return 0;
		}
		return 1;
	}
	return 2;
}

NODE *front_queue(QUEUE *queue){
	if(!empty_queue(queue))	return queue->vector[0];
	else return NULL;
}

int delete_queue(QUEUE **queue){
	if(queue != NULL){
		if((*queue) != NULL){
			free((*queue)->vector);
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
		int i;
		for(i = 0; i < queue->size; i++){
			print_item(queue->vector[i]->item);
		}
		printf("||queue size = %d||\n", queue->size);
	}
}
