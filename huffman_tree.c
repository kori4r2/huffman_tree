#include "huffman_tree.h"

struct tree{
	// A lista armazena os itens de todos os caracteres contidos na string em ordem crescente de frequência
	LIST *decoding;
	// root é o nó correspondente à raiz da árvore
	NODE *root;
};

// Função que cria um nó a partir de um item passado, alocano a memória necessária
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

// Função que cria uma árvore de huffman a partir de uma string passada
TREE *get_huffman_tree(char *string){
	TREE *tree = NULL;
	if(string != NULL){
		tree = (TREE*)malloc(sizeof(TREE));
		tree->root = NULL;
		ITEM **vector = NULL;
		QUEUE *queue;
		NODE *left, *right, *parent;

		// A string é analisada e os itens correspondentes aos caracteres contidos nela são inseridos em um vetor
		int i, size = 0;
		for(i = 0; string[i] != '\0'; i++){
			vector = get_character(vector, string[i], &size);
		}
		// O vetor é ordenado em ordem crescente
		quick_sort(vector, 0, size-1);
		tree->decoding = create_list();
		// A lista é criada com os items inseridos de forma que os mais frequentes sejam os primeiros da lista
		for(i = 0; i < size; i++){
			insert_front(tree->decoding, vector[i]);
		}
		// A fila auxiliar é criada a partir do vetor
		queue = create_queue(vector, size);
		// A memória alocada é liberada
		free(vector);
	
		// Enquanto a fila estiver vazia
		while(!empty_queue(queue)){
			// A variável auxiliar armazena o nó na frente da fila
			right = front_queue(queue);
			// E esse nó é desenfileirado
			dequeue(queue);
			// Caso ainda hajam mais nós na fila
			if(!empty_queue(queue)){
				// A segunda variável auxiliar armazena o nó na frente da fila
				left = front_queue(queue);
				// E esse nó é desenfileirado
				dequeue(queue);
				// É criado um nó com o caracter '\0'
				parent = create_node(create_item('\0'));
				// Seu valor é alterado para a soma dos valores dos dois nós armazenados
				set_count(parent->item, (item_count(left->item) + item_count(right->item)));
				// Os nós armazenados são salvos como filhos do nó criado
				parent->left_child = left;
				parent->right_child = right;
				// E o nó criado é adicionado à fila
				enqueue(queue, parent);
			}else{
				// Caso contrário, esse único nó será a raiz da árvore
				tree->root = right;
			}
		}
		// Apaga a fila auxiliar
		delete_queue(&queue);
	}
	// Retorna a árvore criada
	return tree;
}

// Função que imprime a lista de caracteres armazenados na árvore
void print_tree(TREE *tree){
	if(tree != NULL && tree->decoding != NULL){
		print_list(tree->decoding);
	}
}

// Função recursiva que atualiza o código dos elementos armazenados na árvore
void update_down(NODE *node, int steps, unsigned int path){
	if(node != NULL){
		// Atualiza o código do nó atual de acordo com os bits de path e o número de níveis descidos
		add_code(node->item, path, steps);
		// Ao descer para esquerda dá shift em path deixando 0 no bit menos significativo
		update_down(node->left_child, steps+1, (path << 1));
		// Ao descer para a direita dá shift em path deixando 1 no bit menos significativo
		update_down(node->right_child, steps+1, ((path << 1)|1));
	}
}

// Função que atualiza os códigos dos itens armazenados na árvore
void update_codes(TREE *tree){
	if(tree != NULL){
		// Chama update_down() na raiz da árvore com path e steps zerados
		update_down(tree->root, 0, 0);
	}
}

// Função que a partir de um código procura um caracter dentro da árvore e retorna seu valor
char search_decoding(NODE *node, char *code, int *steps){
	// Caso seja atingido o final da árvore, retorna '\0'
	if(node == NULL) return '\0';
	// Caso o nó encontrado não seja um nó auxiliar, retorna o caractere armazenado nele
	if(item_char(node->item) != '\0') return item_char(node->item);
	// Caso não seja encontrado um caracter válido no nó atual e o fim da string já tenha sido atingido retorna '\0'
	if(code[*steps] == '\0') return '\0';
	// Caso não seja encontrado um caracter válido e o caracter atual do código seja '0'
	if(code[(*steps)] == '0'){
		// incrementa steps e chama recursivamente para o filho da esquerda
		(*steps)++;
		return search_decoding(node->left_child, code, steps);
	// Caso contrário
	}else{
		// incrementa steps e chama recursivamente para o filho da direita
		(*steps)++;
		return search_decoding(node->right_child, code, steps);
	}
}

// Função que a partir de um caractere procura seu código dentro da árvore e retorna esse código
char *search_coding(NODE *node, char character, int *steps, int counter){
	// Caso seja atingido o fim da árvore retorna NULL
	if(node == NULL) return NULL;
	// Caso o nó atual contenha o caractere sendo procurado, retorna seu código
	if(item_char(node->item) == character){
		// E armazena quantos passos foram necessários para encontrá-lo
		*steps = counter;
		return item_code(node->item);
	}
	// A variável auxiliar é inicializada como null
	char *aux = NULL;
	// A busca é realizada recursivamente no filho à esquerda com o contador incrementado
	aux = search_coding(node->left_child, character, steps, counter+1);
	// Caso não seja encontrado no filho à esquerda, a busca é realizada recursivamente no filho à direita
	if(aux == NULL) aux = search_coding(node->right_child, character, steps, counter+1);
	// Retorna o resultado da busca nos filhos (aux)
	return aux;
}

// Função que codifica uma string passada e retorna uma nova string contendo a codificada
char *code(char *string, TREE *tree){
	if(tree != NULL && string != NULL){
		int size, i, aux;
		char *coded, *result;
		// coded é inicializada como uma string "vazia", contendo apenas o caractere indicador de fim de string
		coded = (char*)malloc(sizeof(char));
		coded[0] = '\0';
		// Tamanho inicial é 0
		size = 1;
		// Percorre a string a ser codificada
		for(i = 0; string[i] != '\0'; i++){
			aux = 0;
			// result contém o código do caractere atual e aux armazena o tamanho do código encontrado
			result = search_coding(tree->root, string[i], &aux, 0);
			// Caso tenha sido encontrada uma string de codificação
			if(result != NULL){
				// O tamanho é incrementado de acordo com o tamanho do código
				size += aux;
				coded = (char*)realloc(coded, sizeof(coded) * (size+1));
				// E o código é concatenado na string coded
				strcat(coded, result);
			}
		}
		// Retorna o resultado da codificação
		return coded;
	}
	return NULL;
}

// Função que decodifica uma string passada, retornando uma nova string contendo o resultado da decodificação
char *decode(char *string, TREE *tree){
	if(string != NULL && tree != NULL){
		int i, steps;
		char *decoded = NULL;
		i = 0;
		steps = 0;
		do{
			// Realoca decoded para armazenar mais um caractere
			decoded = (char*)realloc(decoded, sizeof(char)*(i+1));
			// Busca o caractere de acordo com a string codificada, incrementando quantos caracteres já foram analisados
			decoded[i++] = search_decoding(tree->root, string, &steps);
		// Para quando o último caractere salvo for '\0'
		}while(decoded[i-1] != '\0');
		// Retorna a string lida
		return decoded;
	}
	return NULL;
}

// Função auxiliar para impressão da árvore de maneira a facilitar visualização
void print_aux_down(NODE *node, int level){
	if(node == NULL) return;
	int i;
	print_aux_down(node->right_child, level+1);
	for(i = 0; i < level; i++) printf("      ");
	printf("%c\n", (item_char(node->item) != '\0')? item_char(node->item) : 'x');
	print_aux_down(node->left_child, level+1);
}

// Função auxiliar para debug
void print_aux(TREE *tree){
	if(tree != NULL){
		print_aux_down(tree->root, 0);
	}
}

// Função que apaga todos os nós abaixo do nó atual, incluindo ele próprio, liberando toda a memória alocada
void delete_down(NODE **node){
	if(node != NULL && *node != NULL){
		// Chama recursivamente para os filhos
		delete_down(&(*node)->left_child);
		delete_down(&(*node)->right_child);
		// Apaga o item
		delete_item(&(*node)->item);
		// Libera memória
		free(*node);
		// E muda a variável para NULL
		*node = NULL;
	}
}

// Função que apaga uma árvore de huffman, liberando toda a memória alocada
void delete_tree(TREE **tree){
	if(tree != NULL && *tree != NULL){
		delete_list(&(*tree)->decoding);
		delete_down(&(*tree)->root);
		free(*tree);
		*tree = NULL;
	}
}
