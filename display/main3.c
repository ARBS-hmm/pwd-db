#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<termio.h>

// Function to disable input buffering and echoing
void set_input_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);          // Get current terminal settings
    term.c_lflag &= ~(ICANON | ECHO);        // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set terminal settings
}

// Function to restore the original terminal settings
void reset_input_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);          // Get current terminal settings
    term.c_lflag |= (ICANON | ECHO);         // Enable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Restore terminal settings
}

void edit(char *string){
  char localCopy[10];
  int i,len;
  char ch;

  i=0;
  len=0;
  while(string[i]!='\n'){
    localCopy[i]=string[i];
    i++;
    len++;
  };

  set_input_mode();
idk_anymore: 
  i=0;
  len =0;
  while(localCopy[i]!='\n'){
    len++;
    i++;
  };

  ch = getchar();
  if(ch == '\b'){
    localCopy[len-1]= '\n';
    goto idk_anymore;
  }
  else if (ch == '\n'){
    strcpy(localCopy,string); 
    printf("%s\n",localCopy);
    return;
  }

}

int main(){
  char string[10];

  scanf("%s", string);
  setbuf(stdin,NULL);

  edit(string);
  printf("string = %s\n", string);
  return 0;
}
