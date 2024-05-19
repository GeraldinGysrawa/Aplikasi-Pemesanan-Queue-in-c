#include "annisa.h"
#include "dhea.h"
#include "geraldin.h"
#include "ikhsan.h"
#include "rizky.h"

int main() {
    int choice;

    while (1) {
        system("cls");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
                getchar(); // To pause the screen
                getchar(); // To pause the screen
        }
    }
    return 0;
}



