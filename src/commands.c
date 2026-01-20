#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "utils.h"
#include "flags.h"


int CommandList(){
    // printf("\n[DEBUG - Commands.c] Entered Command: %s \n", Command);


    if (strcmp(Command, "test") == 0) {
        printf("tested");
    }

    if (strcmp(Command, "gui") == 0) {
        if (strcmp(Mode, "2") == 0){
            printf("Not Available Yet");
        }
        if (strcmp(Mode, "1") == 0) {
            printf("Not for your mode");
        }
    }


    if (strcmp(Command, "time") == 0){
        char time_str[80]; 
        get_time(time_str, sizeof(time_str), 0); 
        printf("The Time Is: %s", time_str);
    }

    if (strcmp(Command, "exit") == 0){
        exit(1);
    }
    if (strcmp(Command, "clear") == 0){
        clear_screen();
    }

    if (strcmp(Command, "infostats") == 0){
        printf("\nUsername: %s", file_name);
        printf("\nPassword: %s", password);
        printf("\nMode: %s", Mode);
        printf("\nPlatform: %s", pl);
        printf("\nCommand: %s", Command);
    }

    if (strcmp(Command, "jump")==0){
        jump_mode();
    }
    return 1;
}