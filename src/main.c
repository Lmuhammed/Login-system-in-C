#include <stdlib.h>
#include <stdio.h>
#include "../include/user.h"


int main(int argc , char **argv){

    if(argc < 3){// argv[0] <action> username password will be added
	printf("NO argc found:%s\n",argv[0]);
	return -2;
    }

    char *file_name="db.dat";
    FILE *file = fopen(file_name, "ab+");
    if (file == NULL ){
     perror("Error ");
    }

    //command line parsing var names 
    char *login_long_version ="--login";
    char *login_short_version ="-L";
    char *create_user_long_version ="--create-user";
    char *create_user_short_version ="-CU";

    char *action=argv[1];
    

    // login
    if(strncmp(login_long_version , action ,MAX_STRS ) == 0 || 
       strncmp(login_short_version,action,MAX_STRS ) == 0){

    if (is_file_empty(file)) {
    	printf("No accounts Yet , Create one ! \n");
        return -3;

    }

    struct User u;
    char *username=argv[2];
    
    if(strlen(username) < PWD_MIN_LENGTH || strlen(username) > MAX_STRS){
        fprintf(stderr,"Invalide username length , Expected length must be between %d and %d characters\n ",PWD_MIN_LENGTH,MAX_STRS);
	exit(-1);
	
    }
    bool user_found = login(file,&u,username);
    if (user_found) {
    	printf("Login succses , welcome %s\n",u.fullName);
    }else
    	printf("No accounts found\n");
    }

    //create user
    else if(strncmp(create_user_long_version , action ,MAX_STRS ) == 0 ||
            strncmp(create_user_short_version,action,MAX_STRS ) == 0){

       char *fullName=argv[2];
       if(strlen(fullName) < FULLNAME_MIN_LENGTH || strlen(fullName) > MAX_STRS){
        fprintf(stderr,"Invalide full name length , Expected length must be between %d and %d characters\n ",PWD_MIN_LENGTH,MAX_STRS);
	exit(-1);
        }

        char *username=argv[3];
        if(strlen(username) < USERNAME_MIN_LENGTH || strlen(username) > MAX_STRS){
        fprintf(stderr,"Invalide username length , Expected length must be between %d and %d characters\n ",PWD_MIN_LENGTH,MAX_STRS);
	exit(-1);
        }

	create_user(file,fullName,username);
	return -3;

    }

    //invalid option
    else{
    fprintf(stderr,"%s : invalid option -> '%s' \n",argv[0],argv[1]);
    return -5;
    }
    fclose(file);


return 0;
}