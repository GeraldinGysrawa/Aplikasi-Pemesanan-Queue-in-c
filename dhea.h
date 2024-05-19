#ifndef DHEA_H
#define DHEA_H

#include <stdbool.h>
#include "global.h"

void decryptPassword(char *encrypted_password, char *decrypted_password);
void encryptPassword(char *password, char *encrypted_password);
bool checkCredentials(char *username, char *password, const char *file_name);
void adminMenu();
void userMenu();
bool Login(bool isAdmin);
void Register(int index, bool isAdmin);
bool isEmailValid(char *email);
bool isUsernameExists(char *username, const char *filename);
bool isAlphaNumeric(char *password);
void userMenu();

#endif 