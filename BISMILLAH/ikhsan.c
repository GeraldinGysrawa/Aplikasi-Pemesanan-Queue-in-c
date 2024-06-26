#include "ikhsan.h"
#include "geraldin.h"
#include "rizky.h"
#include "annisa.h"


Node* searchjual(List *list, const char *name) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->info, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void readFileToQueue(Queue *q) {
    FILE *file = fopen("pembeli.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    while (!feof(file)) {
        address newNode = (address)malloc(sizeof(listBarang));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        fscanf(file, "Nama Pembeli: %[^\n]\n", newNode->namapembeli);
        fscanf(file, "Nama Barang: %[^\n]\n", newNode->namabarang);
        fscanf(file, "Jumlah: %d\n", &newNode->qty);
        fscanf(file, "Alamat Rumah: %[^\n]\n", newNode->identitas.alamatrumah);
        fscanf(file, "Alamat Email: %[^\n]\n", newNode->identitas.alamatemail);
        fscanf(file, "No. Telepon: %d\n\n", &newNode->identitas.notelp);

        newNode->next = NULL;

        if (q->rear == NULL) {
            q->front = newNode;
            q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }

    fclose(file);
}


void displayPembeli(Queue *q) {
    system("cls");
    if (q->front == NULL) {
        printf("Antrian pembeli kosong.\n");
        return;
    }

    printf("====================================================================\n");
    printf("| %-20s | %-25s | %-15s |\n", "Nama Pembeli", "Barang yang Dibeli", "Jumlah Barang");
    printf("====================================================================\n");

    address current = q->front;
    while (current != NULL) {
        printf("| %-20s | %-25s | %-15d |\n", current->namapembeli, current->namabarang, current->qty);
        current = current->next;
    }

    printf("====================================================================\n");

    char option;
    printf("Apakah Anda ingin mencetak pesanan dari node pertama? (y/n): ");
    scanf(" %c", &option);

    if (option == 'y' || option == 'Y') {
        address firstNode = q->front;

        char decryptedAlamat[500];
        char decryptedEmail[100];

        strcpy(decryptedAlamat, firstNode->identitas.alamatrumah);
        strcpy(decryptedEmail, firstNode->identitas.alamatemail);

        dekripsiceasar(decryptedAlamat, 7);
        dekripsiceasar(decryptedEmail, 7);

        printf("\n");
        printf("=================================================================\n");
        printf("|                      STRUK PENGIRIMAN                          |\n");
        printf("=================================================================\n");
        printf("| %-30s: %-30s |\n", "Nama Pembeli", firstNode->namapembeli);
        printf("| %-30s: %-30s |\n", "Nama Barang", firstNode->namabarang);
        printf("| %-30s: %-30d |\n", "Jumlah Barang", firstNode->qty);
        printf("| %-30s: %-30s |\n", "Alamat Rumah", firstNode->identitas.alamatrumah);
        printf("| %-30s: %-30s |\n", "Alamat Email", firstNode->identitas.alamatemail);
        printf("| %-30s: %-30d |\n", "No. Telepon", firstNode->identitas.notelp);
        printf("=================================================================\n");
        printf("|                   TERIMA KASIH ATAS PESANAN ANDA!              |\n");
        printf("|                Silakan kunjungi kami lagi!                     |\n");
        printf("=================================================================\n");

        // Menghapus node pertama dari antrian (memperbarui antrian)
        removeFromQueue(q);

        // Membersihkan buffer stdin dari karakter newline yang tersisa
        while (getchar() != '\n');

        // Tanyakan apakah ingin mencetak lagi
        printf("Apakah Anda ingin mencetak pesanan lagi? (y/n): ");
        scanf(" %c", &option);
        if (option == 'y' || option == 'Y') {
            // Jika ya, panggil fungsi displayPembeli kembali
            displayPembeli(q);
        }
        // Jika tidak, kembali ke menu utama tanpa menampilkan daftar pembeli lagi
        return;
    }
}



void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Antrian pembeli kosong.\n");
        return;
    }

    // Simpan data node yang akan didequeue
    address temp = q->front;

    // Pindahkan pointer front ke node berikutnya
    q->front = q->front->next;

    // Jika setelah dequeue front menjadi NULL, artinya antrian kosong, rear juga perlu diubah menjadi NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Bebaskan memori yang digunakan oleh node yang didequeue
    free(temp);
}


void updateFile(Queue *q) {
    // Buka file untuk menulis data yang telah diperbarui
    FILE *file = fopen("pembeli.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Tulis ulang data antrian ke file asli
    address current = q->front;
    while (current != NULL) {
        fprintf(file, "Nama Pembeli: %s\n", current->namapembeli);
        fprintf(file, "Nama Barang: %s\n", current->namabarang);
        fprintf(file, "Jumlah: %d\n", current->qty);
        fprintf(file, "Alamat Rumah: %s\n", current->identitas.alamatrumah);
        fprintf(file, "Alamat Email: %s\n", current->identitas.alamatemail);
        fprintf(file, "No. Telepon: %d\n\n", current->identitas.notelp);
        current = current->next;
    }

    // Tutup file setelah selesai menulis
    fclose(file);
}


void copyFileContents(const char *sourceFile, const char *destinationFile) {
    FILE *source = fopen(sourceFile, "r");
    FILE *destination = fopen(destinationFile, "w");
    if (source == NULL || destination == NULL) {
        printf("Gagal membuka file.\n");
        if (source != NULL) fclose(source);
        if (destination != NULL) fclose(destination);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), source) != NULL) {
        fputs(line, destination);
    }

    fclose(source);
    fclose(destination);
}


void deleteTempFile(const char *filename) {
    if (remove(filename) != 0) {
        printf("Gagal menghapus file sementara.\n");
    }
}




void removeFromQueue(Queue *q) {
    dequeue(q);
    updateFile(q);
    copyFileContents("pembeli.txt", "pembeli_temp.txt");
    deleteTempFile("pembeli_temp.txt");

    printf("Pembeli telah dikeluarkan dari antrian dan file telah diperbarui.\n");
}




//void dequeue(Queue *q) {
//    if (q->front == NULL) {
//        printf("Antrian pembeli kosong.\n");
//        return;
//    }
//
//    // Simpan data node yang akan didequeue
//    listBarang *temp = q->front;
//
//    // Pindahkan pointer front ke node berikutnya
//    q->front = q->front->next;
//
//    // Jika setelah dequeue front menjadi NULL, artinya antrian kosong, rear juga perlu diubah menjadi NULL
//    if (q->front == NULL) {
//        q->rear = NULL;
//    }
//
//    // Buka file untuk menulis data yang telah diperbarui
//    FILE *file = fopen("pembeli.txt", "w");
//    if (file == NULL) {
//        printf("Gagal membuka file.\n");
//        return;
//    }
//
//    // Salin isi file asli (pembeli.txt) ke file sementara (pembeli_temp.txt)
//    FILE *fileTemp = fopen("pembeli_temp.txt", "w");
//    if (fileTemp == NULL) {
//        printf("Gagal membuat file sementara.\n");
//        fclose(file);
//        return;
//    }
//
//    // Baca dan salin isi file asli ke file sementara
//    char line[100];
//    while (fgets(line, sizeof(line), file) != NULL) {
//        fputs(line, fileTemp);
//    }
//
//    // Tutup file sementara
//    fclose(fileTemp);
//
//    // Buka file sementara untuk membaca data antrian yang belum didequeue
//    fileTemp = fopen("pembeli_temp.txt", "r");
//    if (fileTemp == NULL) {
//        printf("Gagal membuka file sementara.\n");
//        fclose(file);
//        return;
//    }
//
//    // Tulis ulang data antrian ke file asli, kecuali node pertama yang baru saja didequeue
//    listBarang *current = q->front;
//    while (current != NULL) {
//        fprintf(file, "Nama Pembeli: %s\n", current->namapembeli);
//        fprintf(file, "Nama Barang: %s\n", current->namabarang);
//        fprintf(file, "Jumlah: %d\n", current->qty);
//        fprintf(file, "Alamat Rumah: %s\n", current->identitas.alamatrumah);
//        fprintf(file, "Alamat Email: %s\n", current->identitas.alamatemail);
//        fprintf(file, "No. Telepon: %d\n\n", current->identitas.notelp);
//        current = current->next;
//    }
//
//    // Tutup kedua file setelah selesai menulis
//    fclose(file);
//    fclose(fileTemp);
//
//    // Hapus file sementara
//    remove("pembeli_temp.txt");
//
//    // Bebaskan memori yang digunakan oleh node yang didequeue
//    free(temp);
//
//    printf("Pembeli telah dikeluarkan dari antrian dan file telah diperbarui.\n");
//}

