#include "annisa.h"
//main.c
#include "dhea.h"
#include "geraldin.h"
#include "ikhsan.h"
#include "rizky.h"


int main() {
    int choice;

    // Menampilkan menu utama
    printf("Menu Utama\n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &choice);

    // Menggunakan switch case untuk menangani pilihan
    switch (choice) {
        case 1:
            loginadmin();
            break;
        case 2:
            loginuser();
            break;
        default:
            printf("Pilihan tidak valid!\n");
            break;
    }

    return 0;
}
