#ifndef GERALDIN_H
#define GERALDIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

void initQueue(Queue *q);
void enqueue(Queue *q, address newNode);
void saveToFile(address node);
address createNode(const char *namapembeli, const char *namabarang, int qty, Identitas identitas);
void belibarang(Queue *q, List *list);
int isValidItem(List *list, const char *name);
void enkripsiangka(char *num, int key);
void dekripsiangka(char *num, int key);


//tampilan dan penggabungan
int user();
int admin();

#endif