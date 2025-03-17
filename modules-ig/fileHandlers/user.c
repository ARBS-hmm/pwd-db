#include <stdio.h>
#include <string.h>
#include "io.h"

typedef struct {
    char username[50];   // Username of the user
    char password[50];   // Password of the user
    int enabled;         // User account status (1 = enabled, 0 = disabled)
} User;

// Check if a user exists
int checkUserExistence(const char *name) {
    char path[40] = "data/users/";
    char ext[10] = ".bin";
    strcat(path, name);
    strcat(path, ext);

    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        return 0; // User does not exist
    }
    fclose(fp);
    return 1; // User exists
}

// Create a new user
void createUser(const char *name) {
    char path[40] = "data/users/";
    char ext[10] = ".bin";
    strcat(path, name);
    strcat(path, ext);

    if (checkUserExistence(name)) {
        printf("User already exists\n");
        return;
    }

    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        printf("Error creating user file\n");
        return;
    }

    char pwd[50]; // Increased size for better security
    printf("Enter a master password: ");
    scanf("%s", pwd);

    // Add the user to the userlist
    User newUser;
    strncpy(newUser.username, name, sizeof(newUser.username));
    strncpy(newUser.password, pwd, sizeof(newUser.password));
    newUser.enabled = 1; // Enabled by default

    FILE *userlist = fopen("data/userlist.bin", "ab");
    if (userlist == NULL) {
        printf("Error opening userlist file\n");
        fclose(fp);
        return;
    }
    fwrite(&newUser, sizeof(User), 1, userlist);
    fclose(userlist);

    fclose(fp);
    printf("User created successfully\n");
}

// Rename a user
void renameUser(const char name[]) {
    char newName[50];

    if (!checkUserExistence(name)) {
        printf("This user doesn't exist.\n");
        return;
    }

    printf("Enter new name for the user: ");
    scanf("%s", newName);

    char oldPath[40];
    char newPath[40];
    char ext[10] = ".bin";
    char initial[20] = "data/users/";

    strcpy(oldPath, initial);
    strcat(oldPath, name);
    strcat(oldPath, ext);

    strcpy(newPath, initial);
    strcat(newPath, newName);
    strcat(newPath, ext);

    if (rename(oldPath, newPath) != 0) {
        printf("Error renaming user\n");
        return;
    }

    // Update the userlist
    FILE *fp = fopen("data/userlist.bin", "rb");
    FILE *tmp = fopen("tmp.bin", "wb");
    if (fp == NULL || tmp == NULL) {
        printf("Error updating userlist\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, name) == 0) {
            strncpy(user.username, newName, sizeof(user.username));
        }
        fwrite(&user, sizeof(User), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    remove("data/userlist.bin");
    rename("tmp.bin", "data/userlist.bin");

    printf("User renamed successfully\n");
}

// Delete a user
void deleteUser(const char *name) {
    char path[40] = "data/users/";
    char ext[10] = ".bin";
    strcat(path, name);
    strcat(path, ext);

    if (!checkUserExistence(name)) {
        printf("User does not exist\n");
        return;
    }

    if (remove(path) != 0) {
        printf("Error deleting user file\n");
        return;
    }

    // Update the userlist
    FILE *fp = fopen("data/userlist.bin", "rb");
    FILE *tmp = fopen("tmp.bin", "wb");
    if (fp == NULL || tmp == NULL) {
        printf("Error updating userlist\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, name) != 0) {
            fwrite(&user, sizeof(User), 1, tmp);
        }
    }

    fclose(fp);
    fclose(tmp);

    remove("data/userlist.bin");
    rename("tmp.bin", "data/userlist.bin");

    printf("User deleted successfully\n");
}

// Change the master password
void changeMaster(const char *name, const char *newPassword) {
    FILE *fp = fopen("data/userlist.bin", "rb+");
    if (fp == NULL) {
        printf("Error opening userlist file\n");
        return;
    }

    User user;
    long pos = 0;

    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, name) == 0) {
            strncpy(user.password, newPassword, sizeof(user.password));
            fseek(fp, pos, SEEK_SET); // Move back to the start of the record
            fwrite(&user, sizeof(User), 1, fp); // Overwrite the record
            break;
        }
        pos = ftell(fp); // Save the current position
    }

    fclose(fp);
    printf("Master password changed successfully\n");
}
