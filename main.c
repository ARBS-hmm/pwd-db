#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//USER DEFINED HEADERS
#include"include/display/display.h"
#include"include/fileHandlers/io.h"
#include"include/fileHandlers/user.h"
#include"include/security/security.h"

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
  char confirm[10];
  char newPass[10];
  //Dont declare things inside a loop.... causes Segmentation faults???

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
      if(strcmp(args,"fast")==0){
	return;
      }
      else{
	printf("Use \'logout fast\' to exit\n");
      }
    }
    else if(strcmp(cmd,"change")==0){
      if(strcmp(args,"master")==0){

	printf("Enter current master password to confirm\n");
	char master[10];
	scanf("%s",master);
	int changecode;
	changecode = authenticator(name,master);
	if (changecode ==0){
	  printf("wrong password entered\n");
	  goto skipif;
	}
	else {
	  printf("Enter a new password\n");
	  scanf("%s",newPass);
	  printf("Confirm by typing again\n");
	  scanf("%s",confirm);
	  if(strcmp(newPass,confirm)==0){
	    printf("Changing\n");
	    changeMaster(name,newPass);
	  }
	  else {
	    printf("u entered a different pass 2nd time\n Failed\n");
	    goto skipif;
	  }
	}
      }
      else {
	printf("pls use \'change master\' not what u typed here\n");
      }
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
      //printf("Enter new password: ");
      //WHY IS THIS THING ACTING WEIRD????
      char *current = getpwd(path,args);
      char *new = edit(current);
      update(path, args, new);     
    }
    else if (strcmp(cmd,"delete")==0){
      delete(path,args);
      printf("Deleted\n");
    }
    else{
      printf("invalid option try something else...\n");
    }
  skipif:
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
      printf("\nEnter your master password:\n");
      char pwd[10];
      int code;
      scanf("%s",pwd);
      code = authenticator(args,pwd);
      if (code==0) {
	printf("U CANT LOGIN\n");
      }
      else{
	startSession(args);
	printf("session end\n");
      }
    }
    else if(strcmp(command,"add")==0){ //C
      createUser(args);
    }
    else if(strcmp(command,"rename")==0){
      renameUser(args);
    }
    else if(strcmp(command,"delete")==0){ //D
      deleteUser(args);
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

