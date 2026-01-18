#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "JsonHandler.h"

/**
 * Ensure filename has .json extension
 */
static char *ensure_json_extension(const char *filename) {
    if (!filename) {
        return NULL;
    }

    // Check if filename already ends with .json
    size_t len = strlen(filename);
    if (len >= 5 && strcmp(filename + len - 5, ".json") == 0) {
        // Already has .json extension, just duplicate
        return strdup(filename);
    }

    // Add .json extension
    char *new_filename = (char *)malloc(len + 6); // +5 for ".json" +1 for '\0'
    if (!new_filename) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcpy(new_filename, filename);
    strcat(new_filename, ".json");

    return new_filename;
}

/**
 * Read entire file into a string
 */
static char *read_file_to_string(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer
    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Read file
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\0';
    fclose(file);

    return buffer;
}

cJSON *read_json_file(const char *filename) {
    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return NULL;
    }

    char *file_content = read_file_to_string(json_filename);
    free(json_filename);
    
    if (!file_content) {
        return NULL;
    }

    cJSON *json = cJSON_Parse(file_content);
    free(file_content);

    if (!json) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    return json;
}

int write_json_file(const char *filename, cJSON *json) {
    if (!json) {
        fprintf(stderr, "Invalid JSON object\n");
        return -1;
    }

    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    // Convert JSON to formatted string
    char *json_string = cJSON_Print(json);
    if (!json_string) {
        fprintf(stderr, "Error converting JSON to string\n");
        free(json_filename);
        return -1;
    }

    // Write to file
    FILE *file = fopen(json_filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        free(json_string);
        free(json_filename);
        return -1;
    }

    fprintf(file, "%s\n", json_string);
    fclose(file);
    free(json_string);
    free(json_filename);

    return 0;
}

int create_file(const char *filename, cJSON *initial_data) {
    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    // Check if file already exists
    if (access(json_filename, F_OK) == 0) {
        fprintf(stderr, "File '%s' already exists\n", json_filename);
        free(json_filename);
        return -1;
    }

    cJSON *json;
    if (initial_data) {
        json = initial_data;
    } else {
        // Create empty JSON object
        json = cJSON_CreateObject();
        if (!json) {
            fprintf(stderr, "Error creating JSON object\n");
            free(json_filename);
            return -1;
        }
    }

    int result = write_json_file(json_filename, json);
    
    // Only delete if we created it
    if (!initial_data) {
        cJSON_Delete(json);
    }

    if (result == 0) {
        printf("File '%s' created successfully\n", json_filename);
    }

    free(json_filename);
    return result;
}

int del_file(const char *filename) {
    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    if (access(json_filename, F_OK) != 0) {
        fprintf(stderr, "File '%s' does not exist\n", json_filename);
        free(json_filename);
        return -1;
    }

    if (remove(json_filename) != 0) {
        perror("Error deleting file");
        free(json_filename);
        return -1;
    }

    printf("File '%s' deleted successfully\n", json_filename);
    free(json_filename);
    return 0;
}

int add_content(const char *filename, const char *key, cJSON *value) {
    if (!key || !value) {
        fprintf(stderr, "Invalid key or value\n");
        return -1;
    }

    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    // Read existing JSON
    cJSON *json = read_json_file(json_filename);
    if (!json) {
        free(json_filename);
        return -1;
    }

    // Check if key already exists
    if (cJSON_GetObjectItem(json, key) != NULL) {
        fprintf(stderr, "Key '%s' already exists. Use edit_content to modify it.\n", key);
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    // Add the new item (we need to duplicate the value since cJSON will manage it)
    cJSON *value_copy = cJSON_Duplicate(value, 1);
    if (!cJSON_AddItemToObject(json, key, value_copy)) {
        fprintf(stderr, "Error adding content to JSON\n");
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    // Write back to file
    int result = write_json_file(json_filename, json);
    cJSON_Delete(json);
    free(json_filename);

    if (result == 0) {
        printf("Content added: '%s'\n", key);
    }

    return result;
}

int del_content(const char *filename, const char *key) {
    if (!key) {
        fprintf(stderr, "Invalid key\n");
        return -1;
    }

    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    // Read existing JSON
    cJSON *json = read_json_file(json_filename);
    if (!json) {
        free(json_filename);
        return -1;
    }

    // Check if key exists
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (!item) {
        fprintf(stderr, "Key '%s' not found\n", key);
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    // Delete the item
    cJSON_DeleteItemFromObject(json, key);

    // Write back to file
    int result = write_json_file(json_filename, json);
    cJSON_Delete(json);
    free(json_filename);

    if (result == 0) {
        printf("Content deleted: '%s'\n", key);
    }

    return result;
}

int edit_content(const char *filename, const char *key, cJSON *new_value) {
    if (!key || !new_value) {
        fprintf(stderr, "Invalid key or value\n");
        return -1;
    }

    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    // Read existing JSON
    cJSON *json = read_json_file(json_filename);
    if (!json) {
        free(json_filename);
        return -1;
    }

    // Check if key exists
    if (!cJSON_GetObjectItem(json, key)) {
        fprintf(stderr, "Key '%s' not found. Use add_content to add it.\n", key);
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    // Replace the item
    cJSON *value_copy = cJSON_Duplicate(new_value, 1);
    if (!cJSON_ReplaceItemInObject(json, key, value_copy)) {
        fprintf(stderr, "Error editing content in JSON\n");
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    // Write back to file
    int result = write_json_file(json_filename, json);
    cJSON_Delete(json);
    free(json_filename);

    if (result == 0) {
        printf("Content edited: '%s'\n", key);
    }

    return result;
}

int display_json_file(const char *filename) {
    // Ensure filename has .json extension
    char *json_filename = ensure_json_extension(filename);
    if (!json_filename) {
        return -1;
    }

    cJSON *json = read_json_file(json_filename);
    if (!json) {
        free(json_filename);
        return -1;
    }

    char *json_string = cJSON_Print(json);
    if (!json_string) {
        fprintf(stderr, "Error formatting JSON\n");
        cJSON_Delete(json);
        free(json_filename);
        return -1;
    }

    printf("\n=== Contents of '%s' ===\n", json_filename);
    printf("%s\n", json_string);
    printf("========================\n\n");

    free(json_string);
    cJSON_Delete(json);
    free(json_filename);

    return 0;
}