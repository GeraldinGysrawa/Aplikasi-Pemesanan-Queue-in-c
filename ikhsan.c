#include "ikhsan.h"
#include "geraldin.h"
#include "rizky.h"
#include "annisa.h"



// Fungsi untuk membaca file dan mengisi antrian
void readFileToQueue(Queue *q) {
    FILE *file = fopen("pembeli.txt", "r"); // Buka file untuk dibaca
    if (file == NULL) { // Periksa apakah file berhasil dibuka
        printf("Gagal membuka file.\n"); // Cetak pesan kesalahan jika file tidak bisa dibuka
        return;
    }

    while (!feof(file)) { // Lanjutkan sampai akhir file
        listBarang *newNode = (listBarang*)malloc(sizeof(listBarang)); // Alokasikan memori untuk node baru
        if (newNode == NULL) { // Periksa apakah alokasi memori berhasil
            printf("Gagal mengalokasikan memori.\n"); // Cetak pesan kesalahan jika alokasi gagal
            fclose(file); // Tutup file
            return;
        }

        // Baca data dari file dan simpan di node baru
        fscanf(file, "Nama Pembeli: %[^\n]\n", newNode->namapembeli);
        fscanf(file, "Nama Barang: %[^\n]\n", newNode->namabarang);
        fscanf(file, "Jumlah: %d\n", &newNode->qty);
        fscanf(file, "Alamat Rumah: %[^\n]\n", newNode->identitas.alamatrumah);
        fscanf(file, "Alamat Email: %[^\n]\n", newNode->identitas.alamatemail);
        fscanf(file, "No. Telepon: %d\n\n", &newNode->identitas.notelp);

        newNode->next = NULL; // Setel pointer next dari node baru ke NULL

        if (q->rear == NULL) { // Periksa apakah antrian kosong
            q->front = newNode; // Jika ya, setel front dan rear ke node baru
            q->rear = newNode;
        } else {
            q->rear->next = newNode; // Jika tidak, tambahkan node baru ke akhir antrian
            q->rear = newNode;
        }
    }

    fclose(file); // Tutup file setelah selesai
}


// Fungsi untuk menampilkan antrian pembeli
void displayPembeli(Queue *q) {
    system("cls"); // Bersihkan layar
    if (q->front == NULL) { // Periksa apakah antrian kosong
        printf("Antrian pembeli kosong.\n"); // Cetak pesan jika antrian kosong
        return;
    }

    // Cetak header tabel
    printf("====================================================================\n");
    printf("| %-20s | %-25s | %-15s |\n", "Nama Pembeli", "Barang yang Dibeli", "Jumlah Barang");
    printf("====================================================================\n");

    // Cetak setiap elemen antrian
    listBarang *current = q->front;
    while (current != NULL) {
        printf("| %-20s | %-25s | %-15d |\n", current->namapembeli, current->namabarang, current->qty);
        current = current->next;
    }

    printf("====================================================================\n");

    // Tanya apakah ingin mencetak pesanan dari node pertama
    char option;
    printf("Apakah Anda ingin mencetak pesanan dari node pertama? (y/n): ");
    scanf(" %c", &option);

    if (option == 'y' || option == 'Y') {
        listBarang *firstNode = q->front;

        char decryptedAlamat[500];
        char decryptedEmail[100];

        strcpy(decryptedAlamat, firstNode->identitas.alamatrumah);
        strcpy(decryptedEmail, firstNode->identitas.alamatemail);

        dekripsiceasar(decryptedAlamat, 7);
        dekripsiceasar(decryptedEmail, 7);

        // Cetak struk pengiriman
        printf("\n");
        printf("==============================================================\n");
        printf("|                      STRUK PENGIRIMAN                      |\n");
        printf("==============================================================\n");
        printf("| %-30s: %-30s |\n", "Nama Pembeli", firstNode->namapembeli);
        printf("| %-30s: %-30s |\n", "Nama Barang", firstNode->namabarang);
        printf("| %-30s: %-30d |\n", "Jumlah Barang", firstNode->qty);
        printf("| %-30s: %-30s |\n", "Alamat Rumah", firstNode->identitas.alamatrumah);
        printf("| %-30s: %-30s |\n", "Alamat Email", firstNode->identitas.alamatemail);
        printf("| %-30s: %-30d |\n", "No. Telepon", firstNode->identitas.notelp);
        printf("==============================================================\n");
        printf("|                   TERIMA KASIH ATAS PESANAN ANDA!                |\n");
        printf("|                Silakan kunjungi kami lagi!                      |\n");
        printf("==============================================================\n");

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
        fprintf(file, "No. Telepon: %d\n\n", current->identitas.notelp);
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

    // Perbarui file pembeli.txt dengan data antrian yang baru
    if (q->front != NULL) {
        // Jika ada data yang akan ditulis ke file, maka update file
        updateFile(q);
        // Hapus file sementara hanya jika pembaruan file berhasil
        deleteTempFile("pembeli_temp.txt");
    } else {
        // Jika antrian kosong setelah dequeue, maka jadikan file sementara sebagai file utama
        if (rename("pembeli_temp.txt", "pembeli.txt") != 0) {
            printf("Gagal mengganti file asli dengan file sementara.\n");
            // Jika gagal, tetap gunakan file sementara sebagai file utama dan hapus file sementara
            printf("File sementara akan tetap digunakan sebagai file utama.\n");
        } else {
            printf("File sementara telah menjadi file utama.\n");
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



