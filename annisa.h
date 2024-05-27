#ifndef ANNISA_H
#define ANNISA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "rizky.h"

Node* cari(List *list, const char *name);
Node* search(List *list, int *number);
void initList(List *list);
int isDuplicateItem(List *list, const char *name);
void insert(List *list);
void addStock(List *list);
void clearList(List *list);
void deleteItem(List *list);
void writefile(List *list);
void readfile(List *list);

#endif // BODY_H_INCLUDED
