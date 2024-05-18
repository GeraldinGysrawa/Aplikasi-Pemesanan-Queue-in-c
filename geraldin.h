#ifndef GERALDIN_H
#define GERALDIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

void saveToFile(listBarang *node);
void enque(Queue *q, listBarang *newNode);
listBarang* createNode(const char *namapembeli, const char *namabarang, int qty, Identitas identitas);
void belibarang(Queue *q, List *list);
void writefile(List *list);
void readfile(List *list);
int isValidItem(List *list, const char *name);

//tampilan dan penggabungan
int user();
int admin();

#endif