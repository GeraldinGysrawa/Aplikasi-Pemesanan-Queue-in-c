#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"


void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

address createNode(const char *namapembeli, const char *namabarang, int qty, Identitas identitas) {
    address newNode = (address)malloc(sizeof(listBarang));
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

int isValidItem(List *list, const char *name) {
    return cari(list, name) != NULL;
}


void enqueue(Queue *q, address newNode) {
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
    char namabarang[100];
    int qty;
    Identitas identitas;
    
    printf("Masukan Nama Anda: ");
    while (getchar() != '\n');
    fgets(namapembeli, sizeof(namapembeli), stdin);
    strtok(namapembeli, "\n"); 

    // Input valid item name
    do {
        printf("Masukan nama barang yang ingin di beli: ");
        fgets(namabarang, sizeof(namabarang), stdin);
        strtok(namabarang, "\n"); // Remove newline character if present
        if (!isValidItem(list, namabarang)) {
            printf("Nama barang tidak valid. Silakan coba lagi.\n");
        }
    } while (!isValidItem(list, namabarang));

    // Input valid quantity
    Node *itemNode = cari(list, namabarang);
    do {
        printf("Masukan jumlah barang yang ingin dibeli: ");
        scanf("%d", &qty);
        if (qty > itemNode->available) {
            printf("Stok barang tidak cukup. Silakan masukkan jumlah yang lebih kecil.\n");
        }
        // Membersihkan buffer stdin
        while (getchar() != '\n');
    } while (qty > itemNode->available);

    // Verifikasi pembelian
    printf("Anda akan membeli barang '%s' sebanyak %d dengan total harga %.2f. Apakah Anda yakin? (y/n):  \n", namabarang, qty, qty * itemNode->price);
    char confirm;
    scanf(" %c", &confirm);
    
    
	// Membersihkan buffer stdin
	while (getchar() != '\n'); 

    if (confirm == 'y' || confirm == 'Y') {
        while (getchar() != '\n'); 
        printf("Masukan alamat rumah anda: ");
        fgets(identitas.alamatrumah, sizeof(identitas.alamatrumah), stdin);
        strtok(identitas.alamatrumah, "\n"); 

        printf("Masukan email anda: ");
        fgets(identitas.alamatemail, sizeof(identitas.alamatemail), stdin);
        strtok(identitas.alamatemail, "\n"); 

        printf("Masukan No telepon anda: ");
        scanf("%d", &identitas.notelp);
        // Membersihkan buffer stdin
        while (getchar() != '\n'); 

        itemNode->available -= qty;
        writefile(list);

        address newNode = createNode(namapembeli, namabarang, qty, identitas);
        if (newNode != NULL) {
            enqueue(q, newNode);
        }
    } else {
        printf("Pembelian dibatalkan.\n");
    }
}

void saveToFile(address node) {
	FILE *history = fopen("history.txt", "a");
	if (history == NULL) {
		printf("Error opening file!\n");
		return;
	}
	
	fprintf(history, "Nama Pembeli: %s\n", node->namapembeli);
    fprintf(history, "Nama Barang: %s\n", node->namabarang);
    fprintf(history, "Jumlah: %d\n", node->qty);
    fprintf(history, "Alamat Rumah: %s\n", node->identitas.alamatrumah);
    fprintf(history, "Alamat Email: %s\n", node->identitas.alamatemail);
    fprintf(history, "No. Telepon: %d\n", node->identitas.notelp);
    fprintf(history, "\n");
    
    fclose(history);
	
    FILE *file = fopen("pembeli.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char encryptedAlamat[100];
    char encryptedEmail[100];

    strcpy(encryptedAlamat, node->identitas.alamatrumah);
    strcpy(encryptedEmail, node->identitas.alamatemail);

    enkripsiceasar(encryptedAlamat, 7);
    enkripsiceasar(encryptedEmail, 7);

    fprintf(file, "Nama Pembeli: %s\n", node->namapembeli);
    fprintf(file, "Nama Barang: %s\n", node->namabarang);
    fprintf(file, "Jumlah: %d\n", node->qty);
    fprintf(file, "Alamat Rumah: %s\n", encryptedAlamat);
    fprintf(file, "Alamat Email: %s\n", encryptedEmail);
    fprintf(file, "No. Telepon: %d\n", node->identitas.notelp);
    fprintf(file, "\n");

    fclose(file);
}

