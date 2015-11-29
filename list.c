#include "list.h"

typedef struct l_node{
	ITEM *item;
	struct l_node *next;
}L_NODE;

struct list{
	struct l_node *first;
};

// Função que cria uma lista de nós, alocando a memória necessária
LIST *create_list(void){
	LIST *list = (LIST*)malloc(sizeof(LIST));
	if(list != NULL){
		list->first = NULL;
	}
	return list;
}

// Função que cria um nó da lista a partir de um item, alocando a memória necessária
L_NODE *create_l_node(ITEM *item){
	L_NODE *node = (L_NODE*)malloc(sizeof(L_NODE));
	if(node != NULL){
		node->item = item;
		node->next = NULL;
	}
	return node;
}

// Função que apaga um nó, liberando a memória alocada por ele mas não a memória alocada pelo item armazenado
void delete_l_node(L_NODE **node){
	if(node != NULL && *node != NULL){
		free(*node);
		*node = NULL;
	}
}

// Função que insere um item como primeiro da lista
void insert_front(LIST *list,ITEM *item){
	L_NODE *new_node;
	new_node = create_l_node(item);

	new_node->next = list->first;
	list->first = new_node;
}

// Função que imprime todos os itens armazenados na lista
void print_list(LIST *list){
	L_NODE *aux = list->first;
	while(aux != NULL){
		print_item(aux->item);
		aux = aux->next;
	}
}

// Função que apaga todos os nós da lista usando a função delete_l_node()
void delete_list(LIST **list){
	if(list != NULL && *list != NULL){
		L_NODE *deleted;
		while((*list)->first != NULL){
			deleted = (*list)->first;
			(*list)->first = (*list)->first->next;
			delete_l_node(&deleted);
		}
		free(*list);
		*list = NULL;
	}
}
