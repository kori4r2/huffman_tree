#include "queue.h"

#define left_child(x) ((2*x)+1)
#define right_child(x) ((2*x)+2)
#define parent(x) ((x-1)/2)

struct queue{
	struct node **vector;
	int size;
};

QUEUE *create_queue(ITEM **vector, int size){
	QUEUE *queue = malloc(sizeof(QUEUE));
	if(queue != NULL){
		int i;
		queue->vector = (NODE**)malloc(sizeof(NODE) * size);;
		for(i = 0; i < size; i++){
			queue->vector[i] = create_node(vector[size-1-i]);
		}
		queue->size = size;
	}

	return queue;
}

int empty_queue(QUEUE *queue){
	if(queue != NULL && queue->vector != NULL) return 0;
	else return 1;
}

void swap_nodes(NODE **vector, int i, int j){
	if(vector != NULL){
		NODE *aux = vector[i];
		vector[i] = vector[j];
		vector[j] = aux;
	}
}

void merge(NODE **vector, int start, int middle, int end){
	NODE **left, **right;
	int nleft, nright;
	int i, j, k;

	nleft = middle - start+1;
	nright = end - middle;
        left = (NODE**)malloc(nleft * sizeof(NODE*));
        right = (NODE**)malloc(nright * sizeof(NODE*));

        // copiando os dados do vetor original para o vetor à esquerda
        for(i = 0; i < nleft; i++){
                left[i] = vector[i+start];
        }

        // copiando os dados do vetor original para o vetor à direita
        for(i = 0; i < nright; i++){
                right[i] = vector[i+middle+1];
        }

        i = j = 0;

        for(k = start; k <= end; k++) {
                if(j >= nright || (i < nleft && compare(left[i]->item, right[j]->item) >= 0)){
                        vector[k] = left[i++];
                }else{
                        vector[k] = right[j++];
                }
        }

        free(left);
        free(right);
}

void merge_sort(NODE **vector, int start, int end){
        int middle;

        if(start < end){
                middle = (start + end) / 2;

                merge_sort(vector, start, middle);
                merge_sort(vector, middle+1, end);
                merge(vector, start, middle, end);
        }
}

int enqueue(QUEUE *queue, NODE *node){
	if(queue != NULL && node != NULL){
		queue->size++;
		queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);
		queue->vector[queue->size-1] = node;
		merge_sort(queue->vector, 0, queue->size-1);

		return 0;
	}
	return 1;
}

int dequeue(QUEUE *queue){
	if(queue != NULL){
		if(!empty_queue(queue)){
			queue->size--;
			if(queue->size <= 0){
				free(queue->vector);
				queue->vector = NULL;
			}else queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);

			return 0;
		}
		return 1;
	}
	return 2;
}

NODE *front_queue(QUEUE *queue){
	if(!empty_queue(queue))	return queue->vector[queue->size-1];
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

// Função auxiliar de debug
void print_queue(QUEUE *queue){
	if(queue != NULL){
		int i;
		printf("------------------------\n");
		for(i = 0; i < queue->size; i++){
			print_item(queue->vector[i]->item);
		}
		printf("------------------------\n");
	}
}
