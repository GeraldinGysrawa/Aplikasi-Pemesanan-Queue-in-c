#ifndef TUBUH_H_INCLUDED
#define TUBUH_H_INCLUDED

typedef struct Node {
    char info[100];
    char detail[100];
    float price;
    int available;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

int menu();
void insert(List *list);
void addStock(List *list);
void disList(List *list);
void clearList(List *list);
void deleteItem(List *list);

#endif // BODY_H_INCLUDED
