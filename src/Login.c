#include <stdio.h>
#include <string.h>

#include "credentials.h"
#include "flags.h"

char ask_name[128];
char ask_password[128];

int ask_name_password(void){
    
    //Name
    printf("Enter Username:");
    scanf("%127s", ask_name);
    
    //Password
    printf("Enter Password:");
    scanf("%127s", ask_password);

    return 1;
}

int login_handler(void)
{
    ask_name_password();
    get_credentials(ask_name);

    while (strcmp(file_name, ask_name) != 0) {
        printf("Username not found. Try again.\n");
        ask_name_password();
        get_credentials(ask_name);
    }

    return 1;
}
