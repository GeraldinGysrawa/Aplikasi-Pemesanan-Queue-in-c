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
    gotoxy(50, 10);
    printf("Loading...");
    gotoxy(50, 12);

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
	int i;
	system("cls");
	i=1;
	gotoxy(43,2);printf("W E L C O M E      T O ");
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

int main() {
	loadingScreen();
	system("cls");	
    int choice;
    
    while (1) {
    	judul();
        int i = 43;
        gotoxy(i, 17); printf("=================================\n");
	    gotoxy(i, 18); printf("|       M E N U  U T A M A      |\n");
	    gotoxy(i, 19); printf("=================================\n");
	    gotoxy(i, 20); printf("|1. Admin                       |\n");
	    gotoxy(i, 21); printf("|2. User                        |\n");
	    gotoxy(i, 22); printf("|Masukkan pilihan Anda:         |\n");
	    gotoxy(i, 23); printf("=================================\n");
	    gotoxy(i + 27, 22);
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
                exit(0);
            default:
                printf("Invalid choice\n");
                getchar(); // To pause the screen
                getchar(); // To pause the screen
        }
    }
    return 0;
}



