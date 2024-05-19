//user.c
#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "dhea.h"
#include <stdbool.h>

int loginuser() {
    int num;
    int in = 0;
    bool loggedIn = true;
	
    do {
        system("cls");
        system("color 3F");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t     SELAMAT DATANG DI APLIKASI\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t1. Register\n");
        printf("\t\t\t\t2. Login\n");
        printf("\t\t\t\t3. Exit\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\tPilihan Anda: ");
        scanf("%d", &num);

        switch(num) {
            case 1:
                Register(in);
                break;
            case 2:
                Login(); // Mengirimkan alamat variabel loggedIn agar dapat diubah di dalam fungsi
                break;
            case 3:
				return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
        if (loggedIn) {
            user();
            loggedIn = false;
        }
    } while (num != 3);

    return 0;
}

int user() {
    List barangList;
    barangList.head = NULL;
    barangList.tail = NULL;

    Queue pembeliQueue;
    pembeliQueue.front = NULL;
    pembeliQueue.rear = NULL;

    // Load barang from file
    readfile(&barangList);

    int choice;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Tampilkan Barang yang Dijual\n");
        printf("2. Beli Barang\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                disList(&barangList);
                break;
            case 2:
            	disList(&barangList);
                belibarang(&pembeliQueue, &barangList);
                break;
            case 3:
                printf("Keluar dari program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);

    // Clean up allocated memory
    clearList(&barangList);

    return 0;
}
