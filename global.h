#ifndef global_H
#define global_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//loginregist
// Struktur pengguna
struct users {
    char Nama[40];
    char Email[30];
    char password[20];
    char username[20];
};

struct TreeNode {
    int shift;
    struct TreeNode *left;
    struct TreeNode *right;
};


//Linked List
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


//Queue
typedef struct Identitas {
    char alamatrumah[500];
    char alamatemail[100];
    int notelp;
} Identitas;

typedef struct listNode {
    char namapembeli[50];
    char namabarang[50];
    int qty;
    Identitas identitas;
    struct listNode *next;
} listBarang;

typedef struct {
    listBarang *front;
    listBarang *rear;
} Queue;

#endif