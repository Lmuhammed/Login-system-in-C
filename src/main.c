#include <stdlib.h>
#include <stdio.h>
#include "../include/user.h"


int main(void){
    char *file_name="db.dat";
    FILE *file = fopen(file_name, "ab+");
    if (file == NULL ){
     perror("Error :");
    }
    int option;
    //Main Menu
    printf("\t \t \t \t Login System \n");
    do{
    option=read_int("\t \t (1) Create User \t (2) Login \t  (3) Exit \n");
    if(option == 1){
    //Create User
    create_user(file);
    }
    else if(option == 2){
    //Login
    if (is_file_empty(file_name)) {
        printf("No accounts Yet , Create one ! \n");
        continue;
    }
    struct User u;
    bool user_found = login(file,&u);
    if (user_found) {
        printf("Login succses , welcome %s\n",u.fullName);
        option = 3;
    }else {
    printf("No account found\n");
    continue;
    }
    }

    else if(option == 3){
    printf("Quiting ... \n");
    }
    else 
    printf("Non valid option , please chose 1,2,3 \n");
    }while (option != 3);
    fclose(file);

return 0;
}