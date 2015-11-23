#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"
#include "my_strings.h"

int main(int argc, char *argv[]){

	char *input = my_get_line(stdin);
	TREE *tree = get_huffman_tree(input);
	update_codes(tree);
	char *coded = code(input, tree);
	char *decoded = decode(coded, tree);
	print_tree(tree);
	printf("encode: %s\ndecode: %s\n", coded, decoded);
	free(input);
	free(coded);
	free(decoded);
	delete_tree(&tree);

	return 0;
}
