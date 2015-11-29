// Ítalo Tobler Silva - nUSP 8551910
#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"
#include "my_strings.h"

int main(int argc, char *argv[]){

	// Obtém uma string da stdin
	char *input = my_get_line(stdin);
	// Cria a árvore de huffman correspondente à string lida
	TREE *tree = get_huffman_tree(input);
	// Atualiza os códigos da árvore
	update_codes(tree);
	// coded recebe a string codificada
	char *coded = code(input, tree);
	// decoded recebe coded decodificada
	char *decoded = decode(coded, tree);
	// Imprime na stdout os itens armazenados na árvore
	print_tree(tree);
	// Imprime na stdout as strings obtidas a partir da codificação e decodificação
	printf("\nencode: %s\n\ndecode: %s\n", coded, decoded);
	// Libera a memória alocada
	free(input);
	free(coded);
	free(decoded);
	delete_tree(&tree);

	return 0;
}
