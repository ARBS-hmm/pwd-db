#include <stdio.h>
#include <string.h>

#include"io.h"

// users/data
int checkUserExistence(char name[10]){
  char path[10];
  char ext[10] = ".txt";
  strcpy(path,name);
  strcat(path,ext);

  FILE *fp;
  fp = fopen(path,"r");

  if (fp = NULL){
    fclose(fp);
    return 0;
  }
  else {
    fclose(fp);
    return 1;
  }
}

void createUser(char name[10]){
  char path[10];
  char ext[10] = ".txt";
  strcpy(path,name);
  strcat(path,ext);

  if (checkUserExistence(name)==1){
    printf("User already exists\n");
    return;
  }
  FILE *fp;
  fp = fopen(path,"w");

  FILE *log;
  log = fopen("data/log/permit-rules.txt", "a");
  char pwd[10];
  scanf("\nEnter a master password\n",pwd);
  fprintf(log, "%s %s %s\n",name, pwd,"free");
  fclose(log);

  printf("Created\n");
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

