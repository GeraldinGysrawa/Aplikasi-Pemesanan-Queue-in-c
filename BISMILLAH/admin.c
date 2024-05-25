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
        int i = 43;
        gotoxy(i, 1); printf("=================================\n");
	    gotoxy(i, 2); printf("|       M E N U  A D M I N      |\n");
	    gotoxy(i, 3); printf("=================================\n");
	    gotoxy(i, 4); printf("|1. Register                    |\n");
	    gotoxy(i, 5); printf("|2. Login                       |\n");
	    gotoxy(i, 6); printf("|3. Kembali ke menu utama       |\n");
	    gotoxy(i, 7); printf("|Masukkan pilihan Anda:         |\n");
	    gotoxy(i, 8); printf("=================================\n");
	    gotoxy(i + 27, 7);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                Register(index, isAdmin);
                break;
            case 2:
                if (Login(isAdmin)) {
                    printf("Login berhasil!\n");
                    system("cls");
                    admin();
                } else {
                    printf("Login gagal\n");
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
        system("cls");
    	int i = 43;
	    gotoxy(i, 1); printf("=================================\n");
	    gotoxy(i, 2); printf("|           M E N U             |\n");
	    gotoxy(i, 3); printf("=================================\n");
	    gotoxy(i, 4); printf("|1. Kelola Barang               |\n");
	    gotoxy(i, 5);printf("|2. Tampilkan Daftar Pembeli    |\n");
	    gotoxy(i, 6); printf("|3. Kelola History              |\n");
	    gotoxy(i, 7);printf("|4. Keluar                      |\n");
	    gotoxy(i, 8);printf("=================================\n");
	    gotoxy(i, 9);printf("Pilih:         \n");
	    gotoxy(i + 8, 9);scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                	int i = 43;
                	system("cls");
				    gotoxy(i + 50, 7); printf("=================================\n");
				    gotoxy(i + 50, 8); printf("|         KELOLA BARANG         |\n");
				    gotoxy(i + 50, 9); printf("=================================\n");
				    gotoxy(i + 50, 10); printf("|1. Tambah Barang               |\n");
				    gotoxy(i + 50, 11);printf("|2. Tambah Stok Barang          |\n");
				    gotoxy(i + 50, 12);printf("|3. Hapus Barang                |\n");
				    gotoxy(i + 50, 13);printf("|4. Lihat Barang yang Ada       |\n");
				    gotoxy(i + 50, 14);printf("|5. Kembali ke Menu Utama       |\n");
				    gotoxy(i + 50, 15);printf("=================================\n");
				    gotoxy(i + 50, 16);printf("Pilih:         \n");
				    gotoxy(i + 57, 16);scanf("%d", &choice);

                    switch (choice) {
                        case 1:
//                        	system("cls");
                            insert(&barangList);
                            break;
                        case 2:
//                        	system("cls");
                            disList(&barangList);
                            addStock(&barangList);
                            break;
                        case 3:
//                        	system("cls");
                            disList(&barangList);
                            deleteItem(&barangList);
                            break;
                        case 4:
//                        	system("cls");
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
            	history(&pembeliQueue);
            	break;
            case 4:
                printf("Keluar dari program.\n");
                return 0;
            	default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 4);
    clearList(&barangList);

    return 0;
}

