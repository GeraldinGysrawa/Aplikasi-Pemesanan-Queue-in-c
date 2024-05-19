/*#ifndef REGISTER_H
#define REGISTER_H

#include <stdbool.h>

#define MAX 100

struct users {
    char Nama[30];
    char Email[30];
    char username[20];
    char password[20];
};

// Function prototypes
void getPasswordByUsername(char *username, char *decrypted_password);
void encryptPassword(char *plain_password, char *encrypted_password);
bool isEmailValid(char *email);
bool isUsernameExists(char *username, const char *filename);
bool isAlphaNumeric(char *password);
void Register(int index, bool isAdmin);
bool Login(bool isAdmin);

#endif // REGISTER_H
*/
#ifndef REGISTER_H
#define REGISTER_H

#include <stdbool.h>

#define MAX 100

struct users {
    char Nama[30];
    char Email[30];
    char username[20];
    char password[20];
};

// Function prototypes
void encryptPassword(char *plain_password, char *encrypted_password);
bool isEmailValid(char *email);
bool isUsernameExists(char *username, const char *filename);
bool isAlphaNumeric(char *password);
void Register(int index, bool isAdmin);

#endif // REGISTER_H

