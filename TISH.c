// File: TISH.c
// Horine, Cameron
// Operating Systems
// Driver program for TISH (Transy Indescribable SHell) 

// This program takes in a user input and checks if that
// input matches a pre-defined function, which are enumerated
// inside a hash map with a unique name and function call. If
// there is a match, TISH will execute the pre-defined function.
// If there is not a match, TISH will treat the command as an
// external command, and attempt to fork and execute. TISH will
// tell the user if this external command failed.
// All internal and external commands work. 

#include <stdio.h>
#include <string.h>
#include "commandMap.h"
#include "internalCommands.h"
#include "externalCommands.h"

int main (void) {
    time_t tishStartTime = time(NULL); 
    char lastCommand[COMMAND_MAX_LENGTH] = ""; 
    int lineCount = 0;
    
    printf("\t\tTransylvania Indescribable SHell --- TISH\n\n"); 

    char userInput[COMMAND_MAX_LENGTH];
    int commandCount = initCommandMap(); 

    while (strcmp(userInput, "exit") != 0) {
        printf("%s", "$  ");  
        scanf("%[^\n]%*c", userInput);
        lineCount++;

        if (strcmp(userInput, "lastcom") != 0) {
            strncpy(lastCommand, userInput, COMMAND_MAX_LENGTH - 1);
            lastCommand[COMMAND_MAX_LENGTH - 1] = '\0';  // Null terminate. 
        }

        if (!executeCommand(userInput, commandCount, tishStartTime, lineCount, lastCommand)) {
        	if(!executeExternalCommand(userInput)) {
        		printf("Command not recognized.\n\n"); 
        	}
		}
        printf("\n"); 
    }

    return 0; 
}