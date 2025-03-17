#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the User structure (consistent with auth_lib.h and io.h)
typedef struct {
    char username[50];
    char password[50];
    int enabled; // Added for compatibility
} User;

// Function to get a user's password from a binary file
char* getpwd(const char *path, const char *searchKey) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    User user;
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, searchKey) == 0) {
            // Dynamically allocate memory for the password and return it
            char *password = malloc(strlen(user.password) + 1);
            if (password != NULL) {
                strcpy(password, user.password);
                fclose(fp);
                return password; // Return the password
            }
        }
    }

    fclose(fp);
    return NULL; // If not found, return NULL
}

void create(const char path[], const char key[], const char pwd[]) {
  printf("path = %s\n", path);
    // Open the file in append binary mode
    FILE *fp = fopen(path, "ab");
    if (fp == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    // Create a User structure and populate it
    User newUser;
    strncpy(newUser.username, key, sizeof(newUser.username) - 1); // Ensure null-termination
    newUser.username[sizeof(newUser.username) - 1] = '\0'; // Explicit null-termination
    strncpy(newUser.password, pwd, sizeof(newUser.password) - 1); // Ensure null-termination
    newUser.password[sizeof(newUser.password) - 1] = '\0'; // Explicit null-termination
    newUser.enabled = 1; // Enabled by default

    // Write the user data to the file
    size_t written = fwrite(&newUser, sizeof(User), 1, fp);
    if (written != 1) {
        printf("Error: Failed to write user data to the file.\n");
    } else {
        printf("New entry added...\n");
    }

    // Close the file
    fclose(fp);
}
// Function to read a user's password from a binary file
void readit(const char *path, const char *searchKey) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    User user;
    int found = 0;

    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, searchKey) == 0) {
            printf("Password: %s\n", user.password);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No such entry\n");
        printf("Consider adding one\n");
    }

    fclose(fp);
}

// Function to update a user's password in a binary file
void update(const char *path, const char *searchKey, const char *newPassword) {
    FILE *fp = fopen(path, "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    User user;
    long pos = 0;

    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, searchKey) == 0) {
            strncpy(user.password, newPassword, sizeof(user.password));
            fseek(fp, pos, SEEK_SET); // Move back to the start of the record
            fwrite(&user, sizeof(User), 1, fp); // Overwrite the record
            printf("Updated successfully\n");
            fclose(fp);
            return;
        }
        pos = ftell(fp); // Save the current position
    }

    fclose(fp);
    printf("Entry not found\n");
}

// Function to delete a user from a binary file
void delete(const char *path, const char *searchKey) {
    FILE *fp = fopen(path, "rb");
    FILE *tmp = fopen("tmp.bin", "wb");
    if (fp == NULL || tmp == NULL) {
        printf("Error opening file\n");
        return;
    }

    User user;
    int found = 0;

    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, searchKey) == 0) {
            found = 1;
            continue; // Skip writing this user to the temporary file
        }
        fwrite(&user, sizeof(User), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    if (!found) {
        printf("User not found\n");
        remove("tmp.bin");
        return;
    }

    remove(path);
    rename("tmp.bin", path);
    printf("Entry deleted successfully\n");
}

int main() {
    return 0;
}
