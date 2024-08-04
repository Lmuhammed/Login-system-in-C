#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 10

//Login struct
typedef struct {
int code;
char fullName[20];
char username[MAX_USERNAME];
char password[20];

}login;

int main(void){

    FILE *file_append=fopen("login","a");
    FILE *file_read=fopen("login","r");
    login login;

    char username[MAX_USERNAME],password[20];
    int option;
    //Main Menu
    printf("Login System \n");
    printf("Create User (1) \t Login (2) \n");
    scanf("%d",&option);
    getchar(); // Consume the newline character put by scanf to use fgets later
    if(option == 1){
    //SignUp
    printf("Enter code : \n");
    scanf("%d",&login.code);
    getchar(); // Consume the newline character put by scanf to use fgets later
    printf("Full name : \n");
    fgets(login.fullName,sizeof(login.fullName),stdin);
    printf("username :  \n");
    fgets(login.username,sizeof(login.username),stdin);
    printf("Password :  \n");
    fgets(login.password,sizeof(login.password),stdin);
    fwrite(&login, sizeof(login) , 1 , file_append);
    printf("New account created\n");
    }
    else if(option == 2){
    //Sign in
    printf("Login \n");
    printf("Enter username :  \n");
    fgets(username,sizeof(username),stdin);
    printf("Enter Password :  \n");
    fgets(password,sizeof(password),stdin);
    int found=0;
    while(fread(&login, sizeof(login) , 1 , file_read)){
    //check if username found
    if(strcmp(username,login.username)== 0){
    //check if password correct
    found=1;
    if(strcmp(password,login.password)== 0){
    printf("Login succses , welcome : %s\n",login.fullName);
    break;
    }
    //Wrong password
    else{
    printf("Wrong password for username : %s ,Retry ...\n",username);
    }
    }
    }
    if (found != 1)
    printf("No account for username : %s !\n",username);
    }
    else
    printf("Option error\n");

    fclose(file_append);
    fclose(file_read);

return 0;
}

