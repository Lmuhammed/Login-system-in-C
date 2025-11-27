#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 10
#define MAX_PWD 10

//Login struct
typedef struct {
int code;
char fullName[20];
char username[MAX_USERNAME];
char password[MAX_PWD];

}login;

int main(void){

    FILE *file_append=fopen("login","a");
    FILE *file_read=fopen("login","r");
    login login;

    char username[MAX_USERNAME],password[20];
    int option;
    //Main Menu
    printf("\t \t \t \t Login System \n");
    
    do{
	printf("\t \t (1) Create User \t (2) Login \t  (3) Exit \n");
	scanf("%d",&option);
	getchar();
	if(option == 1){
    //Create User
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
    //Login
    printf("Login \n");
    printf("Enter username : ");
    fgets(username,sizeof(username),stdin);
    printf("Enter Password : ");
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
    printf("No account for username : %s!  \n",username);
    }

    else if(option == 3){
	printf("Quiting ... \n");
	}
	else 
	printf("Non valid option , please chose 1,2,3 \n");
	}while (option != 3);
    fclose(file_append);
    fclose(file_read);

return 0;
}

