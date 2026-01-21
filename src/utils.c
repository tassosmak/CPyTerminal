#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


#include "utils.h"
#include "flags.h"
#include "JsonHandler.h"

void get_time(char *buffer, size_t size, int show_date) {
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    if (show_date) {
        // Show full date and time
        strncpy(buffer, asctime(timeinfo), size - 1);
        buffer[size - 1] = '\0';
    } else {
        // Show only time (HH:MM:SS)
        strftime(buffer, size, "%H:%M:%S", timeinfo);
    }
}

static int has_json_extension(const char *filename) {
    size_t len = strlen(filename);
    
    // Check if filename is long enough to have .json extension
    if (len < 5) {
        return 0;
    }
    
    // Check if it ends with .json (case-sensitive)
    return strcmp(filename + len - 5, ".json") == 0;
}

int user_exist(const char *search_path) {
    DIR *dir;
    struct dirent *entry;
    
    // Validate input
    if (search_path == NULL) {
        return 0;
    }
    
    // Open the directory
    dir = opendir(search_path);
    if (dir == NULL) {
        return 0;
    }
    
    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Check if file has .json extension
        if (has_json_extension(entry->d_name)) {
            closedir(dir);
            return 1;  // Found at least one, return immediately
        }
    }
    
    closedir(dir);
    return 0;  // No .json files found
}

void jump_mode(void) {
    clear_screen();

    char m;
    int valid = 0;
    int ModeListSize = sizeof ModeList / sizeof ModeList[0];

    do {
        valid = 0; // reset validation flag each iteration
        printf("\nSelect Mode (1/2): ");
        scanf(" %c", &m); // read one char

        // Check if input exists in ModeList
        for (int i = 0; i < ModeListSize; i++) {
            if (ModeList[i] == m) {
                Mode[0] = m;
                Mode[1] = '\0';
                valid = 1;
                break;
            }
        }

        if (!valid) {
            printf("Wrong Option! Please enter only 1 or 2.\n");
        }

    } while (!valid); // repeat until user gives valid input

    printf(
        "\nThis is only for the current session.\n"
        "Next time it will be restored to the previous state.\n"
    );
    // printf("[DEBUG] Jump_Value: %c", m);
    // printf("[DEBUG] Mode: %s", Mode);
}





void Recover_mode(void){
    char ask_recover_mode[8];
    
    // jump_mode();
    printf("\nSelect Mode (1/2): ");
    scanf("%7s", ask_recover_mode);
    strcpy(Mode, ask_recover_mode);

    
    cJSON *recover_mode_value = cJSON_CreateString(ask_recover_mode);
    // strcpy(recover_mode_value, ask_recover_mode);

    add_content(file_name, "Mode", recover_mode_value);
    
    
    printf("\nThe Mode has been restored!");
}

void clear_screen(void){
    printf("\033[H\033[J"); //ASCI - Works Everywhere
}

void pl_finder(){
    #if defined(_WIN32) || defined(_WIN64)
        strcpy(pl, "Windows");
    #elif defined(__APPLE__) || defined(__MACH__)
        strcpy(pl, "macOS");
    #elif defined(__linux__)
        strcpy(pl, "Linux");
    #else
        strcpy(pl, "Unknown");
    #endif
}