// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>  // for size_t

void get_time(char *buffer, size_t size, int show_date);
int user_exist(const char *search_path);
void clear_screen(void);
void jump_mode(void);
void Recover_mode(void);
void pl_finder(void);

#endif