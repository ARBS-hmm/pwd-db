
#ifndef USER_H
#define USER_H

// Function to check if a user exists by checking the corresponding file
int checkUserExistence(char name[10]);

// Function to create a user (by creating a file and logging credentials)
void createUser(char name[10]);

// Function to rename an existing user
void renameUser(char name[10]);

// Function to delete a user (by removing the user file)
void deleteUser(char name[10]);

void changeMaster(char name[],char new[]);

#endif // USER_H
