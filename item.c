#include "item.h"

struct item{
	char character;
	int counter;
	char *code;
};

ITEM *create_item(char character){
	ITEM *item = (ITEM*)malloc(sizeof(ITEM));
	if(item != NULL){
		item->character = character;
		item->counter = 1;
		item->code = NULL;
	}
	return item;
}

void set_count(ITEM *item, int value){
	if(item != NULL) item->counter = value;
}

int item_count(ITEM *item){
	if(item != NULL) return item->counter;
	return 0;
}

char item_char(ITEM *item){
	if(item != NULL) return item->character;
	return '\0';
}

char *item_code(ITEM *item){
	if(item != NULL) return item->code;
	return NULL;
}

void print_item(ITEM *item){
	printf("'%c' : %s\n", item->character, item->code);
}

void delete_item(ITEM **item){
	if(item != NULL && *item != NULL){
		if((*item)->code != NULL) free((*item)->code);
		free(*item);
		*item = NULL;
	}
}

int compare(ITEM *item1, ITEM *item2){
	if(item1->counter > item2->counter) return 1;
	if(item1->counter < item2->counter) return -1;
	return 0;
}

void swap(ITEM **vector, int i, int j){
	if(vector != NULL && i >= 0 && j >= 0){
		ITEM *aux = vector[i];
		vector[i] = vector[j];
		vector[j] = aux;
	}
}

ITEM **get_character(ITEM **vector, char character, int *size){
	int i, found = 0;
	for(i = 0; i < *size && !found; i++){
		if(vector[i]->character == character){
			found = 1;
			vector[i]->counter++;
		}
	}
	if(!found){
		(*size)++;
		vector = (ITEM**)realloc(vector, sizeof(ITEM*) * (*size));
		vector[(*size)-1] = create_item(character);
	}
	return vector;
}

void add_code(ITEM *item, unsigned int value, int steps){
	if(item != NULL){
		int i;
		unsigned int aux = 1;
		item->code = (char*)malloc(sizeof(char) * (steps+1));
		for(i = 1; i <= steps; i++){
			item->code[steps-i] = ((aux & value)/aux)+'0';
			aux *= 2;
		}
		item->code[steps] = '\0';
	}
}

int partition(ITEM **vector, int left, int right){
	int i, j;

	i = left;
	for(j = left+1; j <= right; j++){
		if(compare(vector[j], vector[left]) == -1){
			++i;
			swap(vector, i, j);
		}
	}
	swap(vector, left, i);

	return i;
}


void quick_sort(ITEM **vector, int left, int right){
	if(left < right){
		int pos = partition(vector, left, right);

		quick_sort(vector, left, pos-1);
		quick_sort(vector, pos+1, right);
	}
}
