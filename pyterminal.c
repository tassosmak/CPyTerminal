#include <stdio.h>
#include <locale.h>


#include "commands.h"
#include "flags.h"
#include "utils.h"
#include "FTU.h"
#include "Login.h"
#include "credentials.h"



int run(void){
    printf("\033[H\033[J"); //Clear Screen

    // ask_name_password();
    login_handler();
    
    while (1){
        printf("\nEnter Your Command: ");
        scanf("%s", Command);

        // CommandList(command, ask_core);
        CommandList();
    }
    return 0;
}

int main(void) {
    setlocale(LC_ALL, "UTF-8");
    pl_finder();

    if (user_exist(".")){
        run();
        return 1;
    }
    else
    {
        FTU_Handler();
        run();
        return 1;
    }
}