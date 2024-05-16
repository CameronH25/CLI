// File: internalCommands.h
// Horine, Cameron
// Operating Systems
// Interface file for internalCommands.c
// Includes basic function prototypes for the
// internal commands the program will handle. 

#ifndef INTERNALCOMMANDS_H
#define INTERNALCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

// Note 1: more rationale pertaining to function parameters can be found in 'commandMap.h'
// Note 2: 'maxProcCommand' and 'pageSizeCommand' are discoverable by sysconf usage.
// Note 3: 'cwd pid', 'size pid', 'parent pid', and 'pstate pid' are discoverable by proc usage. 

// The help command is a simple print statement that informs the user about the functionality of the internal commands.
// The internal commands are: 'help', 'tishtime', 'lines', 'lastcom', 'maxprocesses', 'pagesize', 'cwd pid', 'size pid',
// 'pstate pid', and 'praent pid'. The function 'helpCommand' always returns true, as it cannot fail. 
bool helpCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput); 

// The tishtime command simply prints out the time that the program "TISH" has been running. The time unit is in seconds.
// the 'timeCommand' function also always returns true. The only parameter used in this function is 'tishStartTime', which
// is the variable that holds the program start time. Program start time is subtracted from the current time, which is the result.
bool timeCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The lines command simply prints out the number of lines that the user has entered. This function never returns false. 
// The only parameter that the function uses is the lineCount integer. 
bool lineCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The lastcom command simply executes the last command entered. This function can fail under two conditions:
// 1) The last command entered *is* 'lastcom'. 
// 2) There is no previously entered command. 
// Otherwise, this function calls 'executeCommand', and then returns true. 
bool lastCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The maxprocesses command prints out the maximum child processes. This function returns false only if that number is 
// -1. Otherwise, it will print out the aforementioned and return true. This function does not use any of the parameters
// passed in, as any information is discoverable by sysconf usage. 
bool maxProcCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The pagesize command prints out the system page size, in bytes. This function returns false only if the number 
// returned from sysconf usage is -1. Otherwise, it will print out the pagesize of the system in bytes. No parameter
// passed in is used, given its relevant information is discoverable by sysconf usage. 
bool pageSizeCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The cwd pid command prints out the current working directory (cwd) of a given PID. This function uses the parameter
// 'userInput', and parses it, extracting the PID. If the format is incorrect, the function will print such and return
// false. Further, if there is an error with the reading for the cwd path -- ie, "/proc/[yourPID]/cwd", the function
// will return false. Otherwise, the current working directory of the given PID will be printed, and the function will
// thereafter return true. 
bool cwdPidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The size pid command prints out the size of a given PID, in pages. This function uses the userInput parameter, and 
// calls the 'pageSizeCommand'. This function will return false in three cases:
// 1) The user input was not in the correct format. 
// 2) There was an error in reading the 'statm' file.
// 3) There was a failure in reading the size for the given PID.
// Otherwise, the function will convert the bytes into pages, print the result, and return true. 
bool sizePidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The pstate pid command prints the state of a given PID. The function only uses the userInput parameter. The function
// will return false in three cases:
// 1) The user input was not in the correct format. 
// 2) There was an error in opening the status file. 
// 3) No state information was found about the given PID.
// Otherwise, the function will print out the state of a given process as a string (in order to help capture more complex
// states), and will return true. 
bool pstatePidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput);

// The parent pid command prints out the parent PID of a given process. The function only uses the userIput parameter. 
// The function will return false in three cases:
// 1) The user input was not in the correct format.
// 2) There was an error in opening the status filepath.
// 3) There was no parent PID found for the given process.
// Otherwise, the function will print the parent PID of the given process and return true. 
bool parentPidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput); 

#endif