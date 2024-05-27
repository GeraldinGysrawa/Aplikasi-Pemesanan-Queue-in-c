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
	    gotoxy(i+10, 16); printf("|                      [1]REGISTER          [2]LOGIN         [3]EXIT                              |\n");
	    gotoxy(i+10, 17); printf("  																								 \n");
	    gotoxy(i+10, 18); printf("|=================================================================================================|\n\n");
	    gotoxy(i+50, 19); printf("Masukkan pilihan Anda:         ");
	    scanf("%d", &choice);
        fflush(stdin);

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
                return 0;
            default:
	            puts("\nINVALID !! PLEASE INSERT THE RIGHT CHOOSE\n");
				system("pause");
				system("cls");
				break;
        }
    }while (choice != 2);

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
    	int i = 43;
    	system("cls");
	    gotoxy(i + 50, 1); printf("=================================\n");
	    gotoxy(i+ 50, 2); printf("|           M E N U             |\n");
	    gotoxy(i+ 50, 3); printf("=================================\n");
	    gotoxy(i+ 50, 4); printf("|1. Tampilkan Barang yang Dijual|\n");
	    gotoxy(i+ 50, 5);printf("|2. Beli Barang                  |\n");
	    gotoxy(i+ 50, 6);printf("|3. Keluar                       |\n");
	    gotoxy(i+ 50, 7);printf("=================================\n");
	    gotoxy(i+ 50, 8);printf("Pilih:         \n");
	    gotoxy(i+ 57, 8);scanf("%d", &choice);
	    
        switch (choice) {
            case 1:
//            	system("cls");
                disList(&barangList);
                break;
            case 2:
//            	system("cls");
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
