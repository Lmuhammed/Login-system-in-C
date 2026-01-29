#ifndef _USER_H_
#define _USER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/globals.h"
#include "../include/helpers.h"

void create_user(FILE * file,char *fullName,char *username);
bool login(FILE *file,struct User *u,char *username);
#endif
