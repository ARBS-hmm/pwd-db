#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void query(char searchKey[], char path[]);
void startSession(char name[]){
  FILE *fp;
  char path[30];
  char extension[10];
  char cmd[10], args[10];
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
    //REPL here ig??
    fclose(fp);
    scanf("%s %s", cmd, args);
    if (strcmp(cmd,"check")==0){
    //  printf("hmm\n");
      query(args,path); //test
    }
    else if (strcmp(cmd,"update")==0){
      printf("Update PENDING\n");
      fopen(path,"r");
  // 	update(key,path);
      // 	check if it exists ig? and then overwrite it.
      //syslog(name, key, pwd, "user has updated their password");
    }
    else if (strcmp(cmd,"del")==0){
      printf("Delete PENDING\n");
      fopen(path,"r");
    }
    else{
      printf("invalid option try something else...\n");
      fopen(path,"r");
    }
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
