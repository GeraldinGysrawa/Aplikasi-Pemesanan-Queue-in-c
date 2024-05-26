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
	int number;
    char info[100];
    char detail[100];
    float price;
    int available;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int lastNumber;
} List;

//Queue
typedef struct listNode *address;
typedef struct Identitas {
    char alamatrumah[500];
    char alamatemail[100];
    char notelp[20];
} Identitas;

typedef struct listNode {
    char namapembeli[50];
    char namabarang[50];
    int qty;
    Identitas identitas;
    address next;
} listBarang;

typedef struct {
    address front;
    address rear;
} Queue;

#endif