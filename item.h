#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct item ITEM;

ITEM *create_item(char);
void print_item(ITEM*);
void set_count(ITEM*, int);
int item_count(ITEM*);
char item_char(ITEM*);
char *item_code(ITEM*);
void delete_item(ITEM**);
int compare(ITEM*, ITEM*);
void quick_sort(ITEM**, int, int);
ITEM **get_character(ITEM **vector, char character, int *size);
void add_code(ITEM*, unsigned int, int steps);

#endif
