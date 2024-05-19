#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#define MAX 100
#include "global.h"

// Prototype
int checkCredentials(char *username, char *password, char *file_name);

// matrik invers
//int inverse_key[2][2] = {{6, 5}, {15, 16}};
void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();
// deklarasi prototype fungsi
//void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
//void decryptPassword(char *encrypted_password, char *decrypted_password);
void Login();


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
}

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




//REGISTER
//prototype
void getPasswordByUsername(char *username, char *decrypted_password);
struct TreeNode* root = NULL;


// Fungsi untuk membuat pohon biner dengan nilai shift sebagai nilai di setiap node
struct TreeNode* addNode(int shift) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->shift = shift;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi untuk mencari nilai shift dalam pohon biner
bool searchShift(struct TreeNode* root, int shift) {
    if (root == NULL)
        return false;
    if (root->shift == shift)
        return true;
    if (shift < root->shift)
        return searchShift(root->left, shift);
    else
        return searchShift(root->right, shift);
}

// Fungsi untuk membebaskan memori pohon biner
void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Fungsi untuk enkripsi Caesar Cipher
void encryptPassword(char *plain_password, char *encrypted_password) {
    int shift = 3; // Shift untuk Caesar Cipher
    root = addNode(shift); // Tambahkan shift ke tree
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
    encrypted_password[i] = '\0'; // Menambahkan null terminator
}
// Matriks kunci
//int key[2][2] = {{2, 1}, {3, 4}}; 

// Deklarasi prototipe fungsi
// multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]);
//void encryptPassword(char *plain_password, char *encrypted_password);

// Untuk perkalian matriks
/* void multiplyMatrix(int key[2][2], int message[2][1], int res[2][1]) 
{
    int i, j;
    for (i = 0; i < 2; i++) 
	{
        res[i][0] = 0;
        for (j = 0; j < 2; j++) 
		{
            res[i][0] += key[i][j] * message[j][0];
        }
    }
} */

/*
// Untuk enkripsi Hill Cipher
void encryptPassword(char *plain_password, char *encrypted_password) 
{
    int len = strlen(plain_password);
    int total_rows = (len % 2 != 0) ? (len / 2 + 1) : (len / 2);

    // Enkripsi password
    int r, i, k = 0;
    for (r = 0; r < total_rows; r++) 
	{
        int message[2][1], result[2][1];
        for (i = 0; i < 2; i++) 
		{
            // Hanya enkripsi karakter alfabet
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') 
			{
                message[i][0] = plain_password[r * 2 + i] - 'a';
            } 
			else if (plain_password[r * 2 + i] >= 'A' && plain_password[r * 2 + i] <= 'Z')
			{
            	message[i][0] = plain_password[r * 2 + i] - 'A';
            } else {
            	// Salin karakter non-alfabet tanpa enkripsi
                message[i][0] = plain_password[r * 2 + i];
			}
        }

        // Lanjutkan proses enkripsi untuk karakter alfabet
        multiplyMatrix(key, message, result);
        for (i = 0; i < 2; i++) 
		{
            if (plain_password[r * 2 + i] >= 'a' && plain_password[r * 2 + i] <= 'z') 
			{
                int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'a';
            } 
			else if (plain_password[r * 2 + i] >= 'A' && plain_password[r * 2 + i] <= 'Z') 
			{
                int num = (result[i][0] % 26);
                encrypted_password[k++] = num + 'A';
            } else {
            	// Salin karakter non-alfabet tanpa enkripsi
                encrypted_password[k++] = plain_password[r * 2 + i];
			}
        }
    }
    encrypted_password[k] = '\0'; // Menambahkan null terminator
}
*/

// Untuk check email
bool isEmailValid(char *email) 
{
    int i, atCount = 0;
    int len = strlen(email);
    // Memastikan '@' tidak berada di awal atau di akhir string
    if (email[0] == '@' || email[len - 1] == '@') 
	{
        return false;
    }
    
    // Menghitung jumlah @ dalam email
    for (i = 0; i < len; i++) 
	{
        if (email[i] == '@') 
		{
            atCount++;
        }
    }
    if (atCount == 1)			//(Ini posisi if(atcount) sama if(domain)nya tadi aku tuker, gatau ngaruh atau ga.
	{							//kalau mau mah paling tuker lagi aja posisinya jadi if(domain baru if(atcount).
        return true;			//terus komen yang ini hapus aja :v
	}
    
    // Memastikan bahwa email berdomain gmail.com
    char *domain = strstr(email, "@");
    if (domain != NULL && (strcmp(domain + 1, "gmail.com") != 0))
	{
        return false;
    }
	return false;
}

// Untuk check username
bool isUsernameExists(char *username) 
{
	// Memastikan username tidak lebih dari 20 karakter
	if (strlen(username) > 20) 
    {
        printf("Username tidak boleh lebih dari 20 karakter.\n");
        return true; // Username tidak valid, kembalikan true
    }
    FILE *file = fopen("file_user1.3.txt", "a");
    if (file == NULL) 
	{
        printf("File tidak dapat dibuka.\n");
        return true;
    }

    char line[100];
    // Membandingkan username dengan yang tersimpan dalam file
    while (fgets(line, sizeof(line), file) != NULL) 
	{
        char saved_username[20];
        sscanf(line, "%*s %*s %s", saved_username);
        if (strcmp(saved_username, username) == 0) 
		{
            fclose(file);
            return true; // Return true jika username sudah ada dalam file
        }
    }
    fclose(file);
    return false; // Return false jika username belum ada dalam file
}

//untuk check password
bool isAlphaNumeric(char *password) 
{
    bool hasLetter = false;
    bool hasDigit = false;
    int length = 0;
    int i;
	
	// Memastikan password terdiri dari angka dan huruf
    while (password[i] != '\0') 
	{
        if (isalpha(password[i])) 
		{
            hasLetter = true;
        } 
		else if (isdigit(password[i])) 
		{
            hasDigit = true;
        }
        length++;
        i++;
    }

	// Memastikan password terdiri dari minimal 8 karakter
    if (length >= 8)
	{
    	return hasLetter && hasDigit;
	} else {
		return false;
	}
}

// Fungsi Register
// Fungsi Register
void Register(int index) {
    char email[30];
    char password[20];
    struct users user[100];
    if (index >= 100) {
        printf("Batas pengguna telah tercapai.\n");
        return;
    }

    system("cls");
    printf("\tRegister Akun\n\n");
    printf("Masukkan nama anda : ");
    scanf("%s", user[index].Nama);

    // Meminta pengguna untuk memasukkan email yang memenuhi kriteria
    bool isValidEmail = false;
    do {
        printf("Masukkan email (@gmail.com) : ");
        scanf("%s", email);
        if (!isEmailValid(email)) {
            printf("Alamat email tidak valid.\n");
        } else {
            isValidEmail = true;
        }
    } while (!isValidEmail);

    // Set email ke dalam struct user
    strcpy(user[index].Email, email);

    bool isUsernameValid = false;
    // Meminta pengguna untuk memasukkan username yang memenuhi kriteria
    do {
        printf("Masukkan username : ");
        scanf("%s", user[index].username);
        if (isUsernameExists(user[index].username)) {
            printf("Username sudah digunakan. Masukkan username lain.\n");
        } else {
            isUsernameValid = true;
        }
    } while (!isUsernameValid);

    // Meminta pengguna untuk memasukkan password yang memenuhi kriteria
    char plain_password[MAX];
    bool isValidPassword = false;
    do {
        printf("Masukkan password (Minimal 8 karakter, terdiri dari angka dan huruf): ");
        scanf("%s", password);

        if (!isAlphaNumeric(password)) {
            printf("Password tidak sesuai kriteria.\n");
        } else {
            isValidPassword = true;
        }
    } while (!isValidPassword);

    // Set password ke dalam struct user
    strcpy(user[index].password, password);

    // Set password ke dalam plain_password
    strcpy(plain_password, password);

    // Enkripsi password
    char encrypted_password[MAX];
    encryptPassword(plain_password, encrypted_password);
    
    // Menyimpan Nama, email, username, dan password yang telah dienkrip kedalam file
    FILE *f_B;
    f_B = fopen("file_user1.3.txt", "a");
    fprintf(f_B, "%s %s %s %s\n", user[index].Nama, user[index].Email, user[index].username, encrypted_password);
    fclose(f_B);

    index++;
    printf("\nRegister Berhasil");
    getchar();
}




