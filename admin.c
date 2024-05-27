//admin.c
#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "ikhsan.h"
#include "dhea.h"
#include <stdbool.h>

void adminMenu() {
	int i;
	i = 23;	
    int choice;
    bool isAdmin = true;
    int index = 0;

    do {
        system("cls");
        int i = 15;
        gotoxy(i,5);  printf(" *######*   #######  *#####*      *##*      ##       *#####*       *#####+   ########   *######*    *#####*     #######    \n");
		gotoxy(i,6);  printf(" ##         ##       ##    ##    *#   #*    ##       ##    #*      ##    ##     ##     *#      #*   ##    ##     ##        \n");
		gotoxy(i,7);  printf(" ##         ##       ##    ##   *#     #*   ##       ##     #*     ##           ##    *#        #*  ##    ##     ##		\n");
		gotoxy(i,8);  printf(" **####*    *####    *#####*   *# ===== #*  ##       ##      #*     *#### *     ##   *#          #*  *#####*     *####     \n");
		gotoxy(i,9);  printf(" ##     ##  ##       ##  ##    ##       ##  ##       ##     *#           ##     ##    *#        #*   ##  ##      ##        \n");
		gotoxy(i,10); printf(" ##     ##  ##       ##   ##   ##       ##  ##       ##    *#      ##    ##     ##     *#      #*    ##   ##     ##        \n");
		gotoxy(i,11); printf(" *#####*    #######  ##    ##  ##       ##  #######  *####*#       +#####*      ##      *#####*      ##    ##    #######   \n");
		gotoxy(i+10, 14); printf("|=================================================================================================|\n");
	    gotoxy(i+10, 15); printf("												     												 \n");
	    gotoxy(i+10, 16); printf("|                                [1]LOGIN                 [2]BACK                                 |\n");
	    gotoxy(i+10, 17); printf("  																								 \n");
	    gotoxy(i+10, 18); printf("|=================================================================================================|\n\n");
	    gotoxy(i+50, 19); printf("Masukkan pilihan Anda:         ");
	    scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
                if (LoginAdmin()) {
                    printf("Login berhasil!\n");
                    system("cls");
                    admin();
                } else {
                    printf("Login gagal\n");
                }
                getchar(); // To pause the screen
                getchar(); // To pause the screen
                break;
            case 2:
            	system("cls");
            	judul2();
                return 0;
            default:
	            puts("\nINVALID !! PLEASE INSERT THE RIGHT CHOOSE\n");
				system("pause");
				system("cls");
				break;
        }
    }while (choice != 2);
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

