#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/user.h"

void create_user(FILE * file){
    struct User u;
    //u.id=read_int("Enter id : \n");
    bool id_unique= false;
    do{
    u.id=generate_id();
    id_unique=is_id_unique(u.id,file);
    }while(id_unique == false);

    printf("Full name : \n");
    fgets(u.fullName,sizeof(u.fullName),stdin);
    printf("Username :  \n");
    fgets(u.username,sizeof(u.username),stdin);
   //check if username unique
    //-1 ) username unique
    if (is_username_unique(u.username,file)){
    printf("Password :  \n");
    fgets(u.password,sizeof(u.password),stdin);
    fwrite(&u, sizeof(u) , 1 , file);
    fflush(file);
    rewind(file);
    printf("New account created\n");
    }
    //-2 ) username used
    else 
    error_msg("Username used , chose another one please");
    
}

bool login(FILE * file,struct User *u){
    rewind(file);
    char username[MAX_STRS],password[MAX_STRS];
    int found=0;
    printf("Login \n Enter username : ");
    fgets(username,sizeof(username),stdin);
    printf("Enter Password : ");
    fgets(password,sizeof(password),stdin);
    while(fread(u, sizeof(struct User) , 1 , file)){
    //check if username found
    if(strcmp(username,u->username)== 0){
    //check if password correct
    if(strcmp(password,u->password)== 0){
    found=1;
    break;
    }
    }
    }

    return found == 1;
}
