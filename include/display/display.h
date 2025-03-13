#ifndef DISPLAY_H
#define DISPLAY_H

#include <termios.h> // for termios structure
#include <unistd.h>  // for syscalls

// Define maximum input length
#define MAX_INPUT_LENGTH 1024

// Function to set terminal to raw mode
void set_raw_mode(struct termios *orig_termios);

// Function to restore terminal to original mode
void restore_terminal(struct termios *orig_termios);

// Function to handle user input for text editing in raw mode
char *edit(const char *initial_text);

#endif // DISPLAY_H
