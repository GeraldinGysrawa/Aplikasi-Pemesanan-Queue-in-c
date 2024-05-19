#include "annisa.h"
#include "rizky.h"

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

void history(Queue *q) 
{
	char opsi;
    FILE *file;
    char buffer[256];
    
    // Membuka file dalam mode read
    file = fopen("history.txt", "r");
    if (file == NULL) 
	{
        perror("Error opening file");
        return;
    }
	
	printf("Histori Pembelian Barang\n");
	printf("========================================\n");
    // Membaca setiap baris dalam file dan menampilkannya
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
	if (buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\0') {
            printf("========================================\n");
        } else {
            printf("%s", buffer);
        }
	}
    // Menutup file
    fclose(file);
    
    do
    {
	    printf("\nHapus seluruh history pemesanan?\n");
	    printf("1. Hapus\n");
	    printf("2. Kembali\n");
	    printf("Pilihan anda: ");
	    scanf("%d", &opsi);
	    
	    switch(opsi) {
	    	case 1:
	    		clearHistory();
	    		break;
	    	case 2:
	    		break;
	    	default:
	    		printf("Pilihan tidak valid\n");
		}
	} while (opsi != 2);
}

void clearHistory() {
    FILE *file;

    // Membuka file dalam mode write untuk menghapus semua isinya
    file = fopen("history.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Menutup file setelah dibuka dalam mode write, yang akan menghapus semua isinya
    fclose(file);
    printf("History telah dihapus.\n");
}
