#ifndef ANNISA_H
#define ANNISA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "rizky.h"


void insert(List *list);
void addStock(List *list);
void clearList(List *list);
void deleteItem(List *list);
void writefile(List *list);
void readfile(List *list);

#endif // BODY_H_INCLUDED
