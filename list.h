#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include "item.h"

typedef struct list LIST;

LIST *create_list(void);
void insert_front(LIST*,ITEM*);
void print_list(LIST*);
void delete_list(LIST**);

#endif
