#include<stdio.h>

void datalog(char name[],char key[],char pwd[],char action[]){
  FILE *fp;
  fp = fopen("data/log/serial.txt","a");

  if(strcmp(action,"create")==0){
    fprintf(fp, "%s added new entry: %s -> %s\n", name, key,pwd);
  }
  if( strcmp(action,"update")==0){
    fprintf(fp, "%s changed the entry: %s -> %s\n", name, key,pwd);
  }
  else if(strcmp(action,"delete")==0){
    fprintf(fp, "%s changed the entry: %s\n", name, key);
  }
  else {
    printf("????????????\n")
  }
}

void syslog(char name[],char log[]){
  FILE *fp;
  fp = fopen("data/log/serial.txt","a");
  fprintf(fp, "%s: %s\n",name, log);
} 

void authLog(char name[10], int success){
  static int tries=0;
  if (success==1){
    return;
  }
  else if (success == 0){
    tries++;
  }

  if(tries==5){
    FILE *fp;
    fp = fopen("data/log/serial.txt","a");
    fprintf(fp, "someone atempted to breach %s\n Setting account to locked",name);
    update("data/log/permit-rules.txt",name,"locked")
    fclose(fp);
  }
  return;
};

//before login ig?
//serial.txt write

int main(){
  return 0;
}
