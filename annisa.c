#include "annisa.h"

Node* search(List *list, int *number) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->number == number) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Barang tidak ditemukan
}

Node* cari(List *list, const char *name) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->info, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Barang tidak ditemukan
}

int isDuplicateItem(List *list, const char *name) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->info, name) == 0) {
            return 1; // Return true if the item with the same name is found
        }
        current = current->next;
    }
    return 0; // Return false if no item with the same name is found
}

void initList(List *list) {
    list->head = NULL;
    list->tail = NULL;
//    list->lastNumber = 0;
}

void insert(List *list) {
	Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
	int lastNumber = 0; 
    // Membaca nomor catatan terakhir dari file jika tersedia
    FILE *file = fopen("jualan.txt", "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d", &lastNumber);
        }
        fclose(file);
        lastNumber++; 
    } 
    
    file = fopen("jualan.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        free(newNode);
        return;
    }
    
    newNode->number = lastNumber;
    
    printf("Masukkan nama barang: \n");
    // Membersihkan buffer stdin
    while (getchar() != '\n');
    fgets(newNode->info, sizeof(newNode->info), stdin);
    strtok(newNode->info, "\n"); // Menghapus karakter newline jika ada
    
    // Cek apakah nama barang sudah ada dalam list
    if (isDuplicateItem(list, newNode->info)) {
        printf("Barang dengan nama yang sama sudah ada dalam list. Barang tidak dapat ditambahkan.\n");
        free(newNode);
        fclose(file);
        return;
    }
    
    printf("Masukkan dekripsi barang: \n");
    fgets(newNode->detail, sizeof(newNode->detail), stdin);
    strtok(newNode->detail, "\n"); // Menghapus karakter newline jika ada
    
    printf("Masukkan harga barang (Rp): ");
    scanf("%f", &newNode->price);
    printf("Masukkan stok barang: ");
    scanf("%d", &newNode->available);
    
    // Membersihkan buffer stdin setelah membaca integer
    while (getchar() != '\n');
    
//    newNode->number = ++list->lastNumber; // Assign a unique sequential number to the new node
    
    newNode->next = NULL; // Set the next pointer to NULL
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
    if (fprintf(file, "%d|%s|%s|%.2f|%d\n", newNode->number, newNode->info, newNode->detail, newNode->price, newNode->available) < 0) {
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
//    char name[100];
//    printf("Masukkan nama barang: ");
//    while (getchar() != '\n'); // Clear input buffer
//    fgets(name, sizeof(name), stdin);
//    strtok(name, "\n"); // Remove newline character if present

	int number;
	printf("Masukkan no barang: ");
	scanf("%d", &number);

    Node *found = search(list, number);
//    Node *found = NULL;
    Node *current = list->head;
    while (current != NULL) {
        if (current->number == number) {
            found = current;
            break;
        }
        current = current->next;
    }
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
        sscanf(line, "%d|%[^|]|%[^|]|%f|%d", &temp.number, temp.info, temp.detail, &temp.price, &temp.available);
        if (temp.number == number) {
            fprintf(tempFile, "%d|%s|%s|%.2f|%d\n", found->number, found->info, found->detail, found->price, found->available);
        } else {
            fprintf(tempFile, "%d|%s|%s|%.2f|%d\n", temp.number, temp.info, temp.detail, temp.price, temp.available);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the updated file
    remove("jualan.txt");
    rename("temp.txt", "jualan.txt");
}


void deleteItem(List *list) {
//	char name[100];
//    printf("Masukkan nama barang yang ingin dihapus: ");
//    while (getchar() != '\n'); // Clear input buffer
//    fgets(name, sizeof(name), stdin);
//    strtok(name, "\n");
    int number;
    printf("Masukkan no barang yang ingin dihapus: ");
    scanf("%d", &number);
    
    Node *current = list->head;
    Node *previous = NULL;
    while (current != NULL && current->number != number) {
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
    
    // Memperbaharui no dari barang
    current = list->head;
    int newNumber = 1; // newNumber dimulai dari 1
    while (current != NULL) {
        current->number = newNumber++;
        current = current->next;
    }

    // Rewrite the file without the deleted item
    FILE *file = fopen("jualan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    current = list->head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n", current->number, current->info, current->detail, current->price, current->available);
        current = current->next;
    }
    fclose(file);

    printf("Barang berhasil dihapus.\n");
}

void writefile(List *list) {
    FILE *file = fopen("jualan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n", current->number, current->info, current->detail, current->price, current->available);
        current = current->next;
    }

    fclose(file);
}

void readfile(List *list) {
    FILE *file = fopen("jualan.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        sscanf(line, "%d|%[^|]|%[^|]|%f|%d", &newNode->number, newNode->info, newNode->detail, &newNode->price, &newNode->available);
        newNode->next = NULL;

        if (list->head == NULL) {
            list->head = newNode;
            list->tail = newNode;
        } else {
            list->tail->next = newNode;
            list->tail = newNode;
        }
        // Update the lastNumber to the highest number found in the file
//        if (newNode->number > list->lastNumber) {
//            list->lastNumber = newNode->number;
//        }
    }

    fclose(file);
}
