#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"

// Function definitions
void saveToFile(listBarang *node) {
    FILE *file = fopen("pembeli.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Buyer Name: %s\n", node->namapembeli);
    fprintf(file, "Item Name: %s\n", node->namabarang);
    fprintf(file, "Quantity: %d\n", node->qty);
    fprintf(file, "Home Address: %s\n", node->identitas.alamatrumah);
    fprintf(file, "Email Address: %s\n", node->identitas.alamatemail);
    fprintf(file, "Phone Number: %d\n", node->identitas.notelp);
    fprintf(file, "\n");

    fclose(file);
}
listBarang* createNode(const char *namapembeli, const char *namabarang, int qty, Identitas identitas) {
    listBarang *newNode = (listBarang*)malloc(sizeof(listBarang));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(newNode->namapembeli, namapembeli);
    strcpy(newNode->namabarang, namabarang);
    newNode->qty = qty;
    newNode->identitas = identitas;
    newNode->next = NULL;
    return newNode;
}

void enque(Queue *q, listBarang *newNode) {
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    newNode->next = NULL;
    saveToFile(newNode);
}

void belibarang(Queue *q, List *list) {
    char namapembeli[50];
    char namabarang[50];
    int qty;
    Identitas identitas;
    char confirm;

    printf("Enter buyer name: ");
    scanf("%s", namapembeli);

    // Input valid item name
    Node *itemNode;
    do {
        printf("Enter item name: ");
        scanf("%s", namabarang);
        itemNode = search(list, namabarang);
        if (itemNode == NULL) {
            printf("Nama barang tidak valid. Silakan coba lagi.\n");
        }
    } while (itemNode == NULL);

    // Input valid quantity
    do {
        printf("Enter quantity: ");
        scanf("%d", &qty);
        if (qty > itemNode->available) {
            printf("Stok barang tidak cukup. Silakan masukkan jumlah yang lebih kecil.\n");
        }
    } while (qty > itemNode->available);

    // Calculate total price
    float totalPrice = qty * itemNode->price;
    printf("Anda yakin ingin membeli barang '%s' dengan total harga %.2f? (y/n): ", namabarang, totalPrice);
    while (getchar() != '\n'); // Clear input buffer
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        printf("Enter home address: ");
        scanf("%s", identitas.alamatrumah);
        printf("Enter email address: ");
        scanf("%s", identitas.alamatemail);
        printf("Enter phone number: ");
        scanf("%d", &identitas.notelp);
        printf("Pemesanan anda sudah selesai.");

        // Update item stock
        itemNode->available -= qty;
        writefile(list);

        // Create and enqueue new node
        listBarang *newNode = createNode(namapembeli, namabarang, qty, identitas);
        if (newNode != NULL) {
            enque(q, newNode);
        }
    } else {
        printf("Pembelian dibatalkan.\n");
    }
}


int isValidItem(List *list, const char *name) {
    return search(list, name) != NULL;
}

void writefile(List *list) {
    FILE *file = fopen("jualan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        fprintf(file, "%s|%s|%.2f|%d\n", current->info, current->detail, current->price, current->available);
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

        sscanf(line, "%[^|]|%[^|]|%f|%d", newNode->info, newNode->detail, &newNode->price, &newNode->available);
        newNode->next = NULL;

        if (list->head == NULL) {
            list->head = newNode;
            list->tail = newNode;
        } else {
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }

    fclose(file);
}
