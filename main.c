#include "annisa.h"
//main.c
#include "dhea.h"
#include "geraldin.h"
#include "ikhsan.h"
#include "rizky.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

void SetColor(unsigned short);
int choice;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void loadingScreen() {
    int i;
    gotoxy(60, 10);
    printf("Loading...");
    gotoxy(60, 12);

    // Set warna untuk balok
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    for (i = 0; i <= 17; i++) {
        Sleep(90);
        printf("%c", 177);
    }
    printf("\n\n");
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); // Mengembalikan warna default
    system("pause");
    system("cls");
}

void judul(){
	int i = 0;
	gotoxy(60,2);
	printf("W E L C O M E      T O ");
	while (i<=10){
		gotoxy(i,5);     printf(" *######*   #######  *#####*      *##*      ##       *#####*       *#####+   ########   *######*    *#####*     #######    \n");
		gotoxy(19-i,6);  printf(" ##         ##       ##    ##    *#   #*    ##       ##    #*      ##    ##     ##     *#      #*   ##    ##     ##        \n");
		gotoxy(i-1,7);   printf(" ##         ##       ##    ##   *#     #*   ##       ##     #*     ##           ##    *#        #*  ##    ##     ##		\n");
		gotoxy(19-i,8);  printf(" **####*    *####    *#####*   *# ===== #*  ##       ##      #*     *#### *     ##   *#          #*  *#####*     *####     \n");
		gotoxy(i-1,9);   printf(" ##     ##  ##       ##  ##    ##       ##  ##       ##     *#           ##     ##    *#        #*   ##  ##      ##        \n");
		gotoxy(19-i,10); printf(" ##     ##  ##       ##   ##   ##       ##  ##       ##    *#      ##    ##     ##     *#      #*    ##   ##     ##        \n");
		gotoxy(i-1,11);  printf(" *#####*    #######  ##    ##  ##       ##  #######  *####*#       +#####*      ##      *#####*      ##    ##    #######   \n");
		Sleep(300);
		i++;
	}
}

void judul2(){
	system("cls");
	gotoxy(60,2);
	printf("W E L C O M E      T O ");
    int i = 15;
    gotoxy(i,5);  printf(" *######*   #######  *#####*      *##*      ##       *#####*       *#####+   ########   *######*    *#####*     #######    \n");
	gotoxy(i,6);  printf(" ##         ##       ##    ##    *#   #*    ##       ##    #*      ##    ##     ##     *#      #*   ##    ##     ##        \n");
	gotoxy(i,7);  printf(" ##         ##       ##    ##   *#     #*   ##       ##     #*     ##           ##    *#        #*  ##    ##     ##		\n");
	gotoxy(i,8);  printf(" **####*    *####    *#####*   *# ===== #*  ##       ##      #*     *#### *     ##   *#          #*  *#####*     *####     \n");
	gotoxy(i,9);  printf(" ##     ##  ##       ##  ##    ##       ##  ##       ##     *#           ##     ##    *#        #*   ##  ##      ##        \n");
	gotoxy(i,10); printf(" ##     ##  ##       ##   ##   ##       ##  ##       ##    *#      ##    ##     ##     *#      #*    ##   ##     ##        \n");
	gotoxy(i,11); printf(" *#####*    #######  ##    ##  ##       ##  #######  *####*#       +#####*      ##      *#####*      ##    ##    #######   \n");
	gotoxy(i+8, 17); printf("|=================================================================================================|\n");
    gotoxy(i+8, 18); printf("																						       		 \n");
    gotoxy(i+8, 19); printf("|                   [1]ADMIN             [2]CUSTOMER             [3]EXIT                          |\n");
    gotoxy(i+8, 20); printf("  														 										 \n");
    gotoxy(i+8, 21); printf("|=================================================================================================|\n\n");
    gotoxy(i+48, 22); printf("Masukkan pilihan Anda:         \n");
}
        

int main() {
	loadingScreen();
	system("cls");	
    int choice;
    judul();
    
    do {
    	judul2();
	    int i = 23;
	    gotoxy(i, 17); printf("|=================================================================================================|\n");
	    gotoxy(i, 18); printf("																						       		 \n");
	    gotoxy(i, 19); printf("|                   [1]ADMIN             [2]CUSTOMER             [3]EXIT                          |\n");
	    gotoxy(i, 20); printf("  														 										 \n");
	    gotoxy(i, 21); printf("|=================================================================================================|\n\n");
	    gotoxy(i+40, 22); printf("Masukkan pilihan Anda:         ");
	    scanf("%d", &choice);
	
	    switch (choice) {
	        case 1:
	        	system("cls");
	            adminMenu();
	            break;
	        case 2:
	        	system("cls");
	            userMenu();
	            break;
	        case 3:
	            return 0;
	        default:
	            puts("\nINVALID !! PLEASE INSERT THE RIGHT CHOOSE\n");
				system("pause");
				system("cls");
				judul2();
				break;
	    }
	} while (choice != 3);
    return 0;
}



