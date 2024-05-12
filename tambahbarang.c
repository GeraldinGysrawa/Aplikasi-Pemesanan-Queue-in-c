//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <malloc.h>
#include "DISPLAY.h"
#include "tambahbarang.h"

/******* PROGRAM *******/ 
address alokasi (address X)
{
	 /* Kamus Lokal */
	 address P;
	 /* Algoritma */
	 P = (address) malloc (sizeof (Node));
	 if (P != Nil)		/* Alokasi berhasil */
	 {
	Info(P) = X;
	Next(P) = Nil;
	 }
	 return (P);
}

void deAlokasi (address P)
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */
{
	 if (P != Nil)
	 {
	free (P);
	 }
}



// Memasukkan barang yang dijual
void input_barang(List *myList) {
    // Cek apakah list kosong
//    if (myList->head == NULL) {
//        // Jika kosong, inisialisasi list
//        createList(myList);
//    }

    char info[30];
    char detail[100];
    float price;
    int available;

    printf("Masukkan nama barang: ");
    scanf("%s", info);
    printf("Masukkan dekripsi barang: ");
    scanf("%s", detail);
    printf("Masukkan harga barang (Rp): ");
    scanf("%f", &price);
    printf("Masukkan stok barang: ");
    scanf("%d", &available);

    // Membersihkan newline character dari buffer stdin
    getchar();

    // Membuat node baru untuk barang yang akan ditambahkan
//    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
//    if (newNode == NULL) {
//        printf("Gagal mengalokasikan memori untuk node baru.\n");
//        exit(EXIT_FAILURE);
//    }
    
    // Mengisi data barang ke dalam node baru
//    strcpy(newNode->info, info);
//    strcpy(newNode->detail, detail);
//    newNode->price = price;
//    newNode->available = available;
//    newNode->next = NULL;

    // Jika list masih kosong, atur head dan tail menjadi newNode
//    if (myList->head == NULL) {
//        myList->head = newNode;
//        myList->tail = newNode;
//    } else {
//        // Jika list tidak kosong, tambahkan newNode ke akhir list dan perbarui tail
//        myList->tail->next = newNode;
//        myList->tail = newNode;
//    }
}

// Implementasi fungsi untuk meminta input dan menambahkan barang baru
void tambah_stok(struct Node **head) {
//    int option;
//    do {
//        printf("\nPilih opsi:\n");
////        printf("1. Tambahkan barang baru\n");
//        printf("2. Tambahkan stok untuk barang yang sudah ada\n");
//        printf("Masukkan pilihan: ");
//        scanf("%d", &option);

//        if (option == 1) {
            char info;
	    	char detail;
		    float price;
		    int available;

            // Meminta input dari pengguna
//            printf("Masukkan nama barang: ");
//            scanf("%s", info);
//            printf("Masukkan dekripsi barang: ");
//            scanf("%s", detail);
//            printf("Masukkan harga barang (Rp): ");
//            scanf("%f", &price);
//            printf("Masukkan stok barang: ");
//            scanf("%d", &available);

            // Menambahkan barang baru ke linked list
//            tambah_barang(head, info, detail, price, available);
//        } else if (option == 2) {
//           	char info[30];
//			char detail[100];
//		    float price;
//		    int available;

            // Meminta input dari pengguna
            printf("Masukkan nama barang yang ingin ditambah stoknya: ");
            scanf("%s", info);

            // Mengecek apakah barang sudah ada dalam linked list
            struct Node *existing_item = *head;
            while (existing_item != NULL && strcmp(existing_item->info, info) != 0) {
                existing_item = existing_item->next;
            }

            if (existing_item != NULL) {
                // Jika barang sudah ada, tambahkan stok barang
                printf("Masukkan jumlah stok tambahan: ");
                scanf("%d", &available);
                existing_item->available += available;
            } else {
                printf("Barang tidak ditemukan.\n");
//            } else {
//            printf("Opsi tidak valid.\n");
//        }
			
        // Membersihkan buffer masukan
        printf("\n\tPress any key to continue . . . ");
		getch();

        // Meminta penjual untuk memilih opsi lagi atau keluar
    } 
}
//	while (option == 1 || option == 2);


//void input_barang(List *myList) {
//    // Cek apakah list kosong
//    if (myList->head == NULL) {
//        // Jika kosong, inisialisasi list
//        createList(myList);
//    }
//
//    char info[30];
//    char detail[100];
//    float price;
//    int available;
//
//    printf("Masukkan barang yang akan dijual: ");
//    scanf("%s", info);
//    printf("Masukkan dekripsi barang: ");
//    scanf("%s", detail);
//    printf("Masukkan harga barang (Rp): ");
//    scanf("%f", &price);
//    printf("Masukkan stok barang: ");
//    scanf("%d", &available);
//
//    // Membuat node baru untuk barang yang akan ditambahkan
//    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
//    if (newNode == NULL) {
//        printf("Gagal mengalokasikan memori untuk node baru.\n");
//        exit(EXIT_FAILURE);
//    }
//    
//    // Mengisi data barang ke dalam node baru
//    strcpy(newNode->info, info);
//    strcpy(newNode->detail, detail);
//    newNode->price = price;
//    newNode->available = available;
//    newNode->next = NULL;
//
//    // Jika list masih kosong, atur head dan tail menjadi newNode
//    if (myList->head == NULL) {
//        myList->head = newNode;
//        myList->tail = newNode;
//    } else {
//        // Jika list tidak kosong, tambahkan newNode ke akhir list dan perbarui tail
//        myList->tail->next = newNode;
//        myList->tail = newNode;
//    }
//}


// Fungsi untuk menyimpan data ke dalam file catatan.txt
//void simpan_ke_file(List *myList) {
//    FILE *file = fopen("catatan.txt", "w");
//    if (file == NULL) {
//        printf("Gagal membuka file.\n");
//        return;
//    }
//
//    Node *current = myList->head;
//    while (current != NULL) {
//        fprintf(file, "%s %.2f %d\n", current->info, current->price, current->available);
//        current = current->next;
//    }
//
//    fclose(file);
//}