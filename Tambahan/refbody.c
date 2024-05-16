#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tubuh.h"

int menu() {
    int choice;
    printf("=================================\n");
    printf("             M E N U            \n");
    printf("=================================\n");
    printf("1. Tambah Barang\n");
    printf("2. Tambah Stok Barang\n");
    printf("3. Tampilkan Semua Barang\n");
    printf("4. Hapus Barang\n");
    printf("0. Exit\n");
    printf("Pilih menu: ");
    scanf("%d", &choice);
    printf("=================================\n");
    return choice;
}

Node* search(List *list, const char *name) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->info, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Barang tidak ditemukan
}

void insert(List *list) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    FILE *file = fopen("jualan.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        free(newNode);
        return;
    }
    
    printf("Masukkan nama barang: \n");
    // Membersihkan buffer stdin
    while (getchar() != '\n');
    fgets(newNode->info, sizeof(newNode->info), stdin);
    strtok(newNode->info, "\n"); // Menghapus karakter newline jika ada
    
    printf("Masukkan dekripsi barang: \n");
    fgets(newNode->detail, sizeof(newNode->detail), stdin);
    strtok(newNode->detail, "\n"); // Menghapus karakter newline jika ada
    
    printf("Masukkan harga barang (Rp): ");
    scanf("%f", &newNode->price);
    printf("Masukkan stok barang: ");
    scanf("%d", &newNode->available);
    
    // Membersihkan buffer stdin setelah membaca integer
    while (getchar() != '\n');
    
    newNode->next = NULL; // Set the next pointer to NULL
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
    if (fprintf(file, "%s|%s|%.2f|%d\n", newNode->info, newNode->detail, newNode->price, newNode->available) < 0) {
        printf("Gagal menulis ke file.\n");
    }

    fclose(file);
}

void clearList(List *list) {
    Node *current = list->head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
}

void disList(List *list) {
    FILE *file = fopen("jualan.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        printf("Tidak ada data barang.\n");
        fclose(file);
        return;
    }
    
    fseek(file, 0, SEEK_SET);
    
    clearList(list);

    printf("List Barang: \n");
    printf("\n===========================================================================\n");
    printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
    printf("===========================================================================\n");

    // Read data from file and populate the list
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            break;
        }
        sscanf(line, "%[^|]|%[^|]|%f|%d", newNode->info, newNode->detail, &newNode->price, &newNode->available);
        newNode->next = NULL;

		if (list->head == NULL) {
            list->head = newNode;
            list->tail = newNode;
        } else {
            list->tail->next = newNode;
            list->tail = newNode;
        }
	
        // Find the node in the list
//        Node *current = list->head;
////        Node *prev = NULL;
//        int found = 0;
//        while (current != NULL) {
//            if (strcmp(current->info, newNode->info) == 0) {
//                // Update the stock
//                current->available = newNode->available;
//                found = 1;
//                break;
//            }
////            prev = current;
//            current = current->next;
//        }

//		if (!found) {
//            if (list->head == NULL) {
//                list->head = newNode;
//                list->tail = newNode;
//            } else {
//                list->tail->next = newNode;
//                list->tail = newNode;
//            }
//        } else {
//            free(newNode);
//        }

        // If the node is not found in the list, add it to the end
//        if (current == NULL) {
//            if (list->head == NULL) {
//                list->head = newNode;
//                list->tail = newNode;
//            } else {
//                list->tail->next = newNode;
//                list->tail = newNode;
//            }
//        }
    }

    fclose(file);

    // Display the list
    Node *current = list->head;
    while (current != NULL) {
        printf("| %-20s | %-15s | %-10.2f | %-5d |\n", current->info, current->detail, current->price, current->available);
        current = current->next;
    }

    printf("===========================================================================\n");
}

void addStock(List *list) {
    char name[100];
    printf("Masukkan nama barang: ");
    while (getchar() != '\n'); // Clear input buffer
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n"); // Remove newline character if present

    Node *found = search(list, name);
    if (found == NULL) {
        printf("Barang tidak ditemukan.\n");
        return;
    }

    int qty;
    printf("Masukkan jumlah stok yang ingin ditambahkan: ");
    scanf("%d", &qty);
    found->available += qty;
    printf("Stok barang berhasil ditambahkan.\n");
    
    FILE *file = fopen("jualan.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char line[100];
    long pos;
    while (fgets(line, sizeof(line), file) != NULL) {
        pos = ftell(file);
        Node temp;
        sscanf(line, "%[^|]|%[^|]|%f|%d", temp.info, temp.detail, &temp.price, &temp.available);
        if (strcmp(temp.info, name) == 0) {
            fseek(file, pos - strlen(line), SEEK_SET);
            fprintf(file, "%s|%s|%.2f|%d\n", found->info, found->detail, found->price, found->available);
            fflush(file); // Ensure the updated content is written to the file
            break;
        }
    }

    fclose(file);
}

void deleteItem(List *list) {
	char name[100];
    printf("Masukkan nama barang yang ingin dihapus: ");
    while (getchar() != '\n'); // Clear input buffer
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");
    
    Node *current = list->head;
    Node *previous = NULL;
    while (current != NULL && strcmp(current->info, name) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Barang tidak ditemukan.\n");
        return;
    }
    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }
    if (current == list->tail) {
        list->tail = previous;
    }
    free(current);

    // Rewrite the file without the deleted item
    FILE *file = fopen("jualan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    current = list->head;
    while (current != NULL) {
        fprintf(file, "%s|%s|%.2f|%d\n", current->info, current->detail, current->price, current->available);
        current = current->next;
    }
    fclose(file);

    printf("Barang berhasil dihapus.\n");
}

//void disList(List *list) {
//    FILE *file = fopen("jualan.txt", "r");
//    if (file == NULL) {
//        printf("Gagal membuka file.\n");
//        return;
//    }
//
//    printf("List Barang: \n");
//    printf("\n===========================================================================\n");
//    printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
//    printf("===========================================================================\n");
//
//    // Clear existing list
//    Node *current = list->head;
//    Node *temp;
//    while (current != NULL) {
//        temp = current->next;
//        free(current);
//        current = temp;
//    }
//    list->head = NULL;
//    list->tail = NULL;
//
//    // Read data from file and populate the list
//    char line[100];
//    while (fgets(line, sizeof(line), file) != NULL) {
//        Node *newNode = (Node*) malloc(sizeof(Node));
//        if (newNode == NULL) {
//            printf("Memory allocation failed.\n");
//            break;
//        }
//        sscanf(line, "%[^|]|%[^|]|%f|%d", newNode->info, newNode->detail, &newNode->price, &newNode->available);
//        newNode->next = NULL;
//        if (list->head == NULL) {
//            list->head = newNode;
//            list->tail = newNode;
//        } else {
//            list->tail->next = newNode;
//            list->tail = newNode;
//        }
//    }
//
//    fclose(file);
//
//    // Display the list
//    current = list->head; // Start from the head of the list
//    while (current != NULL) {
//        printf("| %-20s | %-15s | %-10.2f | %-5d |\n", current->info, current->detail, current->price, current->available);
//        current = current->next; // Move to the next node
//    }
//
//    printf("===========================================================================\n");
//}



//void disList(List *list) {
//    FILE *file = fopen("jualan.txt", "r");
//    if (file == NULL) {
//        printf("Gagal membuka file.\n");
//        return;
//    }
//
//    printf("List Barang: \n");
//    printf("\n===========================================================================\n");
//    printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
//    printf("===========================================================================\n");
//
//    Node *current = list->head; // Start from the head of the list
//    while (current != NULL) {
//        printf("| %-20s | %-15s | %-10.2f | %-5d |\n", current->info, current->detail, current->price, current->available);
//        current = current->next; // Move to the next node
//    }
//
//    printf("===========================================================================\n");
//
//    fclose(file);
//}