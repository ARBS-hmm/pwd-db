#include <stdio.h>
#include <string.h>

// Define a structure for user credentials
typedef struct {
    char username[50];
    char password[50];
    int enabled;
} User;

// Function to log authentication attempts
int authLog(char name[10], int success) {
    static int tries = 0;

    printf("tries = %d\n", tries);
    if (success == 1) {
        tries = 0; // Reset tries on successful authentication
        return 1;
    } else if (success == 0) {
        tries++;
        printf("tries now = %d\n", tries);
    }

    return tries;
}

// Function to disable an account
void disableAccount(const char *username) {
    FILE *fp = fopen("data/userlist.bin", "rb+");
    if (fp == NULL) {
        printf("Error: Unable to open user credentials file.\n");
        return;
    }

    User user;
    long pos = 0;

    // Find the user and update their status
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(username, user.username) == 0) {
            user.enabled = 0; // Disable the account
            fseek(fp, pos, SEEK_SET); // Move back to the start of the record
            fwrite(&user, sizeof(User), 1, fp); // Overwrite the record
            break;
        }
        pos = ftell(fp); // Save the current position
    }

    fclose(fp);
}

// Function to authenticate a user
int authenticator(char *username, char *password) {
    FILE *fp = fopen("data/userlist.bin", "rb");
    if (fp == NULL) {
        printf("Error: Unable to open user credentials file.\n");
        return 0; // Failure
    }

    User user;
    int found = 0;

    // Read users from the binary file
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(username, user.username) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User not found.\n");
        fclose(fp);
        return 0; // Failure
    }

    if (user.enabled == 0) {
        printf("Account Disabled\n");
        fclose(fp);
        return 0; // Failure
    }

    if (strcmp(user.password, password) != 0) {
        printf("Wrong password\n");
        int tries = authLog(username, 0);
        if (tries == 5) {
            // Log the breach attempt
            FILE *logFile = fopen("data/log/security-warnings.txt", "a");
            if (logFile) {
                fprintf(logFile, "Someone attempted to breach %s\nSetting account to locked\n", username);
                fclose(logFile);
            }

            // Disable the account
            disableAccount(username);
            printf("Account locked due to too many failed attempts.\n");
        }
        fclose(fp);
        return 0; // Failure
    }

    // Successful authentication
    int tmp = authLog(username, 1); // Reset tries
    fclose(fp);
    return 1; // Success
}

// Function to create a sample userlist.bin file (for testing)
void createUserFile() {
    FILE *fp = fopen("data/userlist.bin", "wb");
    if (fp == NULL) {
        perror("Error creating user file");
        return;
    }

    User users[] = {
        {"user1", "password1", 1},
        {"user2", "password2", 1},
        {"user3", "password3", 0} // Disabled account
    };

    size_t num_users = sizeof(users) / sizeof(users[0]);
    fwrite(users, sizeof(User), num_users, fp);

    fclose(fp);
}
