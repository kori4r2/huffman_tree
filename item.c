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
	printf("'%c': %s\n", item->character, item->code);
}

void delete_item(ITEM **item){
	if(item != NULL && *item != NULL){
		if((*item)->code != NULL) free((*item)->code);
		free(*item);
		*item = NULL;
	}
}

int compare(ITEM *item1, ITEM *item2, int type){
	if(!type){
		if(item1->character > item2->character) return 1;
		if(item1->character < item2->character) return -1;
		return 0;
	}else{
		if(item1->counter > item2->counter) return 1;
		if(item1->counter < item2->counter) return -1;
		return 0;
	}
}

void swap(ITEM **vector, int i, int j){
	if(vector != NULL && i >= 0 && j >= 0){
		ITEM *aux = vector[i];
		vector[i] = vector[j];
		vector[j] = aux;
	}
}

ITEM **get_character(ITEM **vector, char character, int *size){
	int i, found;
	found = 0;
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

int check_middle_partition(ITEM **vector, int i, int j, int sort_type){
	int k = j-1;
	while(k > i){
		if(compare(vector[j], vector[k], sort_type) != 0){
			swap(vector, i, k);
			return 0;
		}
		k--;
	}
	return 1;
}

void partition(ITEM **vector, int left, int right, int *l_pivot, int *r_pivot, int sort_type){
	int i, j;
	i = left;
	j = right;
	ITEM *pivot = vector[(left+right)/2];

	while(i < j){
		while(j > left && compare(vector[j], pivot, sort_type) > 0) j--;
		while(i < right && compare(vector[i], pivot, sort_type) < 0) i++;
		swap(vector, i, j);
		if(compare(vector[i], pivot, sort_type) == 0 && compare(vector[j], pivot, sort_type) == 0){
			if(check_middle_partition(vector, i, j, sort_type)){
				*l_pivot = i;
				*r_pivot = j;
				return;
			}
		}
	}
	*l_pivot = i;
	*r_pivot = j;
}

void quick_sort(ITEM **vector, int start, int end, int sort_type){
	if(start >= end) return;

	int r_pivot, l_pivot;
	partition(vector, start, end, &l_pivot, &r_pivot, sort_type);

	if(l_pivot < (end+start)/2){
		quick_sort(vector, start, l_pivot-1, sort_type);
		quick_sort(vector, r_pivot+1, end, sort_type);
	}else{
		quick_sort(vector, r_pivot+1, end, sort_type);
		quick_sort(vector, start, l_pivot-1, sort_type);
	}
}
