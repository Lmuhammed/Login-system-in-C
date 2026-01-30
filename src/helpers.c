#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "../include/helpers.h"
//thanks to https://dev.to/namantam1/how-to-take-hidden-password-from-terminal-in-cc-3ddd for getch() & read_password()

int getch() {
    int ch;
    // struct to hold the terminal settings
    struct termios old_settings, new_settings;
    // take default setting in old_settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // make of copy of it (Read my previous blog to know 
    // more about how to copy struct)
    new_settings = old_settings;
    // change the settings for by disabling ECHO mode
    // read man page of termios.h for more settings info
    new_settings.c_lflag &= ~(ICANON | ECHO);
    // apply these new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    // now take the input in this mode
    ch = getchar();
    // reset back to default settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}

void read_password(char arr[],int arr_size){
int i =0,ch;
while ((ch = getch()) != '\n' && i < arr_size) {
        if (ch == 127 || ch == 8) { // handle backspace
            if (i != 0) {
                i--;
                printf("\b \b");
            }
        } else
            arr[i++] = ch;
    }
    arr[i] = '\0';
printf("\n");
}

void error_msg(char *msg){
    fprintf(stderr,"ERROR : %s\n",msg);
    exit(-1);
}

bool is_file_empty(FILE * file) {
    fseek(file,0,SEEK_END);
    int offset=ftell(file);
    return offset == 0;
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

bool is_username_unique(char * username,FILE * file){
 int found=0;
 struct User u;
 rewind(file);
 while(fread(&u, sizeof(u) , 1 , file)){
	 int res=strncmp(username,u.username,MAX_STRS);
    if(res == 0){
    found =1;
    break;
    }
    }
    return found == 0;
}
