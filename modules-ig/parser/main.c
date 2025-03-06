#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user {
  char name[10];
  char address[10];
  int roll;
};

int main(){
  char name[10];
  char address[10];
  int roll;

  FILE *fp;
  fp = fopen("test/csv.txt", "r");
  if (fp == NULL){
    printf("Error\n");
    exit(1);
  }
  struct user list[10];

  char search[10];
  printf("Search for?\n");
  scanf("%s",search);

  int i=0;
  while(fscanf(fp,"%s %s %d\n",name,address,&roll)==3){
    printf("name = %s\n", name);
    if (strcmp(name,search)==0){
      printf("Found\n");
      printf("name = %s\n", name);
      printf("address = %s\n", address);
      printf("roll = %d\n", roll);
      i++;
      printf("line number = %d\n", i);
      i--;
    }
    i++;
  }

  fclose(fp);
  return 0;
}
