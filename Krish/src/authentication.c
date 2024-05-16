// authentication.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "authentication.h"

// Define maximum username and password length
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Hardcoded admin username and password
const char admin_username[] = "admin";
const char admin_password[] = "admin123";

int login()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Prompt for username and password
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);

    // Remove newline characters from username and password
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    // Check if username and password match admin credentials
    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0)
    {
        printf("Login successful!\n");
        return 1; // Return 1 for successful login
    }
    else
    {
        printf("Invalid username or password. Please try again.\n");
        return 0; // Return 0 for unsuccessful login
    }
}

void logout()
{
    // You can add logout functionality here if needed
    printf("Logout successful!\n");
}
