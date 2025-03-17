#ifndef USER_H
#define USER_H

#include <stdio.h>

// Define the User structure
typedef struct {
    char username[50];   // Username of the user
    char password[50];   // Password of the user
    int enabled;         // User account status (1 = enabled, 0 = disabled)
} User;

// Function prototypes
int checkUserExistence(const char *name);
void createUser(const char *name);
void renameUser(const char name[]);
void deleteUser(const char *name);
void changeMaster(const char *name, const char *newPassword);

#endif // USER_H
