#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_USERNAME 10
#define MAX_PWD 10

typedef struct {
int code;
char fullName[20];
char username[MAX_USERNAME];
char password[MAX_PWD];

}login;

void error_msg(char *msg);
bool is_file_empty(FILE *file);
void create_user(login login , FILE * file_append);
void user_login(login login , FILE * file_read);
int read_int (char * msg);

int main(void){

    char *file_name="login";
    FILE *file_append=fopen(file_name,"ab");
    FILE *file_read=fopen(file_name,"rb");
    if (file_append == NULL || file_read == NULL ){
     error_msg("file processing failed");
    }
    login login;
    //char username[MAX_USERNAME],password[MAX_PWD];
    int option;

    //Main Menu
    printf("\t \t \t \t Login System \n");
    do{
    option=read_int("\t \t (1) Create User \t (2) Login \t  (3) Exit \n");
    if(option == 1){
    //Create User
    create_user(login ,file_append);
    }
    else if(option == 2){
    //Login
    if (is_file_empty(file_read)) {
        printf("No accounts Yet , Create one ! \n");
        continue;
    }
   user_login(login ,file_read);
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

void error_msg(char *msg){
    fprintf(stderr,"ERROR : %s",msg);
    exit(-1);
}

bool is_file_empty(FILE *file) {
    if (file == NULL) {
        perror("Error opening file");
        return -1; 
    }
    fseek(file, 0, SEEK_END); 
    long size = ftell(file); 

    return size == 0;
}

void create_user(login login , FILE * file_append){
    login.code=read_int("Enter code : \n");
    printf("Full name : \n");
    fgets(login.fullName,sizeof(login.fullName),stdin);
    printf("Username :  \n");
    fgets(login.username,sizeof(login.username),stdin);
    printf("Password :  \n");
    fgets(login.password,sizeof(login.password),stdin);
    fwrite(&login, sizeof(login) , 1 , file_append);
    printf("New account created\n");
}

void user_login(login login , FILE * file_read){
    char username[MAX_USERNAME],password[MAX_PWD];
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
    error_msg("Wrong password \n");
    //printf("Wrong password for username : %s ,Retry ...\n",username);
    }
    }
    }
    if (found != 1)
    error_msg("No account found \n");
    //printf("No account for username : %s!  \n",username);

}

int read_int (char * msg){
    char buf[100];
    char *end;
    int x;
    //To pass input message (optional) 
    if (msg != NULL)
    printf("%s",msg);
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 1;
    x = (int)strtol(buf, &end, 10);
    if (end == buf)
    error_msg("Please enter a valid integer \n");
        //fprintf(stderr,"ERROR : Please enter a valid integer \n");
        //exit(-1);
    return x;
}
