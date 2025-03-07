#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//USER DEFINED HEADERS
#include"include/display/display.h"
#include"include/fileHandlers/io.h"
#include"include/fileHandlers/user.h"

int query(char path[40], char searchKey[10]);

void get(char path[40], char searchKey[10]){
  if (query(path,searchKey)==0){
    printf("No such entry exists\n");
    printf("consider adding one\n");
    return;
  }
  return;
};

void startSession(char name[]){
  FILE *fp;
  char path[40];
  char extension[10];
  char cmd[10], args[10];
  char key[10];
  char pwd[10];

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
  fclose(fp);


  printf("Welcome %s\n", name);
  while(1){
    printf("%s> ",name);
    scanf("%s %s", cmd, args);
    if (strcmp(cmd,"check")==0){
    //  printf("hmm\n");
      get(path,args); //test
    }
    else if (strcmp(cmd,"logout")==0){
      return;
    }
    else if (strcmp(cmd,"add")==0){
      if (query(path,args)==0){
	printf("Enter a password\n");
	scanf("%s",pwd);
	create(path,args,pwd);
      }
      else{
	printf("this entry already exits.. u need to update it\n");
      }
    }
    else if (strcmp(cmd,"update")==0){
      //printf("Update PENDING\n");
      printf("Enter new password\n");
      char new[10];
      scanf("%s",new);
      update(path,args,new);

      //find(args ig)
      //term(input);
      //update(path,key,newentry);

      // 	check if it exists ig? and then overwrite it.
      //syslog(name, key, pwd, "user has updated their password");
    }
    else if (strcmp(cmd,"del")==0){
      delete(path,args);
      printf("Deleted\n");
    }
    else{
      printf("invalid option try something else...\n");
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

    if (strcmp(command,"login")==0){ //R U
      startSession(args);
    }
    else if(strcmp(command,"add")==0){ //C
      createUser(args);
      //HERE PENDING
    }
    else if(strcmp(command,"delete")==0){ //D
      //reason = requestRemove(args);
      //syslog(args,reason,"delete account");
      printf("your request has been sent\n");
      printf("waiting for approval\n");
    }
    else if(strcmp(command, "exit")==0){
      return 0;
    }
    else {
      printf("No such option exists here...\n");
    }
  }
  return 0;
}

int query(char path[40],char searchKey[10]){
  FILE *fp;
  char key[10];
  char pwd[10];

  //printf("path = %s\n", path);
  fp = fopen(path, "r");
  if (fp == NULL){
    return 0;
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
      return 1;
    };
    i++;
  };
  //printf("No such entry\n");
  //printf("consider adding one\n");
  return 0;
}

