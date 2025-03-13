#ifndef IO_H
#define IO_H

char* getpwd(char path[], char searchKey[]);

// Function to create an entry in the password file
void create(char path[], char key[], char pwd[]);

// Function to read an entry from the password file
void readit(char path[], char searchKey[]);

// Function to update the password for an existing entry
void update(char path[], char searchKey[10], char new[10]);

// Function to delete an entry from the password file
void delete(char path[], char searchKey[]);

#endif // IO_H
