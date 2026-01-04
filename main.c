#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_USERNAME 10
#define MAX_PWD 10

struct User {
int code;
char fullName[20];
char username[MAX_USERNAME];
char password[MAX_PWD];

};

void error_msg(char *msg);
bool is_file_empty(FILE *file);
void create_user(FILE * file_append);
bool login(FILE * file_read);
int read_int (char * msg);

int main(void){

    char *file_name="db.dat";
    FILE *file_append=fopen(file_name,"ab");
    FILE *file_read=fopen(file_name,"rb");
    if (file_append == NULL || file_read == NULL ){
     error_msg("file processing failed");
    }
    int option;
    //Main Menu
    printf("\t \t \t \t Login System \n");
    do{
    option=read_int("\t \t (1) Create User \t (2) Login \t  (3) Exit \n");
    if(option == 1){
    //Create User
    create_user(file_append);
    }
    else if(option == 2){
    //Login
    if (is_file_empty(file_read)) {
        printf("No accounts Yet , Create one ! \n");
        continue;
    }
    bool user_found = login(file_read);
    if (user_found) {
        printf("Login succses , welcome\n");
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

void create_user(FILE * file_append){
    struct User u;
    u.code=read_int("Enter code : \n");
    printf("Full name : \n");
    fgets(u.fullName,sizeof(u.fullName),stdin);
    printf("Username :  \n");
    fgets(u.username,sizeof(u.username),stdin);
    printf("Password :  \n");
    fgets(u.password,sizeof(u.password),stdin);
    fwrite(&u, sizeof(u) , 1 , file_append);
    printf("New account created\n");
}

bool login(FILE * file_read){
    struct User u;
    char username[MAX_USERNAME],password[MAX_PWD];
    printf("Login \n");
    printf("Enter username : ");
    fgets(username,sizeof(username),stdin);
    printf("Enter Password : ");
    fgets(password,sizeof(password),stdin);
    int found=0;
   rewind(file_read);
    while(fread(&u, sizeof(u) , 1 , file_read)){
    //check if username found
    if(strcmp(username,u.username)== 0){
    //check if password correct
    if(strcmp(password,u.password)== 0){
    found=1;
    break;
    }
    }
    }
    return found == 1;
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
