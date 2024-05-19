//user.c
#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "dhea.h"
#include <stdbool.h>


void userMenu() {
    int choice;
    bool isAdmin = false;
    int index = 0;

    while (1) {
        system("cls");
        printf("User Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Register(index, isAdmin);
                break;
            case 2:
                if (Login(isAdmin)) {
                    printf("User Login Successful\n");
                    user();
                } else {
                    printf("User Login Failed\n");
                }
                getchar(); // To pause the screen
                getchar(); // To pause the screen
                break;
            case 3:
                return;
            default:
                printf("Invalid choice\n");
                getchar(); // To pause the screen
                getchar(); // To pause the screen
        }
    }
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
