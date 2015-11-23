#include "list.h"

typedef struct l_node{
	ITEM *item;
	struct l_node *next;
}L_NODE;

struct list{
	struct l_node *first;
};

LIST *create_list(void){
	LIST *list = (LIST*)malloc(sizeof(LIST));
	if(list != NULL){
		list->first = NULL;
	}
	return list;
}

L_NODE *create_l_node(ITEM *item){
	L_NODE *node = (L_NODE*)malloc(sizeof(L_NODE));
	if(node != NULL){
		node->item = item;
		node->next = NULL;
	}
	return node;
}

void delete_l_node(L_NODE **node){
	if(node != NULL && *node != NULL){
		free(*node);
		*node = NULL;
	}
}

void insert_sorted(LIST *list,ITEM *item){
	L_NODE *previous, *next, *new_node;
	previous = NULL;
	next = list->first;
	while(next != NULL && (compare(item, next->item, 0) > 0)){
		if(previous == NULL) previous = list->first;
		else previous = previous->next;

		if(next != NULL) next = next->next;
	}
	new_node = create_l_node(item);

	if(previous == NULL) list->first = new_node;
	else previous->next = new_node;

	new_node->next = next;
}

void print_list(LIST *list){
	L_NODE *aux = list->first;
	while(aux != NULL){
		print_item(aux->item);
		aux = aux->next;
	}
}

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
