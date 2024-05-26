#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "dhea.h"
#include "global.h"
#include <ctype.h>


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
    int nomorBarang;
    int qty;
    Identitas identitas;
    
    printf("Masukan Nama Anda: ");
    while (getchar() != '\n');  // Membersihkan buffer stdin
    fgets(namapembeli, sizeof(namapembeli), stdin);
    strtok(namapembeli, "\n"); 

    // Input valid item number
    Node *itemNode = NULL;
    do {
        printf("Masukan nomor barang yang ingin dibeli: ");
        scanf("%d", &nomorBarang);
        
        // Cari nomor barang dalam list
        Node *current = list->head;
        while (current != NULL) {
            if (current->number == nomorBarang) {
                itemNode = current;
                break;
            }
            current = current->next;
        }
        
        if (itemNode == NULL) {
            printf("Nomor barang tidak valid. Silakan coba lagi.\n");
        }
        
        // Membersihkan buffer stdin
        while (getchar() != '\n');
    } while (itemNode == NULL);

    // Input valid quantity
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
    printf("Anda akan membeli barang '%s' sebanyak %d dengan total harga %.2f. Apakah Anda yakin? (y/n):  ", itemNode->info, qty, qty * itemNode->price);
    char confirm;
    scanf(" %c", &confirm);
    
    // Membersihkan buffer stdin
    while (getchar() != '\n'); 

    if (confirm == 'y' || confirm == 'Y') {
        printf("Masukan alamat rumah anda: ");
        fgets(identitas.alamatrumah, sizeof(identitas.alamatrumah), stdin);
        strtok(identitas.alamatrumah, "\n"); 

        // email
        bool emailValidd = false;
        do {
            printf("Masukkan alamat email Anda (@gmail.com): ");
            scanf("%s", identitas.alamatemail);
            
            if (!emailValid(identitas.alamatemail)){
                printf("Alamat email tidak valid.\n");
            } else {
                emailValidd = true;
            }
        } while (!emailValidd);

        // Validasi nomor telepon
        bool isPhoneNumberValid = false;
        do {
            printf("Masukan No telepon anda: ");
            fgets(identitas.notelp, sizeof(identitas.notelp), stdin);
            strtok(identitas.notelp, "\n"); // Menghapus newline character dari input
            
            isPhoneNumberValid = true;
            for (int i = 0; identitas.notelp[i] != '\0'; i++) {
                if (!isdigit(identitas.notelp[i])) {
                    printf("Nomor telepon harus berupa angka. Silakan coba lagi.\n");
                    isPhoneNumberValid = false;
                    break;
                }
            }
        } while (!isPhoneNumberValid);

        itemNode->available -= qty;
        writefile(list);

        address newNode = createNode(namapembeli, itemNode->info, qty, identitas);
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
    fprintf(history, "No. Telepon: %s\n", node->identitas.notelp);
    fprintf(history, "\n");
    
    fclose(history);

    FILE *file = fopen("pembeli.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char encryptedAlamat[100];
    char encryptedEmail[100];
    char encryptedNoTelp[100];

    // Enkripsi alamat rumah, alamat email, dan nomor telepon
    strcpy(encryptedAlamat, node->identitas.alamatrumah);
    strcpy(encryptedEmail, node->identitas.alamatemail);
    strcpy(encryptedNoTelp, node->identitas.notelp); 
    
    enkripsiceasar(encryptedAlamat, 7);
    enkripsiceasar(encryptedEmail, 7);
    enkripsiangka(encryptedNoTelp, 7);


    // Simpan ke file
    fprintf(file, "Nama Pembeli: %s\n", node->namapembeli);
    fprintf(file, "Nama Barang: %s\n", node->namabarang);
    fprintf(file, "Jumlah: %d\n", node->qty);
    fprintf(file, "Alamat Rumah: %s\n", encryptedAlamat);
    fprintf(file, "Alamat Email: %s\n", encryptedEmail);
    fprintf(file, "No. Telepon: %s\n", encryptedNoTelp);
    fprintf(file, "\n");

    fclose(file);
}



void enkripsiangka(char *num, int key){
    for (int i = 0; num[i] != '\0'; i++) {
        if (num[i] >= '0' && num[i] <= '9'){
            num[i] = '0' + ((num[i] - '0' + key) % 10);
        }
    }
}

void dekripsiangka(char *num, int key){
    for (int i = 0; num[i] != '\0'; i++){
        if (num[i] >= '0' && num[i] <= '9'){
            num[i] = '0' + ((num[i] - '0' - key + 10) % 10);
        }
    }
}


