#ifndef DHEA_H
#define DHEA_H

#include <stdbool.h>
#include "global.h"

//login
int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();
	
//Register
int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);
bool isAlphaNumeric(char *password);
bool isEmailValid(char *email);
bool isUsernameExists(char *username);
void encryptPassword(char *plain_password, char *encrypted_password);
struct TreeNode* addNode(int shift);
bool searchShift(struct TreeNode* root, int shift);
void freeTree(struct TreeNode* root);
void Register(int index);
/*
//Dhea
int checkCredentials(char *username, char *password, char *file_name);
void getPasswordByUsername(char *username, char *decrypted_password);
//void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();
*/

#endif 