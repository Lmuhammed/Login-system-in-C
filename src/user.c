#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sodium.h>
#include "../include/user.h"

bool pwd_hash(const char *clear_text, size_t clear_text_len,char *hash){
  if (crypto_pwhash_str(
            hash,
            clear_text,
            clear_text_len,
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0)
  return false;
    
return true;
}

bool pwd_verify(const char *stored_hash,char *input_password, size_t input_password_len ){
   //char stored_hash[] ="$argon2id$v=19$m=65536,t=2,p=1$..."; 
    //char input_password[] = "mySecretPassword";
   int res =crypto_pwhash_str_verify(
            stored_hash,
            input_password,
            input_password_len);

return res == 0;
}

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
    if(strlen(u.password) < PWD_MIN_LENGTH || strlen(u.password) > MAX_STRS){
        fprintf(stderr,"Invalid Password length , Expected length must be between %d and %d characters\n ",PWD_MIN_LENGTH,MAX_STRS);
	exit(-1);
	
    }
    char hash[crypto_pwhash_STRBYTES]={0};//from sodium docs
    if(! pwd_hash(u.password, sizeof u.password ,hash))
    fprintf(stderr,"Password hashing failed \n");
    sodium_memzero(u.password, sizeof u.password);
    strncpy(u.password,hash,PWD_MAX_LENGTH);
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
    char password[PWD_MAX_LENGTH]={0};
    printf("Password : ");
    read_password(password, sizeof password);
    while(fread(u, sizeof(struct User) , 1 , file)){
   // printf ("usr : '%s'\n",u->username);
   // printf ("userArgv : '%s'\n",username);
    if(strncmp(u->username,username,PWD_MAX_LENGTH)== 0){
    //check if password correct
    if(pwd_verify(u->password,password,PWD_MAX_LENGTH)){
    found=1;
    break;
    }
    }
    }
    return found == 1;
}
