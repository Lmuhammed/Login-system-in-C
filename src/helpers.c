#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/helpers.h"

void error_msg(char *msg){
    fprintf(stderr,"ERROR : %s",msg);
    exit(-1);
}

bool is_file_empty(char *filename) {
 struct stat file_status;
 if (stat(filename,&file_status) < 0)
 exit (-1);
    return file_status.st_size == 0;
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

