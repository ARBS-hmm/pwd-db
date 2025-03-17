
#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>

// Define the User structure
typedef struct {
    char username[50];   // Username of the user
    char password[50];   // Password of the user
    int enabled;         // User account status (1 = enabled, 0 = disabled)
} User;

// Function prototypes
int authLog(char name[10], int success);
void disableAccount(const char *username);
int authenticator(char *username, char *password);
void createUserFile(); // This is for testing purposes, to create a sample user list

#endif // SECURITY_H
