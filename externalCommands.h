// File: externalCommands.h
// Horine, Cameron
// Operaitng Systems
// Interface file for externalCommands.c

#ifndef EXTERNALCOMMANDS_H
#define EXTERNALCOMMANDS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// This function attempts to execute a command that is not one of the 
// pre-defined internal commands found in internalCommands.h. This function
// takes in any user-specified input (passed in as the const char* command)
// as an external command. The function will return false in three cases:
// 1) There is a failure in forking.
// 2) There is a failure in executing the command.
// 3) An abnormal termination of the child process occurs.
// Otherwise, the function will return true. 
// 	Specific references:
// 	1) 'man 2 fork'
// 	2) 'man 2 waitpid'
// 	3) 'man 2 fork' 
// 	4) 'man 3 exec'
// 	5) 'man 3 perror'
// 	6) 'man 3 exit' 
// 	7) 'man 3 perror'
// 	8) 'man 2 waitpid'
// 	9) 'man 3 perror'
// 	10) 'man 2 waitpid' 

// 	General references:
// 	1) Link: https://stackoverflow.com/questions/5237482/how-do-i-execute-an-external-program-within-c-code-in-linux-with-arguments
//    	General Info: Cited on December 26, 2024. 3:12pm. 
bool executeExternalCommand(const char* command);

#endif