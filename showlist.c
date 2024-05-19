#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string.h>
#include "rizky.h"

void createList(List *list) 
{
    list->head = NULL;
    list->tail = NULL;
}  

// Untuk menampilkan list barang yang ada
void disList(List *list) 
{
    FILE *file = fopen("jualan.txt", "r");
    if (file == NULL) 
	{
        printf("Gagal membuka file.\n");
        return;
    }

    printf("List Barang: \n");
    printf("\n===========================================================================\n");
    printf("| %-20s | %-15s | %-10s | %-5s |\n", "Nama Barang", "Dekripsi", "Harga (Rp)", "Stok");
    printf("===========================================================================\n");

    // Read data from file and populate the list
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) 
	{
        Node *newNode = (Node*) malloc(sizeof(Node));
        if (newNode == NULL) 
		{
            printf("Memory allocation failed.\n");
            break;
        }
        sscanf(line, "%[^|]|%[^|]|%f|%d", newNode->info, newNode->detail, &newNode->price, &newNode->available);
        newNode->next = NULL;

        // Find the node in the list
        Node *current = list->head;
        Node *prev = NULL;
        while (current != NULL) 
		{
            if (strcmp(current->info, newNode->info) == 0) 
			{
                // Update the stock
                current->available = newNode->available;
                break;
            }
            prev = current;
            current = current->next;
        }

        // If the node is not found in the list, add it to the end
        if (current == NULL) 
		{
            if (list->head == NULL) 
			{
                list->head = newNode;
                list->tail = newNode;
            } else {
                list->tail->next = newNode;
                list->tail = newNode;
            }
        }
    }

    fclose(file);

    // Display the list
    Node *current = list->head;
    while (current != NULL) 
	{
        printf("| %-20s | %-15s | %-10.2f | %-5d |\n", current->info, current->detail, current->price, current->available);
        current = current->next;
    }

    printf("===========================================================================\n");
}
