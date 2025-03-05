#include <stdio.h>
#include <string.h>
#include <unistd.h>

void editAndRead(char *string[]);

int main(){
  char string[10];

  printf("Enter a string\n");
  scanf("%s",&string);

  editAndRead(&string);
  printf("%s\n",string);

  return 0;
}

void editAndRead(char *string[]){
  printf("%s\n",string);

  int len = 0
  while (string[len]!="\0"){
    localcopy[len]=string[len];
    len++;
  };
  printf("%s\n",localcopy);

  input = getchar();
  asciiInput = (int)input;
  if (asciiInput == "pending code"){
    localcopy[len-1] = '\0';
    printf("\r%s\n", "                           ");
    printf("%s\n", localcopy);
    return
  }
  else if (asciiInput = "pending code") {
    strcpy(localcopy,string);
    return
  }
}
