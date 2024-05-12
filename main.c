#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "DISPLAY.h"
#include "tambahbarang.h"

int main()
{
	List myList;
	createList(&myList);
	input_barang(&myList);
	disList(&myList);
//	tambah(&myList);
	return 0;
}

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
