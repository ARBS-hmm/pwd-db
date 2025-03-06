#include<stdio.h>

void datalog(name,key,pwd,action);
void syslog(name); //rename of user, delete of user, ...idk

void authLog(char name[10], int success){
  static int tries=0;
  if (success==1){
    return;
  }
  if (success == 0){
    tries++
  }

  if(tries==5){
    //report attempts to breach
    //account lock
  }
  return;
};

//before login ig?
//serial.txt write
void request(char name[10], char request[10]);

int main(){
  return 0;
}
