#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"

typedef struct tree TREE;

TREE *get_huffman_tree(char*);
void print_tree(TREE*);
void update_codes(TREE*);
char *code(char*, TREE*);
char *decode(char* , TREE*);
void print_aux(TREE*);
void delete_tree(TREE**);

#endif
