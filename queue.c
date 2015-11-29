#include "queue.h"

struct queue{
	struct node **vector;
	int size;
};

// Uma fila de nós é criada a partir de um vetor de itens
QUEUE *create_queue(ITEM **vector, int size){
	QUEUE *queue = malloc(sizeof(QUEUE));
	if(queue != NULL){
		int i;
		// Aloca-se a memória necessária para guardar os nós de todos os itens do vetor
		queue->vector = (NODE**)malloc(sizeof(NODE) * size);
		// O vetor é inserido de maneira invertida
		for(i = 0; i < size; i++){
			queue->vector[i] = create_node(vector[size-1-i]);
		}
		// O tamanho do vetor é armazenado
		queue->size = size;
	}

	return queue;
}

// Função que retorna se a fila está vazia
int empty_queue(QUEUE *queue){
	if(queue != NULL && queue->vector != NULL) return 0;
	else return 1;
}

// Função que troca a posição de dois nós de um vetor
void swap_nodes(NODE **vector, int i, int j){
	if(vector != NULL){
		NODE *aux = vector[i];
		vector[i] = vector[j];
		vector[j] = aux;
	}
}

// Função que mescla duas metades de uma partição de um vetor de nós, ordenando-as de maneira decrescente
void merge(NODE **vector, int start, int middle, int end){
	NODE **left, **right;
	int nleft, nright;
	int i, j, k;

	nleft = middle - start+1;
	nright = end - middle;
        left = (NODE**)malloc(nleft * sizeof(NODE*));
        right = (NODE**)malloc(nright * sizeof(NODE*));

        // Copia os dados do vetor original para o vetor à esquerda
        for(i = 0; i < nleft; i++){
                left[i] = vector[i+start];
        }

        // Copia os dados do vetor original para o vetor à direita
        for(i = 0; i < nright; i++){
                right[i] = vector[i+middle+1];
        }

        i = j = 0;

	// Reinsere os dados no vetor original em ordem decrescente
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

// Função que ordena um vetor de nós de maneira descrescente utilizando o algoritmo de merge sort (mantém a ordem de entrada)
void merge_sort(NODE **vector, int start, int end){
        int middle;

	// Casó haja ao menos dois nós no intervalo
        if(start < end){
		// Obtém o meio do intervalo passado
                middle = (start + end) / 2;

		// Faz chamada recursiva para as duas metades do intervalo
                merge_sort(vector, start, middle);
                merge_sort(vector, middle+1, end);
		// Chama a função merge para o intervalo
                merge(vector, start, middle, end);
        }
}

// Função que enfileira um nó e reordena a fila de modo que o último item do vetor seja o primeiro da fila (ordem decrescente)
int enqueue(QUEUE *queue, NODE *node){
	if(queue != NULL && node != NULL){
		// Aumenta o tamanho da fila
		queue->size++;
		queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);
		// Insere o nó no fim do vetor
		queue->vector[queue->size-1] = node;
		// Reordena utilizando o merge sort
		merge_sort(queue->vector, 0, queue->size-1);

		return 0;
	}
	return 1;
}

// Função que desenfilera um item
int dequeue(QUEUE *queue){
	if(queue != NULL){
		if(!empty_queue(queue)){
			// Diminui o tamanho da fila
			queue->size--;
			// Caso o tamanho seja zero, libera a memória alocada pelo vetor e faz com que seja nulo
			if(queue->size <= 0){
				free(queue->vector);
				queue->vector = NULL;
			// Caso contrário, apenas realoca a memória, apagando o último item do vetor (primeiro da fila)
			}else queue->vector = (NODE**)realloc(queue->vector, sizeof(NODE*) * queue->size);

			return 0;
		}
		return 1;
	}
	return 2;
}

// Função que retorna o nó que se encontra no final do vetor (frente da fila)
NODE *front_queue(QUEUE *queue){
	if(!empty_queue(queue))	return queue->vector[queue->size-1];
	// Caso seja passado parâmetro inválido ou uma fila vazia, retorna NULL
	else return NULL;
}

// Função que apaga uma fila, liberando a memória alocada pela fila em si mas não pelos nós contidos nela
int delete_queue(QUEUE **queue){
	if(queue != NULL){
		if((*queue) != NULL){
			// Libera o vetor auxiliar criado pela fila se necessário
			if((*queue)->vector != NULL) free((*queue)->vector);
			// Libera a memória alocada pela fila e muda seu valor para nulo
			free(*queue);
			(*queue) = NULL;

			return 0;
		}
		return 1;
	}
	return 2;
}

// Função auxiliar de impressão para debug
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
