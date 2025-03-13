#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> //handles input output mode for unix terminals
#include <unistd.h> //handles syscalls for unix or POSIX compliant OS

#define MAX_INPUT_LENGTH 1024

// Function to set terminal to raw mode
void set_raw_mode(struct termios *orig_termios) {
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Function to restore terminal to original mode
void restore_terminal(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

char *edit(const char *initial_text) {
    struct termios orig_termios;
    char *input = malloc(MAX_INPUT_LENGTH);
    int input_len = strlen(initial_text);
    char c;

    if (!input) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy initial text to input buffer
    strncpy(input, initial_text, MAX_INPUT_LENGTH);
    input[MAX_INPUT_LENGTH - 1] = '\0';

    // Set terminal to raw mode
    set_raw_mode(&orig_termios);

    // Display initial text
    write(STDOUT_FILENO, input, input_len);

    while (1) {
        // Read a single character
        read(STDIN_FILENO, &c, 1);

        if (c == '\n' || c == '\r') {
            // Enter key pressed, exit the loop
            break;
        } else if (c == 127 || c == 8) {
            // Backspace key pressed
            if (input_len > 0) {
                // Move cursor back, overwrite character with space, move cursor back again
                write(STDOUT_FILENO, "\b \b", 3);
                input_len--;
            }
        } else if (input_len < MAX_INPUT_LENGTH - 1) {
            // Append character to input
            input[input_len++] = c;
            write(STDOUT_FILENO, &c, 1);
        }
    }

    // Null-terminate the input
    input[input_len] = '\0';

    // Restore terminal to original mode
    restore_terminal(&orig_termios);

    // Print a newline after editing is done
    write(STDOUT_FILENO, "\n", 1);

    return input;
}

int main() {
    char original_string[MAX_INPUT_LENGTH] = "Edit this text: ";
    char *edited_string;

    printf("Original string: %s\n", original_string);

    // Edit the string
    edited_string = edit(original_string);
    strcpy(original_string, edited_string);
    free(edited_string);

    printf("Updated string: %s\n", original_string);

    return 0;
}
