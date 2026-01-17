#include <time.h>
#include <string.h>
#include <stdio.h>

#include "flags.h"

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