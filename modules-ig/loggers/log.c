#include<stdio.h>

//void datalog(char name[],char key[],char pwd[],char action[])
//void syslog(name); //rename of user, delete of user, ...idk
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
    // TO BE IMPLEMENTED IG
   // lock(name);
    fclose(fp);
  }
  return;
};

//before login ig?
//serial.txt write


//void request(char name[10], char request[10]);

int main(){
  return 0;
}
