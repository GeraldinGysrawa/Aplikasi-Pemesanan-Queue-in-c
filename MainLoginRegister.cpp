#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "login.h"
#include "Register.h"

void adminMenu();
void userMenu();

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

void adminMenu() {
    int choice;
    bool isAdmin = true;
    int index = 0;

    while (1) {
        system("cls");
        printf("Admin Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Register(index, isAdmin);
                break;
            case 2:
                if (Login(isAdmin)) {
                    printf("Admin Login Successful\n");
                } else {
                    printf("Admin Login Failed\n");
                }
                getchar(); // To pause the screen
                getchar(); // To pause the screen
                break;
            case 3:
                return;
            default:
                printf("Invalid choice\n");
                getchar(); // To pause the screen
                getchar(); // To pause the screen
        }
    }
}

void userMenu() {
    int choice;
    bool isAdmin = false;
    int index = 0;

    while (1) {
        system("cls");
        printf("User Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Register(index, isAdmin);
                break;
            case 2:
                if (Login(isAdmin)) {
                    printf("User Login Successful\n");
                } else {
                    printf("User Login Failed\n");
                }
                getchar(); // To pause the screen
                getchar(); // To pause the screen
                break;
            case 3:
                return;
            default:
                printf("Invalid choice\n");
                getchar(); // To pause the screen
                getchar(); // To pause the screen
        }
    }
}
