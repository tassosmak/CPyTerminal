#include <stdio.h>
#include <string.h>

#include "JsonHandler.h"
#include "flags.h"


int get_credentials(char fl[128]){
    
    cJSON *json = read_json_file(fl);
    if (!json) {
        return 1;
    }

    // printf("\n---CREDENTIALS-START---\n");
    /* Read a string */
    cJSON *username_value = cJSON_GetObjectItem(json, "Name");
    if (cJSON_IsString(username_value)) {
        strcpy(file_name, username_value->valuestring);
        // printf("Name: %s\n", username_value->valuestring);
    }

    cJSON *password_value = cJSON_GetObjectItem(json, "Password");
    if (cJSON_IsString(password_value)) {
        strcpy(password, password_value->valuestring);
        // printf("Password: %s\n", password_value->valuestring);
    }

    cJSON *mode_value = cJSON_GetObjectItem(json, "Mode");
    if (cJSON_IsString(mode_value)) {
        strcpy(Mode, mode_value->valuestring);
        // printf("Mode: %s\n", mode_value->valuestring);
    }
    
    // printf("---CREDENTIALS-END---");

    // printf("\nDEBUG: %s", file_name);
    // printf("\nDEBUG: %s", password);
    // printf("\nDEBUG: %s", Mode);

    cJSON_Delete(json);
    return 0;
}