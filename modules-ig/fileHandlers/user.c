#include <stdio.h>
#include <string.h>

#include"io.h"

// users/data
int checkUserExistence(char name[10]){
  char path[40] = "data/users/";
  char ext[10] = ".txt";
  strcat(path,name);
  strcat(path,ext);

  printf("checking path = %s\n", path);

  FILE *fp;
  fp = fopen(path,"r");

  if (fp == NULL){
    //THE FILE NEVER OPENED HERE...
    //fclose(fp);
    return 0;
  }
  else {
    fclose(fp);
    return 1;
  }
}

void createUser(char name[10]){

  char path[40] = "data/users/";
  char ext[10] = ".txt";
  strcat(path,name);
  strcat(path,ext);
    printf("path = %s\n", path);

    if (checkUserExistence(name) == 1) {
        printf("User already exists\n");
        return;
    }

    FILE *fp;
    fp = fopen(path, "w");

    if (fp == NULL) {
        printf("Error creating user file\n");
        return;
    }

    FILE *log = fopen("data/log/permit-rules.txt", "a");
    if (log == NULL) {
        printf("Error opening log file\n");
        fclose(fp);  // Make sure to close the user file before returning
        return;
    }

    char pwd[10];  // Increase size if needed
    printf("Enter a master password: ");  // Print the prompt correctly
    scanf("%s", pwd);  // Use "%s" to read a string into pwd

    fprintf(log, "%s %s %s\n", name, pwd, "free");
    fclose(log);

    printf("User created successfully\n");
    fclose(fp);
    return;
}

void renameUser(char name[10]) {
    char newName[10];
    printf("Enter new name for the user: ");
    scanf("%s", newName);  // Fixed incorrect use of scanf

    if (checkUserExistence(newName) == 0) {
        printf("This user doesnt exists.\n");
        return;
    }

    char oldPath[10];
    char newPath[10];
    char ext[10] = ".txt";
    
    strcpy(oldPath, name);
    strcat(oldPath, ext);

    strcpy(newPath, newName);
    strcat(newPath, ext);

    if (rename(oldPath, newPath) != 0) {
        printf("Error renaming user\n");
        return;
    }

    update("data/users/permit-rules.txt",name,newName); 
    printf("User renamed successfully\n");
}

void deleteUser(char name[10]) {
    char path[10];
    char ext[10] = ".txt";
    strcpy(path, name);
    strcat(path, ext);

    if (checkUserExistence(name) == 0) {
        printf("User does not exist\n");
        return;
    }

    if (remove(path) != 0) {
        printf("Error deleting user file\n");
        return;
    }

    delete("data/users/permit-rules.txt",name);
    printf("User deleted successfully\n");
}

