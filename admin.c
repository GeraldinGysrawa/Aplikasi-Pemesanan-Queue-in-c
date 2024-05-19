//admin.c
#include "geraldin.h"
#include "annisa.h"
#include "rizky.h"
#include "ikhsan.h"
#include <stdbool.h>

int loginadmin() {
    int num;
    int in = 0;
    bool loggedIn = true;
	
    do {
        system("cls");
        system("color 4F");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t     SELAMAT DATANG DI APLIKASI\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t1. Register\n");
        printf("\t\t\t\t2. Login\n");
        printf("\t\t\t\t3. Exit\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\tPilihan Anda: ");
        scanf("%d", &num);

        switch(num) {
            case 1:
                Register(in);
                break;
            case 2:
                Login(); // Mengirimkan alamat variabel loggedIn agar dapat diubah di dalam fungsi
                break;
            case 3:
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }

        // Jika sudah login, panggil MenuUtama dan reset loggedIn
        if (loggedIn) {
            admin();
            loggedIn = false;
        }
    } while (num != 3);

    return 0;
}

int admin() {
    List barangList;
    barangList.head = NULL;
    barangList.tail = NULL;

    Queue pembeliQueue;
    pembeliQueue.front = NULL;
    pembeliQueue.rear = NULL;

    // Load barang from file
    readfile(&barangList);

    int choice;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Kelola barang\n");
        printf("2. Tampilkan daftar pembeli\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    printf("\n=== KELOLA BARANG ===\n");
                    printf("1. Tambah barang\n");
                    printf("2. Tambah stok barang\n");
                    printf("3. Hapus barang\n");
                    printf("4. Lihat barang yang ada ada\n");
                    printf("5. Kembali ke menu utama\n");
                    printf("Pilih: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            insert(&barangList);
                            break;
                        case 2:
                            disList(&barangList);
                            addStock(&barangList);
                            break;
                        case 3:
                            disList(&barangList);
                            deleteItem(&barangList);
                            break;
                        case 4:
                        	disList(&barangList);
                        	break;
                        case 5:
                            printf("Kembali ke menu utama.\n");
                            break;
                        default:
                            printf("Pilihan tidak valid. Silakan coba lagi.\n");
                    }
                } while (choice != 5);
                choice = 0; // Reset looping
                break;
            case 2:
            	if (pembeliQueue.front == NULL) {
       				 readFileToQueue(&pembeliQueue);
    			}
    			displayPembeli(&pembeliQueue);
                break;
            case 3:
                printf("Keluar dari program.\n");
                return 0;
            	default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
    clearList(&barangList);

    return 0;
}

