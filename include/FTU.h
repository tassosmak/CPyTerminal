#ifndef FTU_HANDLER_H
#define FTU_HANDLER_H

/**
 * First Time Usage Handler
 * 
 * Initializes the application for first-time users by:
 * - Displaying a welcome message
 * - Prompting for a username
 * - Creating a user file
 * 
 * @return int - Status code (0 for success, non-zero for failure)
 */
int FTU_Handler(void);

#endif // FTU_HANDLER_H