#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

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
void disList(List *list);

#endif // BODY_H_INCLUDED
