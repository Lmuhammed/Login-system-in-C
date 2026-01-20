#ifndef _USER_H_
#define _USER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/globals.h"
#include "../include/helpers.h"

void create_user(FILE * file);
bool login(FILE * file,struct User *u);

#endif
