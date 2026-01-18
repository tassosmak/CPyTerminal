#ifndef LOGIN_H
#define LOGIN_H

/* Buffers that store user input */
extern char ask_name[128];
extern char ask_password[128];

/* Prompts the user for username and password */
int ask_name_password(void);

/* Handles the login flow */
int login_handler(void);

#endif /* LOGIN_H */
