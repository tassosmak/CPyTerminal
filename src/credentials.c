#include <stdio.h>
#include <string.h>

#include "JsonHandler.h"
#include "flags.h"


int get_credentials(char fl[128]){
    
    cJSON *json = read_json_file(fl);
    if (!json) {
        return 1;
    }

    printf("\n---CREDENTIALS-START---\n");
    /* Read a string */
    cJSON *username_value = cJSON_GetObjectItem(json, "Name");
    if (cJSON_IsString(username_value)) {
        strcpy(file_name, username_value);
        printf("Name: %s\n", username_value->valuestring);
    }

    cJSON *password_value = cJSON_GetObjectItem(json, "Password");
    if (cJSON_IsString(password_value)) {
        strcpy(password, password_value);
        printf("Password: %s\n", password_value->valuestring);
    }

    cJSON *mode_value = cJSON_GetObjectItem(json, "Mode");
    if (cJSON_IsString(mode_value)) {
        strcpy(Mode, mode_value);
        printf("Mode: %s\n", mode_value->valuestring);
    }
    
    printf("---CREDENTIALS-END---");

    cJSON_Delete(json);
    return 0;
}