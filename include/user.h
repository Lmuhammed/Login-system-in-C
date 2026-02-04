#ifndef _USER_H_
#define _USER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sodium.h>
#include "../include/globals.h"
#include "../include/helpers.h"

bool pwd_hash(const char *clear_text, size_t clear_text_len,char *hash);
bool pwd_verify(const char *stored_hash,char *input_password, size_t input_password_len );
void create_user(FILE * file,char *fullName,char *username);
bool login(FILE *file,struct User *u,char *username);
#endif
