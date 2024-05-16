#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First
#define first(head) head->first
#define last(tail) tail->last
#ifndef rizky_H
#define rizky_H

#define MAX_INFO 30
#define MAX_DETAIL 100

// Struct untuk barang
typedef struct Node{
    char info;
    char detail;
    float price;
    int available;
    struct Node *next;
}Node;

// struct untuk pointer head
typedef struct playlist {
    struct Node *head;
    struct Node *tail;
} List;

// belum tau untuk apa(kemungkinan ga ke pake)
//typedef struct Node *address;
//
//typedef struct {
//	address First;
//} Last;

// fungsi yang ada
void createList(List *myList);
void disList(List *myList);

#endif
