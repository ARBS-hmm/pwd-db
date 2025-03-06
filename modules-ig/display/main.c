#include <stdio.h>
#include <string.h>
#include <unistd.h>

void editAndRead(char *string);

int main(){
  char string[10];

  printf("\033[2J\033[H");
  printf("Enter a string\n");
  scanf("%s", string);
  char test = getchar();
  setbuf(stdin,NULL);

  editAndRead(string);
  printf("%s\n", string);

  return 0;
}

void editAndRead(char *string){
  char localcopy[10];
  char input;
  int len = 0;
  int asciiInput;

  while (string[len] != '\0'){
    localcopy[len] = string[len];
    len++;
  }
  printf("len = %d\n", len);

idk:
  setbuf(stdin,NULL);
  len =0;
  while (localcopy[len] != '\0'){
    len++;
  }
  printf("\nlen = %d\n", len);
  //localcopy[len] = '\0';
  printf("enter something\n");

  input = getchar();
  printf("input = %c\n", input);
  setbuf(stdin,NULL);
  //clear the dumb \n

  if (input == 'b') {
    localcopy[len-1] = '\0';
    len--;

    printf("\033[2J\033[H");
    printf("%s", localcopy);
    goto idk;
  }
  else if (input == 'z') {
    strcpy(localcopy, string);
    return;
  }
  else {
    localcopy[len] = input;
    printf("%s", localcopy);
    goto idk;
  }
  char ch=getchar();
}
