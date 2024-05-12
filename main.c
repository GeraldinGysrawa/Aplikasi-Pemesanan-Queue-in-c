//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
#include "DISPLAY.h"
#include "tambahbarang.h"

int main() {
    // Inisialisasi linked list
    List myList;
    createList(&myList);

    int option;
    do {
    	system("cls");
        printf("=================================\n");
        printf("             M E N U            \n");
        printf("=================================\n");
        printf("1. Tambah Barang\n");
        printf("2. Tambah Stok Barang\n");
        printf("3. Tampilkan Semua Barang\n");
        printf("4. Hapus Barang\n");
        printf("0. Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &option);
        printf("=================================\n");

        switch (option) {
            case 1:
                input_barang(&myList);
                printf("Barang berhasil ditambahkan.\n");
                break;
            case 2:
                tambah_stok(&myList);
                break;
            case 3:
                disList(&myList);
                break;
//            case 4:
//                disList(&myList);
//                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Opsi tidak valid.\n");
                break;
        }
        // Membersihkan newline character dari buffer stdin
        printf("\nPress any key to continue . . . ");
        getchar();
    } while (option != 0);

    return 0;
}

//int main()
//{
//	List myList;
//	createList(&myList);
//	input_barang(&myList);
//	disList(&myList);
//	tambah(&myList);
//	return 0;
//}

//// Fungsi utama
//int main() {
//    List myList;
//
//    // Memasukkan barang-barang yang dijual
//    tambah_barang(&myList, "Laptop", "Laptop Intel Core i5", 5000000, 10);
//    tambah_barang(&myList, "Smartphone", "Smartphone Android 4G", 2000000, 15);
//    tambah_barang(&myList, "Headphone", "Headphone Bluetooth", 500000, 20);
//
//    // Menampilkan list barang yang dijual
//    disList(&myList);
//
//   // Menambahkan barang baru ke linked list
//    tambah_barangbaru(&myList);
//
//    // Menampilkan daftar barang elektronik yang diperbarui
//    printf("Daftar barang setelah penambahan:\n");
//    disList(&myList);
////
//    // Menyimpan data ke dalam file catatan.txt
//    simpan_ke_file(head);
//
//    // Dealokasi memori linked list setelah digunakan
////    struct Node *current = head;
////    while (current != NULL) {
////        struct Node *temp = current;
////        current = current->next;
////        free(temp);
////    }

//    return 0;
//}
