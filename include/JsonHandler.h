#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <cJSON.h>

/**
 * Create a new JSON file with initial content
 * @param filename - path to the JSON file to create
 * @param initial_data - optional initial JSON object (can be NULL)
 * @return 0 on success, -1 on failure
 */
int create_file(const char *filename, cJSON *initial_data);

/**
 * Delete a JSON file
 * @param filename - path to the JSON file to delete
 * @return 0 on success, -1 on failure
 */
int del_file(const char *filename);

/**
 * Add content to JSON file (adds a new key-value pair)
 * @param filename - path to the JSON file
 * @param key - the key to add
 * @param value - cJSON object/value to add
 * @return 0 on success, -1 on failure
 */
int add_content(const char *filename, const char *key, cJSON *value);

/**
 * Delete content from JSON file (removes a key-value pair)
 * @param filename - path to the JSON file
 * @param key - the key to delete
 * @return 0 on success, -1 on failure
 */
int del_content(const char *filename, const char *key);

/**
 * Edit content in JSON file (modifies an existing key's value)
 * @param filename - path to the JSON file
 * @param key - the key to edit
 * @param new_value - new cJSON value to set
 * @return 0 on success, -1 on failure
 */
int edit_content(const char *filename, const char *key, cJSON *new_value);

/**
 * Read and parse a JSON file
 * @param filename - path to the JSON file
 * @return cJSON object on success, NULL on failure
 * Note: caller must free the returned cJSON object with cJSON_Delete()
 */
cJSON *read_json_file(const char *filename);

/**
 * Write cJSON object to a file
 * @param filename - path to the JSON file
 * @param json - cJSON object to write
 * @return 0 on success, -1 on failure
 */
int write_json_file(const char *filename, cJSON *json);

/**
 * Display contents of a JSON file in a formatted way
 * @param filename - path to the JSON file
 * @return 0 on success, -1 on failure
 */
int display_json_file(const char *filename);

#endif // JSON_MANAGER_H