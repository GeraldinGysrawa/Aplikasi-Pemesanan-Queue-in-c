#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "Register.h"
#include "tree.h"
#define MAX 100

// Prototype
void getPasswordByUsername(char *username, char *decrypted_password);

// For encryption and decryption (Caesar Cipher)
void encryptPassword(char *plain_password, char *encrypted_password) {
    int shift = 3; // Shift for Caesar Cipher
    int i;
    for (i = 0; plain_password[i] != '\0'; ++i) {
        char ch = plain_password[i];
        if (ch >= 'a' && ch <= 'z') {
            encrypted_password[i] = ((ch - 'a' + shift) % 26) + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            encrypted_password[i] = ((ch - 'A' + shift) % 26) + 'A';
        } else {
            encrypted_password[i] = ch;
        }
    }
    encrypted_password[i] = '\0'; // Adding null terminator
}

// Check email
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

// Check username
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

// Check password
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

// Register function
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

/*
// Login function
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

    const char *filename = isAdmin ? "admin_file.txt" : "file_user1.3.txt";
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
}*/


