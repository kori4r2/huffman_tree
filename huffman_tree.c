#include "huffman_tree.h"

struct tree{
	LIST *decoding;
	struct node *root;
};

NODE *create_node(ITEM *item){
	NODE *node = NULL;
	if(item != NULL){
		node = (NODE*)malloc(sizeof(NODE));
		if(node != NULL){
			node->item = item;
			node->left_child = NULL;
			node->right_child = NULL;
		}
	}
	return node;
}

TREE *get_huffman_tree(char *string){
	TREE *tree = NULL;
	if(string != NULL){
		tree = (TREE*)malloc(sizeof(TREE));
		tree->root = NULL;
		ITEM **vector = NULL;
		QUEUE *queue;
		NODE *left, *right, *parent;

		int i, size = 0;
		for(i = 0; string[i] != '\0'; i++){
			vector = get_character(vector, string[i], &size);
		}
		quick_sort(vector, 0, size-1);
		tree->decoding = create_list();
		for(i = 0; i < size; i++){
//			print_item(vector[i]);
			insert_front(tree->decoding, vector[i]);
		}
//		printf("------------------\n");
//		print_list(tree->decoding);
		queue = create_queue(vector, size);
		free(vector);

		//construção da árvore
		while(!empty_queue(queue)){
			right = front_queue(queue);
			dequeue(queue);
			if(!empty_queue(queue)){
				left = front_queue(queue);
				dequeue(queue);
				parent = create_node(create_item('\0'));
				set_count(parent->item, (item_count(left->item) + item_count(right->item)));
				parent->left_child = left;
				parent->right_child = right;
				enqueue(queue, parent);
			}else{
				tree->root = right;
			}
		}
		delete_queue(&queue);
	}
	return tree;
}

void print_tree(TREE *tree){
	if(tree != NULL && tree->decoding != NULL){
		print_list(tree->decoding);
	}
}

void update_down(NODE *node, int steps, unsigned int path){
	if(node != NULL){
		add_code(node->item, path, steps);
		update_down(node->left_child, steps+1, (path << 1));
		update_down(node->right_child, steps+1, ((path << 1)|1));
	}
}

void update_codes(TREE *tree){
	if(tree != NULL){
		update_down(tree->root, 0, 0);
	}
}

char search_decoding(NODE *node, char *code, int *steps){
	if(node == NULL) return '\0';
	if(item_char(node->item) != '\0') return item_char(node->item);
	if(code[*steps] == '\0') return '\0';
	if(code[(*steps)] == '0'){
		(*steps)++;
		return search_decoding(node->left_child, code, steps);
	}else{
		(*steps)++;
		return search_decoding(node->right_child, code, steps);
	}
}

char *search_coding(NODE *node, char character, int *steps, int counter){
	if(node == NULL) return NULL;
	char *aux = NULL;
	if(item_char(node->item) == character){
		*steps = counter;
		return item_code(node->item);
	}
	aux = search_coding(node->left_child, character, steps, counter+1);
	if(aux == NULL) aux = search_coding(node->right_child, character, steps, counter+1);
	return aux;
}

char *code(char *string, TREE *tree){
	if(tree != NULL && string != NULL){
		int size, i, aux;
		char *coded, *result;
		coded = (char*)malloc(sizeof(char));
		coded[0] = '\0';
		size = 1;
		for(i = 0; string[i] != '\0'; i++){
			result = search_coding(tree->root, string[i], &aux, 0);
			if(result != NULL){
				size += aux;
				coded = (char*)realloc(coded, sizeof(coded) * (size+1));
				strcat(coded, result);
			}
		}
		return coded;
	}
	return NULL;
}

char *decode(char *string, TREE *tree){
	if(string != NULL && tree != NULL){
		int i, steps;
		char *decoded = NULL;
		i = 0;
		steps = 0;
		do{
			decoded = (char*)realloc(decoded, sizeof(char)*(i+1));
			decoded[i++] = search_decoding(tree->root, string, &steps);
		}while(decoded[i-1] != '\0');
		return decoded;
	}
	return NULL;
}

void print_aux_down(NODE *node, int level){
	if(node == NULL) return;
	int i;
	print_aux_down(node->right_child, level+1);
	for(i = 0; i < level; i++) printf("      ");
	printf("%c\n", (item_char(node->item) != '\0')? item_char(node->item) : 'x');
	print_aux_down(node->left_child, level+1);
}

void print_aux(TREE *tree){
	if(tree != NULL){
		print_aux_down(tree->root, 0);
	}
}

void delete_down(NODE **node){
	if(node != NULL && *node != NULL){
		delete_down(&(*node)->left_child);
		delete_down(&(*node)->right_child);
		delete_item(&(*node)->item);
		free(*node);
		*node = NULL;
	}
}

void delete_tree(TREE **tree){
	if(tree != NULL && *tree != NULL){
		delete_list(&(*tree)->decoding);
		delete_down(&(*tree)->root);
		free(*tree);
		*tree = NULL;
	}
}
