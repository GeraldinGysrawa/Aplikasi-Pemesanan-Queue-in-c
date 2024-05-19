#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "global.h"

#define MAX 100

// Fungsi decryptPassword untuk Caesar Cipher
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

// Fungsi encryptPassword untuk Caesar Cipher
void encryptPassword(char *password, char *encrypted_password) {
    int shift = 3; // Shift untuk Caesar Cipher
    int i;
    for (i = 0; password[i] != '\0'; ++i) {
        char ch = password[i];
        if (ch >= 'a' && ch <= 'z') {
            encrypted_password[i] = ((ch - 'a' + shift) % 26) + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            encrypted_password[i] = ((ch - 'A' + shift) % 26) + 'A';
        } else {
            encrypted_password[i] = ch;
        }
    }
    encrypted_password[i] = '\0'; // Menambahkan null terminator
}

// Fungsi untuk memeriksa kredensial
bool checkCredentials(char *username, char *password, const char *file_name) {
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

// Fungsi untuk memeriksa validitas email
bool isEmailValid(char *email) {
    int i, atCount = 0;
    int len = strlen(email);
    if (email[0] == '@' || email[len - 1] == '@') {
        return false;
    }
    for (i = 0; i < len; i++) {
        if (email[i] == '@') {
            atCount++;
        }
    }
    if (atCount != 1) {
        return false;
    }
    char *domain = strstr(email, "@");
    if (domain != NULL && (strcmp(domain + 1, "gmail.com") != 0)) {
        return false;
    }
    return true;
}

// Fungsi untuk memeriksa keberadaan username
bool isUsernameExists(char *username, const char *filename) {
    if (strlen(username) > 20) {
        printf("Username cannot be longer than 20 characters.\n");
        return true;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File cannot be opened.\n");
        return true;
    }
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char saved_username[20];
        sscanf(line, "%*s %*s %s", saved_username);
        if (strcmp(saved_username, username) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

// Fungsi untuk memeriksa apakah password alfanumerik
bool isAlphaNumeric(char *password) {
    bool hasLetter = false;
    bool hasDigit = false;
    int length = 0;
    int i = 0;

    while (password[i] != '\0') {
        if (isalpha(password[i])) {
            hasLetter = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
        length++;
        i++;
    }
    return length >= 8 && hasLetter && hasDigit;
}

// Fungsi Login untuk Admin dan User
bool Login(bool isAdmin) {
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    const char *filename = isAdmin ? "file_admin1.3.txt" : "file_user1.3.txt";
    if (checkCredentials(username, password, filename)) {
        return true;
    } else {
        return false;
    }
}

// Fungsi Register untuk Admin dan User
void Register(int index, bool isAdmin) {
    char email[30];
    char password[20];
    struct users user[100];
    if (index >= 100) {
        printf("User limit reached.\n");
        return;
    }

    system("cls");
    printf("\tRegister Account\n\n");
    printf("Enter your name: ");
    scanf("%s", user[index].Nama);

    bool isValidEmail = false;
    do {
        printf("Enter email (@gmail.com): ");
        scanf("%s", email);
        if (!isEmailValid(email)) {
            printf("Invalid email address.\n");
        } else {
            isValidEmail = true;
        }
    } while (!isValidEmail);
    strcpy(user[index].Email, email);

    bool isUsernameValid = false;
    const char *filename = isAdmin ? "file_admin1.3.txt" : "file_user1.3.txt";
    do {
        printf("Enter username: ");
        scanf("%s", user[index].username);
        if (isUsernameExists(user[index].username, filename)) {
            printf("Username already exists. Enter another username.\n");
        } else {
            isUsernameValid = true;
        }
    } while (!isUsernameValid);

    char plain_password[MAX];
    bool isValidPassword = false;
    do {
        printf("Enter password (Minimum 8 characters, containing both letters and numbers): ");
        scanf("%s", password);
        if (!isAlphaNumeric(password)) {
            printf("Password does not meet the criteria.\n");
        } else {
            isValidPassword = true;
        }
    } while (!isValidPassword);

    strcpy(user[index].password, password);
    strcpy(plain_password, password);

    char encrypted_password[MAX];
    encryptPassword(plain_password, encrypted_password);

    FILE *f_B;
    f_B = fopen(filename, "a");
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].username, encrypted_password);
    fclose(f_B);

    index++;
    printf("\nRegistration Successful\n");
    getchar();
}
