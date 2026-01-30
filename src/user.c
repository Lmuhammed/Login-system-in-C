#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/user.h"

void create_user(FILE * file,char *fullName,char *username){
    struct User u={0};
    bool id_unique= false;
    do{
    u.id=generate_id();
    id_unique=is_id_unique(u.id,file);
    }while(id_unique == false);
    strncpy(u.fullName,fullName,MAX_STRS);
    strncpy(u.username,username,MAX_STRS);
    //check if username unique
    if (is_username_unique(u.username,file)){
    //-1 ) username unique
    printf("Password : ");
    read_password(u.password, sizeof u.password);
    fwrite(&u, sizeof(u) , 1 , file);
    fflush(file);
    rewind(file);
    printf("New user added\n");
    }
    //-2 ) username used
    else 
    error_msg("Username used , chose another one please");
}

bool login(FILE *file,struct User *u,char *username){
    rewind(file);
    int found=0;
    char password[MAX_STRS]={0};
    printf("Password : ");
    read_password(password, sizeof password);
    while(fread(u, sizeof(struct User) , 1 , file)){
   // printf ("usr : '%s'\n",u->username);
   // printf ("userArgv : '%s'\n",username);
    if(strcmp(u->username,username)== 0){
    //check if password correct
    if(strcmp(u->password,password)== 0){
    found=1;
    break;
    }
    }
    }
    return found == 1;
}
