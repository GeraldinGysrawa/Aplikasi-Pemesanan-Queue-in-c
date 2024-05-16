#include <stdio.h>
#include "tubuh.h"

int main() {
    List list;
    list.head = NULL;
    list.tail = NULL;

    int choice;
    do {
        choice = menu();
        switch(choice) {
            case 1:
                insert(&list);
                break;
            case 2:
				addStock(&list);
                break;
            case 3:
                disList(&list);
                break;
            case 4:
                // Hapus barang
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0);

    return 0;
}
