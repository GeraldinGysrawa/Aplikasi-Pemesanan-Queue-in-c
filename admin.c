//admin.c
#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "ikhsan.h"
#include "dhea.h"
#include <stdbool.h>

void adminMenu() {
    int choice;
    bool isAdmin = true;
    int index = 0;

    while (1) {
        system("cls");
        printf("Admin Menu:\n");
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
                    printf("Admin Login Successful\n");
                    system("cls");
                    admin();
                } else {
                    printf("Admin Login Failed\n");
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
int admin() {
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
        printf("1. Kelola barang\n");
        printf("2. Tampilkan daftar pembeli\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    printf("\n=== KELOLA BARANG ===\n");
                    printf("1. Tambah barang\n");
                    printf("2. Tambah stok barang\n");
                    printf("3. Hapus barang\n");
                    printf("4. Lihat barang yang ada ada\n");
                    printf("5. Kembali ke menu utama\n");
                    printf("Pilih: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            insert(&barangList);
                            break;
                        case 2:
                            disList(&barangList);
                            addStock(&barangList);
                            break;
                        case 3:
                            disList(&barangList);
                            deleteItem(&barangList);
                            break;
                        case 4:
                        	disList(&barangList);
                        	break;
                        case 5:
                            printf("Kembali ke menu utama.\n");
                            break;
                        default:
                            printf("Pilihan tidak valid. Silakan coba lagi.\n");
                    }
                } while (choice != 5);
                choice = 0; // Reset looping
                break;
            case 2:
            	if (pembeliQueue.front == NULL) {
       				 readFileToQueue(&pembeliQueue);
    			}
    			displayPembeli(&pembeliQueue);
                break;
            case 3:
                printf("Keluar dari program.\n");
                return 0;
            	default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
    clearList(&barangList);

    return 0;
}

