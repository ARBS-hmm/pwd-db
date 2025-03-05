#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void query(char searchKey[], char path[]);
void startSession(char name[]){
  FILE *fp;
  char path[30];
  char extension[10];
  char prompt[10];
  char key[10];

  strcpy(extension, ".txt");
  strcpy(path, "data/users/");  // Copy "data/users" to path first
  strcat(path, name);          // Then concatenate the name to it
  strcat(path,extension);

  printf("path = %s\n", path);
  fp = fopen(path,"r");
  if (fp == NULL){
    printf("The requested user doesnt exist\n");
    printf("Use \"add <username>\"\n");
    return;
  }
  printf("Welcome %s\n", name);
  while(1){
    printf("%s> ",name);
    scanf("%s", key);
    //REPL here ig??
    fclose(fp);
    query(key,path); //test
  }
}

int main(){
  char command[10];
  char args[10];
  char prompt[10] = "hmm> ";

  while(1){
    printf("%s", prompt);
    scanf("%s %s", command,args);

    if (strcmp(command,"check")==0){ //R U
      startSession(args);
    }
    else if(strcmp(command,"add")==0){ //C
      //addUser(args);
    }
    else if(strcmp(command,"delete")==0){ //D
      //requestRemove(args);
    }
    else {
      printf("No such option exists here...\n");
    }
  }
  return 0;
}

void query(char searchKey[], char path[]){
  FILE *fp;
  char key[10];
  char pwd[10];

  printf("path = %s\n", path);
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
      printf("Found\n");
      i++;
      printf("line number = %d\n", i);
      i--;
      return;
    };
    i++;
  };
  printf("No such entry\n");
  printf("consider adding one\n");
  return;
}
