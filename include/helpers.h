#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/globals.h"


void error_msg(char *msg);
bool is_file_empty(char *filename);
int read_int (char * msg);
int generate_id (void);
bool is_id_unique(int id,FILE * file);
bool is_username_unique(char * username,FILE * file);



#endif
