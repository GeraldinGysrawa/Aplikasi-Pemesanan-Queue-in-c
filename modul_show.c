#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "DISPLAY.h"
#include "tambahbarang.h"

// Untuk menampilkan list barang yang ada
void disList(List *myList)
{
    if (myList->head != NULL)
    {
    	printf("List Barang: \n");
        printf("\n===========================================================================\n");
        printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
        printf("===========================================================================\n");
        struct Node *current = myList->head;
        while (current != NULL)
        {
            printf("| %-20s | %-15s | %-10.2f | %-5d |\n", current->info, current->detail, current->price, current->available);
            current = current->next;
        }

        printf("===========================================================================\n");
    }
    else
    {
        printf("\nList Kosong\n");
    }
//    struct Node *current = *head;
//    while (current != NULL) {
//        struct Node *temp = current;
//        current = current->next;
//        free(temp);
//    }
}

void createList(List *myList) {
    myList->head = NULL;
    myList->tail = NULL;
}  

//void disList(List *myList)
//{
////	Node *temp;
////	temp = myList->head;
//	struct Node *current = myList->head;
//	
//	// Cek apakah list kosong
//	if (myList->head == NULL)
//	{
//		printf("List Kosong\n");
//	} else {
//		while (current != NULL) {
//		// Tampilkan list jika ada
//		printf("List Barang: \n");	
////		while (current->next != NULL && current != NULL)
////		{
//			printf("===========================================================================\n");
//		    printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
//		    printf("===========================================================================\n");
////		    struct Node *current = head;
//			struct Node *current = myList->head;
////		    while (current != NULL) {
//		        printf("| %-20s | %-15.2f | %-10d | %-5s |\n", current->info, current->detail, current->price, current->available);
//		        current = current->next;
//		    }
//		    printf("===========================================================================\n");
//				
////			printf("Barang: %s", &temp->info);
////			printf("Barang: %s", &temp->detail);
////			printf("Barang: %d", &temp->available);
////			printf("Barang: %.2f", &temp->price);
////			temp = temp->next;
//		}
//	}
//	struct Node *current = temp;
//    while (current != NULL) {
//        struct Node *temp = current;
//        current = current->next;
//        free(temp);
//    }

//}

