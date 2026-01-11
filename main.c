#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_USERNAME 10
#define MAX_PWD 10

struct User {
int id;
char fullName[20];
char username[MAX_USERNAME];
char password[MAX_PWD];

};

void error_msg(char *msg);
bool is_file_empty(FILE *file);
void create_user(FILE * file);
bool login(FILE * file);
int read_int (char * msg);
int generate_id (void);
bool is_id_unique(int id,FILE * file);

int main(void){

    char *file_name="db.dat";
    FILE *file = fopen(file_name, "ab+");
    if (file == NULL ){
     error_msg("file processing failed");
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
    if (is_file_empty(file)) {
        printf("No accounts Yet , Create one ! \n");
        continue;
    }
    bool user_found = login(file);
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
    fclose(file);

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
    printf("Password :  \n");
    fgets(u.password,sizeof(u.password),stdin);
    fwrite(&u, sizeof(u) , 1 , file);
    fflush(file);
    rewind(file);
    printf("New account created\n");
}

bool login(FILE * file){
    struct User u;
    char username[MAX_USERNAME],password[MAX_PWD];
    printf("Login \n Enter username : ");
    fgets(username,sizeof(username),stdin);
    printf("Enter Password : ");
    fgets(password,sizeof(password),stdin);
    int found=0;
    rewind(file);
    while(fread(&u, sizeof(u) , 1 , file)){
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

int generate_id (void){
srand(time(NULL));
int id=(rand()%1001);
return id;
}

bool is_id_unique(int id,FILE * file){
 int found=0;
 struct User u;
 rewind(file);
 while(fread(&u, sizeof(u) , 1 , file)){
    if(u.id == id){
    found =1;
    break;
    }
    }
    return found == 0;
}


