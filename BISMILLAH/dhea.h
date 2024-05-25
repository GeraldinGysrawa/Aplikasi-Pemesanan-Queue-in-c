#ifndef DHEA_H
#define DHEA_H

#include <stdbool.h>

#define MAX 100

struct usersRegist {
    char Nama[30];
    char Email[30];
    char username[20];
    char password[20];
};

struct NodeRegist {
    char data;
    int index;
    struct NodeRegist *left, *right;
};

// Function prototypes
char* encryptPassword(char *password);
//void encryptPassword(char *plain_password, char *encrypted_password);
bool isEmailValid(char *email);
bool isUsernameExists(char *username, const char *filename);
bool isAlphaNumeric(char *password);
void Register(int index, bool isAdmin);
bool Login(bool isAdmin);

#endif // REGISTER_H

