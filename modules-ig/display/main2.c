//DOESNT WORK SOMEHOW
/*
 *
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termio.h>

#define BUFFER_SIZE 128

void editAndRead(char *string);
void clearInputBuffer();

void setTerminalMode();
void resetTerminalMode();

void idek(char *ch) {
    ssize_t n;
    
    // Set terminal to non-canonical mode
    setTerminalMode();

    // Read one character immediately after it is pressed
    n = read(STDIN_FILENO, ch, 1);  // Read one byte

    if (n > 0) {
        // Successfully read a character, now *ch holds the key
    }

    // Restore the terminal to its original settings
    resetTerminalMode();
}

int main(){
  char string[10];

  printf("\033[2J\033[H");
  printf("Enter a string: ");
  scanf("%s", string);
  
  // Clear any leftover characters (like newline) after scanf
  clearInputBuffer();

  editAndRead(string);
  printf("%s\n", string);

  return 0;
}

void editAndRead(char *string){
  char localcopy[10];
  char input;
  int len = 0;

  while (string[len] != '\0'){
    localcopy[len] = string[len];
    len++;
  }

  printf("len = %d\n", len);

  setTerminalMode();
idk:
  len = 0;
  while (localcopy[len] != '\0'){
    len++;
  }

  printf("\nlen = %d\n", len);
  printf("enter something: ");
  input = getchar();  // Using fgetc to read the character
  clearInputBuffer();  // Clear the leftover newline character
  
  printf("input = %c\n", input);

  if (input == '\b') {
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
    fflush(stdout);
    goto idk;
  }
}

// Function to clear the input buffer to remove any unwanted characters like '\n'
void clearInputBuffer() {
    while (getchar() != '\n'); // Consume characters until newline is found
}
void setTerminalMode() {
    struct termios newt;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &newt);

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    newt.c_cc[VMIN] = 1;  // Minimum number of bytes to read before returning
    newt.c_cc[VTIME] = 0; // No timeout (immediate detection)
    
    // Apply new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  return;
}

void resetTerminalMode() {
    struct termios oldt;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);

    // Restore canonical mode and echo
    oldt.c_lflag |= (ICANON | ECHO);

    // Apply old settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
