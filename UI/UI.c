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

void printFromFile(const char* location){
	FILE *read;
	char c;

	read=fopen(location, "rt");
	while((c=fgetc(read))!=EOF){
		printf("%c", c);
	}

	fclose(read);
}

int main() {
    loadingScreen();
    printFromFile("gambar/welcome.txt");
	printf("\n\n\t\t");
	system("Pause");
	system("cls");
	printFromFile("gambar/bos.txt");
	printf("\n\n\t\t");
    return 0;
}
