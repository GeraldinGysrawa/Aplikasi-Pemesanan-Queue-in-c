#ifndef DHEA_H
#define DHEA_H

#include <stdbool.h>

#define MAX 100

struct usersRegist {
    char Nama[30];
    char Email[30];
    char usn[20];
    char pass[20];
};

struct NodeRegist {
    char data;
    int index;
    struct NodeRegist *left, *right;
};

// Function prototypes
char* encryptPassword(char *password);
//void encryptPassword(char *plain_password, char *encrypted_password);
bool emailValid(char *email);
bool isUsernameExists(char *username, const char *filename);
bool isAlphaNumeric(char *password);
void Register(int index, bool isAdmin);
bool Login(bool isAdmin);
bool LoginAdmin();
void userMenu();
void adminMenu();

#endif // REGISTER_H

