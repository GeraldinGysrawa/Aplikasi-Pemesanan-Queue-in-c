
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "global.h"
#include "dhea.h"
#define MAX 100

#define MAX 100

/*
	^ Binary Search Tree
	^ temp : pointer
	^ alokasikan tempat jika NULL dan isikan data dan index
	^ index yang lebih kecil menjadi left son
	^ index yang lebih besar menjadi rightson
*/
struct NodeRegist* insertRegist(struct NodeRegist* node, char data, int index) {
    if (node == NULL) {
        struct NodeRegist* temp = (struct NodeRegist*)malloc(sizeof(struct NodeRegist));
        temp->data = data;
        temp->index = index;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (index < node->index)
        node->left = insertRegist(node->left, data, index);
    else
        node->right = insertRegist(node->right, data, index);
    return node;
}

/*
	^ Dilakukan ketika root tidak NULL
	^ left-son -- right-son -- parent
	^ alokasikan tempat jika NULL dan isikan data dan index
	^ index yang lebih kecil menjadi left son
	^ index yang lebih besar menjadi rightson
*/
void postorderTraversal(struct NodeRegist* root, char* password, int* pos) {
    if (root != NULL) {
        postorderTraversal(root->left, password, pos);
        postorderTraversal(root->right, password, pos);
        password[(*pos)++] = root->data;
    }
}

/*
	^ var result : menyimpan hasil trav (static : mempertahankan nilai nilai)
	^ pos : melacak posisi dlm array
	^ alokasikan tempat jika NULL dan isikan data dan index
	^ index yang lebih kecil menjadi left son
	^ index yang lebih besar menjadi rightson
*/
char* postorder(struct NodeRegist* root) {
    static char result[100]; 
    int pos = 0;
    postorderTraversal(root, result, &pos);
    result[pos] = '\0'; 
    return result;
}

/* 
	^ pass yang telah terenkrip oleh traversal inorder, akan di enkrip lagi oleh caesar chiper
	^ caesar chiper akan mengubah posisi char dalam string dengan 3
	^ enkripsi yang dilakukan di fitur ini dilakukan sebanyak 2 kali;
	^ oleh traversal inorder & caesar chiper 
*/
void caesarchiper(char* pass, int len) {
    for (int i = 0; i < len; i++) {
        if (pass[i] >= 'A' && pass[i] <= 'Z') {
            pass[i] = pass[i] + 3;
        } else if (pass[i] >= 'a' && pass[i] <= 'z') {
            pass[i] = pass[i] + 3;
        }
    }
}


char* encryptPassword(char *pass) {
    int len = strlen(pass);

    /* 
		^ pointer : root (NULL)
		^ iterasi insert pass ke tree 
	*/
    struct NodeRegist *root = NULL;
    for (int i = 0; i < len; i++) {
        root = insertRegist(root, pass[i], i);
    }

    /* 
		^ hasil postorder disimpan di pass
	*/
    pass = postorder(root);
	caesarchiper(pass, len);

    return pass;
}

// cek email
bool emailValid(char *email) {
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

// cek usn
bool usnValid(char *username, const char *filename) {
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

// cek pass
bool alphaNumeric(char *password) {
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

// register
void Register(int index, bool isAdmin) {
    char email[30];
    char pass[20];
    struct usersRegist user[100];
    if (index >= 100) {
        printf("Batas jumlah pengguna tercapai.\n");
        return;
    }
    
    //tampilan regist
    system("cls");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t======================== R E G I S T E R ==========================\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t|                          GERALD STORE                           |\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");

    printf("\t\t\t\t Masukkan nama Anda : ");
    scanf("%s", user[index].Nama);

	//email
    bool emailValidd = false;
    do {
    	printf("\t\t\t\t Masukkan alamat email Anda (@gmail.com):");
        scanf("%s", email);
        
        if (!emailValid(email)){
            printf("\t\t\t\t Alamat email tidak valid.\n");
        } else {
            emailValidd = true;
        }
    } while (!emailValidd);
    
    strcpy(user[index].Email, email);
				
	//username
    bool usnValidd = false;
    const char *filename = isAdmin ? "file_admin1.3.txt" : "file_user1.3.txt";
    do {
    	printf("\t\t\t\t Masukkan username : ");
        scanf("%s", user[index].usn);
        
        if (usnValid(user[index].usn, filename)) {
            printf("\t\t\t\t Username sudah ada, masukkan username lain!\n");
        } else {
            usnValidd = true;
        }
        
    } while (!usnValidd);

	//password
    char plain_pass[MAX];
    bool passValid = false;
    do {
    	printf("\t\t\t\t Masukkan password : ");
        scanf("%s", pass);
        if (!alphaNumeric(pass)) {
            printf("\t\t\t\t Password minimum 8 karakter dan terdiri dari huruf dan angka.\n");
        } else {
            passValid = true;
        }
    } while (!passValid);
	
	//copy ke array
    strcpy(user[index].pass, pass);
    strcpy(plain_pass, pass);

	char anjiang[MAX];
	strcpy(anjiang,encryptPassword(pass));
	getchar();

    FILE *f_B;
    f_B = fopen(filename, "a");
    if (f_B == NULL) {
        printf("\t\t\t\t File tidak dapat dibuka.\n");
        return;
    }
    getchar();
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].usn, anjiang);
    fclose(f_B);

    index++;
    printf("\n");
    printf("\t\t\t\t Register Sukses!\n");
    getchar();
}

// login user
bool Login(bool isAdmin) {
    char usn[20];
    char pass[20];
    char encrypted_password[MAX];
    char passTersimpan[MAX];
	
	//tampilan login
    system("cls");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t=========================== L O G I N =============================\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t|                          GERALD STORE                           |\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    
    printf("\t\t\t\t Masukkan username : ");
    scanf("%s", usn);
    printf("\t\t\t\t Masukkan password : ");
    scanf("%s", pass);
	
	//copy ke array
	char anjiang[MAX];
	strcpy(anjiang, encryptPassword(pass));
	getchar();
	
    const char *filename = isAdmin ? "file_admin1.3.txt" : "file_user1.3.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return false;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char usnTersimpan[20];
        sscanf(line, "%*s %*s %s %s", usnTersimpan, passTersimpan);
        if (strcmp(usnTersimpan, usn) == 0 && strcmp(passTersimpan, anjiang) == 0) {
            fclose(file);
            return true;
        }
    }
    
    fclose(file);
    return false;
}

//login admin
bool LoginAdmin() {
    char usn[20];
    char pass[20];
    char encryptedPass[MAX];   						//menyimpan pass yang sudah dienkripsi setelah admin input
    const char storedUsn[] = "Geraldin";
    const char storedPass[] = "Geraldin12321";
	
	/*
		^ 'encrypted_stored_pass[MAX]' : menyimpan pass yang sudah dienkripsi dari stored_pass
		^ 'strdup(stored_pass)' : membuat salinan
		^ menyimpan hasil enkripsi di 'encrypted_stored_pass'
	*/
	char encStoredPass[MAX];				
    strcpy(encStoredPass, encryptPassword(strdup(storedPass)));	
	
    
    // tampilan login
    system("cls");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t=========================== L O G I N =============================\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    printf("\t\t\t\t|                          GERALD STORE                           |\n");
    printf("\t\t\t\t-------------------------------------------------------------------\n");
    
    printf("\t\t\t\t Masukkan username : ");
    scanf("%s", usn);
    printf("\t\t\t\t Masukkan password : ");
    scanf("%s", pass);
	
	/*
		^ 'encryptPassword(pass)' : melakukan enkripsi pass yang diinput admin
		^ 'encryptedaPass' : menyimpan hasil enkripsi yang diinput admin
		^ menyimpan hasil enkripsi di 'encrypted_stored_pass'
	*/
    strcpy(encryptedPass, encryptPassword(pass));
	
    /*
		^ 'strcmp(usn, stored_usn)' : membandingkan usn
		^ 'strcmp(encryptedPass, encrypted_stored_pass)' : membandingkan pass
		^ jika sama hasil : 0 (true)
	*/
    if (strcmp(usn, storedUsn) == 0 && strcmp(encryptedPass, encStoredPass) == 0) {
        return true;
    }
    
    return false;
}