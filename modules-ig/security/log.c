#include<stdio.h>
#include<string.h>

int authLog(char name[10], int success){
  static int tries=0;

  printf("tries = %d\n", tries);
  if (success==1){
    int tries =0;
    return 1;
  }
  else if (success == 0){
    tries++;
    printf("tries now = %d\n", tries);
  }

  return tries;
};

void disableAccount(const char *username) {
    FILE *fp, *tempFile;
    char file_username[50];
    char file_password[50];
    int enabled;

    fp = fopen("data/userlist.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open user credentials file.\n");
        return;
    }

    tempFile = fopen("data/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    // Read the userlist file and update the disabled status
    while (fscanf(fp, "%s %s %d", file_username, file_password, &enabled) == 3) {
        if (strcmp(username, file_username) == 0) {
            fprintf(tempFile, "%s %s %d\n", file_username, file_password, 0); // Disable account
        } else {
            fprintf(tempFile, "%s %s %d\n", file_username, file_password, enabled);
        }
    }

    fclose(fp);
    fclose(tempFile);

    // Replace the original file with the updated file
    remove("data/userlist.txt");
    rename("data/temp.txt", "data/userlist.txt");
}

int authenticator(char *username,char *password) {
    FILE *fp;
    char file_username[50];
    char file_password[50];
    int enabled;

    fp = fopen("data/userlist.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open user credentials file.\n");
        return 0; // Failure
    }

    // Find the entry
    int found = 0;
    while (fscanf(fp, "%s %s %d", file_username, file_password, &enabled) == 3) {
        if (strcmp(username, file_username) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User not found.\n");
        fclose(fp);
        return 0; // Failure
    }

    if (enabled == 0) {
        printf("Account Disabled\n");
        fclose(fp);
        return 0; // Failure
    }

    if (strcmp(file_password, password) != 0) {
        printf("Wrong password\n");
	int tries;
        tries = authLog(username, 0);
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
  int tmp;
  tmp = authLog(username, 1); // Reset tries
  fclose(fp);
  return 1; // Success
}

//before login ig?
//serial.txt write

int main(){
  return 0;
}

