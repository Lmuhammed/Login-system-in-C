#ifndef _LIB_H_
#define _LIB_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

#define MAX_USERNAME 10
#define MAX_PWD 10

struct User {
int id;
char fullName[20];
char username[MAX_USERNAME];
char password[MAX_PWD];

};
void error_msg(char *msg);
bool is_file_empty(char *filename);
void create_user(FILE * file);
bool login(FILE * file,struct User *u);
int read_int (char * msg);
int generate_id (void);
bool is_id_unique(int id,FILE * file);


#endif
