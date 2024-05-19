#include "annisa.h"

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

    // Update the stock in the file
    FILE *file = fopen("jualan.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Use a temporary file to rewrite the content
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file sementara.\n");
        fclose(file);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        Node temp;
        sscanf(line, "%[^|]|%[^|]|%f|%d", temp.info, temp.detail, &temp.price, &temp.available);
        if (strcmp(temp.info, name) == 0) {
            fprintf(tempFile, "%s|%s|%.2f|%d\n", found->info, found->detail, found->price, found->available);
        } else {
            fprintf(tempFile, "%s|%s|%.2f|%d\n", temp.info, temp.detail, temp.price, temp.available);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the updated file
    remove("jualan.txt");
    rename("temp.txt", "jualan.txt");
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

