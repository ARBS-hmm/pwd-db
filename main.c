#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//USER DEFINED HEADERS
#include"include/display/display.h"
#include"include/fileHandlers/io.h"
#include"include/fileHandlers/user.h"
#include"include/security/security.h"

int query(const char *path, const char *searchKey) {
    FILE *fp = fopen(path, "rb"); // Open the file in read binary mode
    if (fp == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return 0; // File could not be opened
    }

    User user;
    int found = 0;

    // Read the file record by record
    while (fread(&user, sizeof(User), 1, fp) == 1) {
        if (strcmp(user.username, searchKey) == 0) {
      //      printf("Password for user '%s': %s\n", user.username, user.password);
            found = 1;
            break; // Exit the loop once the user is found
        }
    }

    fclose(fp); // Close the file

    if (!found) {
        printf("No such entry found for user '%s'.\n", searchKey);
    }

    return found; // Return 1 if found, 0 otherwise
}

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

  strcpy(extension, ".bin");
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
      readit(path,args); //test
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
      if (query("data/userlist.bin",args)==0){
	printf("User doesnt exist....\n");
	continue;
      }
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

