
#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>
// Function prototypes
int authLog(char name[10], int success);
void disableAccount(const char *username);
int authenticator(char *username, char *password);
void createUserFile(); // This is for testing purposes, to create a sample user list

#endif // SECURITY_H
