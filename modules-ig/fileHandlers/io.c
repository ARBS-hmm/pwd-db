#include<stdio.h>
#include<string.h>

void create(char path[],char key[], char pwd[]){
  FILE *fp
  fp =fopen(path,"a");
  fprintf(fp, "%s %s\n",key,pwd);
  fclose(fp);
}

void read(char path[],char searchKey[]){
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

void update(){
  //edit()
  return;
}

void delete(){
  //idk
  return;

}

int main(){
  return 0;
}
