#include <stdio.h>
#include "JsonHandler.h"
#include "flags.h"

int FTU_Handler(){
    // First Time Usage Script
    printf("Welcome To The C Version Of PyTerminal \n");
    
    //Build The File
    // char file_name[128];
    printf("Enter you username:");
    scanf("%s", file_name);
    create_file(file_name, NULL);


    //Add The Contents

    //Name
    cJSON *name_value = cJSON_CreateString(file_name);
    add_content(file_name, "Name", name_value);

    //Password
    // char password[128];
    printf("Enter The Password You Want: ");
    scanf("%s", password);
    cJSON *password_value = cJSON_CreateString(password);
    add_content(file_name, "Password", password_value);

    // char Mode[128];
    printf("Basic Or Advanced Mode\n1 or 2\nSelect:");
    scanf("%s", Mode);
    cJSON *Mode_value = cJSON_CreateString(Mode);
    add_content(file_name, "Mode", Mode_value);


    return 1;
}