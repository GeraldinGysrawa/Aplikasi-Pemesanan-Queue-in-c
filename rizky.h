#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#ifndef rizky_H
#define rizky_H

// Struct untuk barang
typedef struct Node{
    char info[100];
    char detail[100];
    float price;
    int available;
    struct Node *next;
}Node;

// struct untuk pointer head&tail
typedef struct playlist {
    Node *head;
    Node *tail;
} List;

// fungsi yang ada
void createList(List *myList);
void disList(List *myList);

#endif
