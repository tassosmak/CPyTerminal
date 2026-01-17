#include <stdio.h>
#include <locale.h>


#include "commands.c"
#include "flags.h"
#include "utils.h"

int main(void) {
    setlocale(LC_ALL, "UTF-8");
    pl_finder();


    printf("\033[H\033[J"); //Clear Screen
    
    
    printf("Welcome To PyTerminal\nThere are 2 Modes on this terminal\n1) The Basic Mode,     2) The Advanced Mode\n");

    scanf("%s", mode);

    while (1){
        printf("\nEnter Your Command: ");
        scanf("%s", Command);

        // CommandList(command, ask_core);
        CommandList();
    }
    return 0;
}