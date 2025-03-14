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
    char pwd[10];  // Increase size if needed
    printf("Enter a master password: ");  // Print the prompt correctly
    scanf("%s", pwd);  // Use "%s" to read a string into pwd
    printf("User created successfully\n");
    fclose(fp);

    fp = fopen("data/userlist.txt","a");
  fprintf(fp, "%s %s %d\n", name, pwd,1); //not 0 here ...
  fclose(fp);
    return;
}

void renameHelperig(char path[], char searchKey[],char new[]){
    FILE *tmp;
    FILE *fp;

    char key[10];
    char pwd[10];
  int enabled;

  printf("opening tmp\n");
    tmp = fopen("tmp.txt", "w");
    if (tmp == NULL) {
        printf("Error opening temporary file for writing\n");
        return;
    }

  printf("opening log file\n");
  printf("path = %s\n", path);
    //fp = fopen(path, "r");
  //so this doesnt work for some reason.... why a seg fault?
    fp = fopen("data/userlist.txt", "r");
    if (fp == NULL) {
        printf("Error opening original file for reading\n");
        return;
    }
  printf("am i here?\n");

    while (fscanf(fp, "%s %s %d\n", key, pwd,&enabled) == 3) { // & are important... 
        if (strcmp(key, searchKey) == 0) {
      printf("im scanning ig\n");
            fprintf(tmp, "%s %s %d\n", key, new,enabled);
        } else {
            fprintf(tmp, "%s %s %d\n", key, pwd,enabled);
        }
    }

    fclose(fp);
    fclose(tmp);

    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Error opening original file for writing\n");
        return;
    }

    tmp = fopen("tmp.txt", "r");
    if (tmp == NULL) {
        printf("Error opening temporary file for reading\n");
        fclose(fp); // Ensure we close fp before returning
        return;
    }

    char ch;
    while ((ch = fgetc(tmp)) != EOF) {
	//printf("writing\n");
        fputc(ch, fp);
    }

    fclose(tmp);
    fclose(fp);

    //remove("tmp.txt");
    printf("updated successfully\n");
  return;
};

void renameUser(char name[10]) {
    char newName[10];

    if (checkUserExistence(name) == 0) {
        printf("This user doesnt exists.\n");
        return;
    }
    printf("Enter new name for the user: ");
    scanf("%s", newName);  // Fixed incorrect use of scanf

    char oldPath[40];
    char newPath[40];
    char ext[10] = ".txt";
    char initial[20] = "data/users/";

    strcpy(oldPath, initial);
    strcat(oldPath,name);
    strcat(oldPath, ext);

    strcpy(newPath, initial);
    strcat(newPath,newName);
    strcat(newPath, ext);

    if (rename(oldPath, newPath) != 0) {
        printf("Error renaming user\n");
	printf("oldPath = %s\n", oldPath);
	printf("newPath = %s\n", newPath);
        return;
    }
	printf("oldPath = %s\n", oldPath);
	printf("newPath = %s\n", newPath);

    printf("calling helper\n");
    renameHelperig("data/userlist.txt",name,newName); 
    printf("User renamed successfully\n");
  return;
}

void deleteHelper(char path[],char searchKey[]){
    FILE *tmp;
    FILE *fp;

    char key[10];
    char pwd[10];
  int enabled;

    tmp = fopen("tmp.txt", "w");
    if (tmp == NULL) {
        printf("Error opening temporary file for writing\n");
        return;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening original file for reading\n");
        fclose(tmp); // Ensure we close tmp before returning
        return;
    }

    while (fscanf(fp, "%s %s\n", key, pwd,enabled) == 3) {
        if (strcmp(key, searchKey) == 0) {
      // Nothing to do here...
        } else {
            fprintf(tmp, "%s %s\n", key, pwd,enabled);
        }
    }

    fclose(fp);
    fclose(tmp);

    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Error opening original file for writing\n");
        return;
    }

    tmp = fopen("tmp.txt", "r");
    if (tmp == NULL) {
        printf("Error opening temporary file for reading\n");
        fclose(fp); // Ensure we close fp before returning
        return;
    }

    char ch;
    while ((ch = fgetc(tmp)) != EOF) {
        fputc(ch, fp);
    }

    fclose(tmp);
    fclose(fp);

    remove("tmp.txt");
  return;
};

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

    deleteHelper("data/userlist.txt",name);
    printf("User deleted successfully\n");
}

void changeMaster(char name[],char new[]){
    FILE *tmp;
    FILE *fp;

    char key[10];
    char pwd[10];
  int enabled;

    tmp = fopen("tmp.txt", "w");
    if (tmp == NULL) {
        printf("Error opening temporary file for writing\n");
        return;
    }

    fp = fopen("data/userlist.txt", "r");
    if (fp == NULL) {
        printf("Error opening original file for reading\n");
        fclose(tmp); // Ensure we close tmp before returning
        return;
    }

    while (fscanf(fp, "%s %s %d\n", key, pwd,enabled) == 3) {
        if (strcmp(key, name) == 0) {
	    fprintf(tmp, "%s %s %d\n",key,new,enabled);
        } else {
            fprintf(tmp, "%s %s %d\n", key, pwd,enabled);
        }
    }

    fclose(fp);
    fclose(tmp);

    fp = fopen("data/userlist.txt", "w");
    if (fp == NULL) {
        printf("Error opening original file for writing\n");
        return;
    }

    tmp = fopen("tmp.txt", "r");
    if (tmp == NULL) {
        printf("Error opening temporary file for reading\n");
        fclose(fp); // Ensure we close fp before returning
        return;
    }

    char ch;
    while ((ch = fgetc(tmp)) != EOF) {
        fputc(ch, fp);
    }

    fclose(tmp);
    fclose(fp);

    remove("tmp.txt");
  return;
}
