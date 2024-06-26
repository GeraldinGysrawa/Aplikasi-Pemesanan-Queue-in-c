#include "ikhsan.h"
#include "geraldin.h"
#include "rizky.h"
#include "annisa.h"


// Fungsi untuk membaca file dan mengisi antrian
void readFileToQueue(Queue *q) {
    FILE *file = fopen("pembeli.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        address newNode = (address)malloc(sizeof(listBarang));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        sscanf(buffer, "Nama Pembeli: %[^\n]\n", newNode->namapembeli);
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Nama Barang: %[^\n]\n", newNode->namabarang);
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Jumlah: %d\n", &newNode->qty);
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Alamat Rumah: %[^\n]\n", newNode->identitas.alamatrumah);
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "Alamat Email: %[^\n]\n", newNode->identitas.alamatemail);
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "No. Telepon: %[^\n]\n", newNode->identitas.notelp);
        fgets(buffer, sizeof(buffer), file);  // To consume the empty line

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

// Fungsi untuk menampilkan antrian pembeli
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
        char decryptedNoTelp[100];

        strcpy(decryptedAlamat, firstNode->identitas.alamatrumah);
        strcpy(decryptedEmail, firstNode->identitas.alamatemail);
        strcpy(decryptedNoTelp, firstNode->identitas.notelp);

        dekripsiceasar(decryptedAlamat, 7);
        dekripsiceasar(decryptedEmail, 7);
        dekripsiangka(decryptedNoTelp, 7);

        printf("\n");
        printf("=================================================================\n");
        printf("|                      STRUK PENGIRIMAN                          |\n");
        printf("=================================================================\n");
        printf("| %-30s: %-30s |\n", "Nama Pembeli", firstNode->namapembeli);
        printf("| %-30s: %-30s |\n", "Nama Barang", firstNode->namabarang);
        printf("| %-30s: %-30d |\n", "Jumlah Barang", firstNode->qty);
        printf("| %-30s: %-30s |\n", "Alamat Rumah", decryptedAlamat);
        printf("| %-30s: %-30s |\n", "Alamat Email", decryptedEmail);
        printf("| %-30s: %-30s |\n", "No. Telepon", decryptedNoTelp);
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

// Fungsi untuk menghapus elemen dari antrian
void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Antrian pembeli kosong.\n");
        return;
    }

    // Simpan data node yang akan didequeue
    listBarang *temp = q->front;

    // Pindahkan pointer front ke node berikutnya
    q->front = q->front->next;

    // Jika setelah dequeue front menjadi NULL, artinya antrian kosong, rear juga perlu diubah menjadi NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // Bebaskan memori yang digunakan oleh node yang didequeue
    free(temp);
}

// Fungsi untuk memperbarui file setelah perubahan pada antrian
void updateFile(Queue *q) {
    // Buka file untuk menulis data yang telah diperbarui
    FILE *file = fopen("pembeli.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Tulis ulang data antrian ke file asli
    listBarang *current = q->front;
    while (current != NULL) {
        fprintf(file, "Nama Pembeli: %s\n", current->namapembeli);
        fprintf(file, "Nama Barang: %s\n", current->namabarang);
        fprintf(file, "Jumlah: %d\n", current->qty);
        fprintf(file, "Alamat Rumah: %s\n", current->identitas.alamatrumah);
        fprintf(file, "Alamat Email: %s\n", current->identitas.alamatemail);
        fprintf(file, "No. Telepon: %s\n\n", current->identitas.notelp);
        current = current->next;
    }

    // Tutup file setelah selesai menulis
    fclose(file);
}

// Fungsi untuk menyalin isi file dari satu file ke file lain
void copyFileContents(const char *sourceFile, const char *destinationFile) {
    FILE *source = fopen(sourceFile, "r");
    FILE *destination = fopen(destinationFile, "w");
    if (source == NULL || destination == NULL) {
        printf("Gagal membuka file.\n");
        if (source != NULL) fclose(source);
        if (destination != NULL) fclose(destination);
        return;
    }

    // Salin isi file baris demi baris
    char line[100];
    while (fgets(line, sizeof(line), source) != NULL) {
        fputs(line, destination);
    }

    fclose(source);
    fclose(destination);
}

// Fungsi untuk menghapus file sementara
void deleteTempFile(const char *filename) {
    if (remove(filename) != 0) { // Periksa apakah file berhasil dihapus
        printf("Gagal menghapus file sementara.\n"); // Cetak pesan kesalahan jika file tidak bisa dihapus
    }
}

// Fungsi utama yang menghapus elemen dari antrian dan memperbarui file
void removeFromQueue(Queue *q) {
    // Buat salinan sementara terlebih dahulu
    copyFileContents("pembeli.txt", "pembeli_temp.txt");

    // Hapus elemen pertama dari antrian
    if (q->front == NULL) {
        printf("Antrian pembeli kosong, tidak ada yang dihapus.\n");
        // Hapus file sementara karena tidak ada perubahan yang dilakukan
        deleteTempFile("pembeli_temp.txt");
        return;
    }

    dequeue(q);

    // Perbarui file pembeli.txt dengan data antrian

    if (q->front != NULL) {
        // Jika ada data yang akan ditulis ke file, maka update file
        updateFile(q);
        // Hapus file sementara hanya jika pembaruan file berhasil
        deleteTempFile("pembeli_temp.txt");
    } else {
        // Jika antrian kosong setelah dequeue, maka hapus isi file utama
        FILE *file = fopen("pembeli.txt", "w");
        if (file != NULL) {
            fclose(file);
            deleteTempFile("pembeli_temp.txt");
        } else {
            printf("Gagal membuka file untuk mengosongkan isinya.\n");
        }
    }
}

// // Fungsi untuk menghapus elemen dari antrian dan memperbarui file
// void removeFromQueue(Queue *q) {
//     dequeue(q); // Hapus elemen dari antrian
//     updateFile(q); // Perbarui file dengan antrian yang telah diubah
//     copyFileContents("pembeli.txt", "pembeli_temp.txt"); // Salin isi file ke file sementara
//     deleteTempFile("pembeli_temp.txt"); // Hapus file sementara

//     // Cetak pesan bahwa pembeli telah dikeluarkan dan file diperbarui
//     printf("Pembeli telah dikeluarkan dari antrian dan file telah diperbarui.\n");
// }