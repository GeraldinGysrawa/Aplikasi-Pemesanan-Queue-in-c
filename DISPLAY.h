#ifndef DISPLAY_H
#define DISPLAY_H

#define MAX_INFO 30
#define MAX_DETAIL 100

// Struct untuk barang
typedef struct Node {
    char info;
    char detail;
    float price;
    int available;
    struct Node *next;
} Node;

// struct untuk pointer head
typedef struct playlist {
    struct Node *head;
    struct Node *tail;
} List;

// belum tau untuk apa(kemungkinan ga ke pake)
typedef struct Node *address;

// fungsi yang ada
void createList();
void disList();

#endif