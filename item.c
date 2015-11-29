#include "item.h"

struct item{
	char character;
	int counter;
	char *code;
};

// Função que cria um item para armazenar um caracter, alocando a memória necessária
ITEM *create_item(char character){
	ITEM *item = (ITEM*)malloc(sizeof(ITEM));
	if(item != NULL){
		// Armazena o caracter passado
		item->character = character;
		// Inicia a contagem em 1
		item->counter = 1;
		// O código começa como NULL
		item->code = NULL;
	}
	return item;
}

// Função que altera o contador de um item já criado
void set_count(ITEM *item, int value){
	if(item != NULL) item->counter = value;
}

// Função que retorna o contador de um item já criado
int item_count(ITEM *item){
	if(item != NULL) return item->counter;
	return 0;
}

// Função que retorna o caracter armazenado em um item já criado
char item_char(ITEM *item){
	if(item != NULL) return item->character;
	return '\0';
}

// Função que retorna o código de um item já criado
char *item_code(ITEM *item){
	if(item != NULL) return item->code;
	return NULL;
}


// Função que imprime o caracter armazenado em um item e seu código
void print_item(ITEM *item){
	printf("'%c' : %s\n", item->character, item->code);
}

// Função que apaga um item, liberando toda a memória alocada
void delete_item(ITEM **item){
	if(item != NULL && *item != NULL){
		if((*item)->code != NULL) free((*item)->code);
		free(*item);
		*item = NULL;
	}
}

// Função que compara os contadores de 2 items e retorna o resultado da comparação
int compare(ITEM *item1, ITEM *item2){
	// Ordem decrescente
	if(item1->counter > item2->counter) return 1;
	// Ordem crescente
	if(item1->counter < item2->counter) return -1;
	return 0;
}

// Função que troca a posição de dois itens contidos em um vetor de itens
void swap(ITEM **vector, int i, int j){
	if(vector != NULL && i >= 0 && j >= 0){
		ITEM *aux = vector[i];
		vector[i] = vector[j];
		vector[j] = aux;
	}
}

// Função que analisa um caracter armazena-o num vetor de itens ou altera o contador ja existente
ITEM **get_character(ITEM **vector, char character, int *size){
	// A flag found indica se o caractere foi encontrado dentro do vetor ou não
	int i, found = 0;
	for(i = 0; i < *size && !found; i++){
		// Caso seja encontrado, incrementa o contador e altera a flag
		if(vector[i]->character == character){
			found = 1;
			vector[i]->counter++;
		}
	}
	// Caso não seja encontrado
	if(!found){
		// Aumenta o tamanho do vetor
		(*size)++;
		vector = (ITEM**)realloc(vector, sizeof(ITEM*) * (*size));
		// E adiciona o novo item no fim do vetor
		vector[(*size)-1] = create_item(character);
	}
	return vector;
}

// Função que salva o código de um caracter inserido na árvore de huffman
void add_code(ITEM *item, unsigned int value, int steps){
	// A variável value é um unsigned int que armazena em seus bits o caminho percorrido até chegar no nó da arvore
	// A variável steps armazena quantos níveis se desceu na árvore até chegar ao nó atual
	if(item != NULL){
		int i;
		unsigned int aux = 1;
		// Aloca-se a memória necessária para armazenar o código
		item->code = (char*)malloc(sizeof(char) * (steps+1));
		// Analiza value bit a bit
		for(i = 1; i <= steps; i++){
			// Se value for 0 armazena o caracter '0' e se for 1 armazena '0'+1 = '1'
			item->code[steps-i] = ((aux & value)/aux)+'0';
			// A variavel auxiliar é multiplicada por 2 para ser analisado o próximo bit
			aux *= 2;
		}
		// O indicador de fim de string é adicionado
		item->code[steps] = '\0';
	}
}

// Função auxiliar do quick sort que ordena uma partição em relação a um pivô escolhido
int partition(ITEM **vector, int left, int right){
	int i, j;

	// O item mais à esquerda é escolhido como pivô
	i = left;
	// Percorre-se o restante do vetor
	for(j = left+1; j <= right; j++){
		// Se for encontrado um número menor que o pivô, i é incrementado
		if(compare(vector[j], vector[left]) == -1){
			++i;
			// E o número encontrado é jogado para a esquerda de i
			swap(vector, i, j);
		}
	}
	// i armazenará a posição final do pivô no vetor ordenado
	swap(vector, left, i);

	// A posição do pivô é retornada
	return i;
}


void quick_sort(ITEM **vector, int left, int right){
	// Caso haja ao menos dois elementos no intervalo passado
	if(left < right){
		// A partição é feita e a posição do pivô é armazenada
		int pos = partition(vector, left, right);

		// Chama recursivamente para a esquerda e a direita do pivô
		quick_sort(vector, left, pos-1);
		quick_sort(vector, pos+1, right);
	}
}
