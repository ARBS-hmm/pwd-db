#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* getpwd(char path[], char searchKey[]) {
    FILE *fp;
    char key[10];
    char pwd[10];

    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error\n");
        exit(1);
    }

    while (fscanf(fp, "%s %s\n", key, pwd) == 2) {
        if (strcmp(key, searchKey) == 0) {
            // Dynamically allocate memory for the password and return it
            char *password = malloc(strlen(pwd) + 1);
            if (password != NULL) {
                strcpy(password, pwd);
                fclose(fp);
                return password; // Return the password
            }
        }
    }

    fclose(fp);
    return NULL; // If not found, return NULL
}

void create(char path[],char key[], char pwd[]){
  FILE *fp;
  fp =fopen(path,"a");
  fprintf(fp, "%s %s\n",key,pwd);
  fclose(fp);
  return;
}

void readit(char path[],char searchKey[]){
  FILE *fp;
  char key[10];
  char pwd[10];

  //printf("path = %s\n", path);
  fp = fopen(path, "r");
  if (fp == NULL){
    printf("Error\n");
    exit(1);
  }

  int i=0;
  //CHECK IF THE FILE IS EMPTY FIRST HERE......
  while(fscanf(fp,"%s %s\n",key,pwd)==2){
    //printf("key = %s\n", key);
    if (strcmp(key,searchKey)==0){
      printf("password: %s\n", pwd);
      i++;
      //printf("line number = %d\n", i);
      i--;
      return;
    };
    i++;
  };
  printf("No such entry\n");
  printf("consider adding one\n");
  return;
}

void update(char path[], char searchKey[10],char new[10]){
    FILE *tmp;
    FILE *fp;

    char key[10];
    char pwd[10];

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

    while (fscanf(fp, "%s %s\n", key, pwd) == 2) {
        if (strcmp(key, searchKey) == 0) {
            fprintf(tmp, "%s %s\n", key, new);
        } else {
            fprintf(tmp, "%s %s\n", key, pwd);
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
    printf("updated successfully\n");
  return;
};

void delete(char path[], char searchKey[]){
  FILE *tmp;
  FILE *fp;

  char key[10];
  char pwd[10];
  char new[10];

  tmp = fopen("tmp.txt","w");
  fp = fopen(path,"r+"); //w+ maybe? // no r+?

  while(fscanf(fp, "%s %s\n",key,pwd)==2){
    if (strcmp(key,searchKey)==0){
      continue;
    }
    else{
      fprintf(tmp, "%s %s\n",key,pwd);
    }
  }
  fclose(fp);
  fclose(tmp);
  fp = fopen(path,"w");
  tmp = fopen("tmp.txt","r");

  char ch;
  while ((ch = fgetc(tmp)) != EOF) {
    fputc(ch, fp);
  }

  fclose(tmp);
  fclose(fp);
  remove("tmp.txt");
  return;
}

int main(){
  return 0;
}
