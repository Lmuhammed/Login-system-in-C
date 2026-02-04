#ifndef _GLOB_
#define _GLOB_

#define MAX_STRS 40
#define USERNAME_MIN_LENGTH 5
#define PWD_MIN_LENGTH 6
#define PWD_MAX_LENGTH 255 //later make it #define PWD_MAX_LENGTH crypto_pwhash_STRBYTES
#define FULLNAME_MIN_LENGTH 6


struct User {
int id;
char fullName[MAX_STRS];
char username[MAX_STRS];
char password[PWD_MAX_LENGTH];

};

#endif

