#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "login.h"
#include "register.h"
#define MAX 100

// Prototype
int checkCredentials(char *username, char *password, char *file_name);

// matrik invers
//int inverse_key[2][2] = {{6, 5}, {15, 16}};
void decryptPassword(char *encrypted_password, char *decrypted_password);

// deklarasi prototype fungsi
//void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
//void decryptPassword(char *encrypted_password, char *decrypted_password);

/*
// untuk login
void Login(){
    char username[20], password[20];
    system("cls");
    system("color 3F");
    printf("\t\t\t\t===================================\n");
	printf("\t\t\t\t              LOGIN                \n");
	printf("\t\t\t\t===================================\n");
	printf("\t\t\t\tUsername:");
	scanf("%s", username);
	printf("\t\t\t\tPassword: ");
	scanf("%s", password);

    // Membersihkan buffer input
    getchar();
    
    // Memeriksa kecocokan username dan password
    if (checkCredentials(username, password, "file_user1.3.txt")) {
        printf("\t\t\t\tLogin berhasil!\n");
        //MenuUtama();
    } else {
        printf("Login gagal. Username atau password salah.\n");
    }
    getch();
    /*
    // Memeriksa kecocokan username dan password
    if (checkCredentials(username, password, 	"file_user1.3.txt")) {
    	printf("\t\t\t\tLogin berhasil!\n");
    	//MenuUtama();
    } else {
        printf("Login gagal. Username atau password salah.\n");
    }
    getch();*/



// Fungsi decryptPassword baru untuk Caesar Cipher
void decryptPassword(char *encrypted_password, char *decrypted_password) {
    int shift = 3; // Shift untuk Caesar Cipher
    int i;
    for (i = 0; encrypted_password[i] != '\0'; ++i) {
        char ch = encrypted_password[i];
        if (ch >= 'a' && ch <= 'z') {
            decrypted_password[i] = ((ch - 'a' - shift + 26) % 26) + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            decrypted_password[i] = ((ch - 'A' - shift + 26) % 26) + 'A';
        } else {
            decrypted_password[i] = ch;
        }
    }
    decrypted_password[i] = '\0'; // Menambahkan null terminator
}
/*
void decryptPassword(char *encrypted_password, char *decrypted_password) {
    int len = strlen(encrypted_password);
    int total_rows = (len % 2 != 0) ? (len / 2 + 1) : (len / 2);

    // Dekripsi password
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) {
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) {
            // Hanya dekripsi karakter alfabet
            if (encrypted_password[r * 2 + i] >= 'a' && encrypted_password[r * 2 + i] <= 'z') {
                message[i][0] = encrypted_password[r * 2 + i] - 'a';
            } else if (encrypted_password[r * 2 + i] >= 'A' && encrypted_password[r * 2 + i] <= 'Z') {
                message[i][0] = encrypted_password[r * 2 + i] - 'A';
            } else {
                // Salin karakter non-alfabet tanpa dekripsi
                message[i][0] = encrypted_password[r * 2 + i];
            }
        }

        // Lanjutkan proses dekripsi untuk karakter alfabet
        multiplyMatrix(inverse_key, message, result);
        for (i = 0; i < 2; i++) {
            if (encrypted_password[r * 2 + i] >= 'a' && encrypted_password[r * 2 + i] <= 'z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                decrypted_password[k++] = num + 'a';
            } else if (encrypted_password[r * 2 + i] >= 'A' && encrypted_password[r * 2 + i] <= 'Z') {
                int num = (result[i][0] % 26);
                if (num < 0) num += 26; // Menangani nilai negatif
                decrypted_password[k++] = num + 'A';
            } else {
                // Salin karakter non-alfabet tanpa dekripsi
                decrypted_password[k++] = encrypted_password[r * 2 + i];
            }
        }
    }
    decrypted_password[k] = '\0'; // Menambahkan null terminator
}
*/

// Fungsi untuk memeriksa kredensial
int checkCredentials(char *username, char *password, char *file_name) {
    FILE *file = fopen(file_name, "r"); // Buka file

    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return false;
    }

    char line[MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        char saved_username[MAX];
        char saved_encrypted_password[MAX];

        // Memindai username dan password terenkripsi dari setiap baris dalam file
        sscanf(line, "%*s %*s %s %s", saved_username, saved_encrypted_password);

        // Dekripsi password yang tersimpan dalam file
        char decrypted_password[MAX];
        decryptPassword(saved_encrypted_password, decrypted_password);

        // Bandingkan username dan password yang telah terdekripsi dengan input pengguna
        if (strcmp(saved_username, username) == 0 && strcmp(decrypted_password, password) == 0) {
            fclose(file);
            printf("Login berhasil!\n");
            return true; // username dan password cocok
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n");
    return false; // Username dan password tidak cocok
}

bool Login(bool isAdmin) {
    char username[20];
    char password[20];
    char encrypted_password[MAX];
    char stored_password[MAX];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    encryptPassword(password, encrypted_password);

    const char *filename = isAdmin ? "file_admin1.3.txt" : "file_user1.3.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File cannot be opened.\n");
        return false;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char stored_username[20];
        sscanf(line, "%*s %*s %s %s", stored_username, stored_password);
        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, encrypted_password) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}


/*
// untuk check username dan password
int checkCredentials(char *username, char *password, char *file_name) {
    FILE *file = fopen(file_name, "r"); // Buka file

    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return false;
    }

    char line[MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        char saved_username[MAX];
        char saved_encrypted_password[MAX];

        // Memindai username dan password terenkripsi dari setiap baris dalam file
        sscanf(line, "%*s %*s %s %s", saved_username, saved_encrypted_password);

        // Dekripsi password yang tersimpan dalam file
        char decrypted_password[MAX];
        //decryptPassword(saved_encrypted_password, decrypted_password);

        // Bandingkan username dan password yang telah terdekripsi dengan input pengguna
        if (strcmp(saved_username, username) == 0 && strcmp(decrypted_password, password) == 0) {
            fclose(file);
            printf("Login berhasil!\n");
            return true; // username dan password cocok
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n");
    return false; // Username dan password tidak cocok
}*/