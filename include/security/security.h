#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>
#include <string.h>

#define MAX_TRIES 5

// Function declarations
int authenticator(const char *username, const char *password);
int authLog(const char *username, int success);
void disableAccount(const char *username);

#endif // SECURITY_H
