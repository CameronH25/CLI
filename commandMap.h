// File: commandMap.h
// Horine, Cameron
// Operating Systems
// Interface file for commandMap.c

#ifndef COMMANDMAP_H
#define COMMANDMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define MAX_COMMANDS 10
#define COMMAND_MAX_LENGTH 256

// Interface for a set of functions. Used in the struct for the hashmap,
// which contains a name and function of the type 'CommandFunction'. This
// typedef is used to standardize the signature of the internal command
// functions. This will return true or false depending on if the command
// was successfully executed, which is determined by the other function
// called 'executeCommand'. 
typedef bool(*CommandFunction)(time_t, int, char*, int, const char*); 

// Initializes the hash map of internal commands for TISH by populating the
// 'commandMap' with predefined internal commands, wherein each has a unique 
// name and corresponding function that adheres to the 'CommandFunction'
// typedef signature. 
// The function returns an integer of the total count of internal commands that 
// are within the commandMap -- 'totalCount'. This integer is used to iterate 
// through the command map for matching and execution. 
int initCommandMap(void);

// This function first attempts to match the user input to one of those found in
// the commandMap hash map. These are the predefined internal commands that are 
// enumerated in the initCommandMap. If a match is found, it invokes the relevant 
// function call. There are two cases in which the function will return false:
// 1) The user command is 'exit'.
// 2) The name of the command does not match any of the internal commands.
// Otherwise, the function will return true, calling the relevant function for the
// specified user input. 
// Parameters:
// 	const char* userInput: The raw input string entered in by the user.
// 	int commandCount: The total number of internal commands.
//	time_t tishStartTime: The start time of the TISH program.
//	int lineCount: The current count of lines (or, commands) entered by the user.
//	char* lastCommand: A string storing the last executed command. 
bool executeCommand(const char* userInput, int commandCount, time_t tishStartTime, int lineCount, char* lastCommand);

#endif