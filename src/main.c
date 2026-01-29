#include <stdlib.h>
#include <stdio.h>
#include "../include/user.h"


int main(int argc , char **argv){
    //command line parsing var names 
    char *login_long_version ="--login";
    char *login_short_version ="-L";
    char *create_user_long_version ="--create-user";
    char *create_user_short_version ="-CU";

    if(argc < 4){
	printf("NO argc found:%s",argv[0]);
	return -2;
    }
    char *file_name="db.dat";
    FILE *file = fopen(file_name, "ab+");
    if (file == NULL ){
     perror("Error ");
    }

    else if(argc == 4){// argv[0] <action> username password will be added
    //create login
    if(strncmp(login_long_version , argv[1] ,MAX_STRS ) == 0 || strncmp(login_short_version,argv[1],MAX_STRS ) == 0){
    if (is_file_empty(file)) {
        printf("No accounts Yet , Create one ! \n");
        return -3;
    }
    struct User u;
    bool user_found = login(file,&u,argv[2],argv[3]);
    if (user_found) {
        printf("Login succses , welcome %s\n",u.fullName);
    }else
    printf("No account found\n");
 }
    //create user
    else if(strncmp(create_user_long_version , argv[1] ,MAX_STRS ) == 0 || strncmp(create_user_short_version,argv[1],MAX_STRS ) == 0){
    create_user(file,argv[2],argv[3]);
 return -3;

    }
       fclose(file);

    }

return 0;
}