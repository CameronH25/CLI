// File: commandMap.c
// Horine, Cameron
// Operating Systems
// Implementation file for commandMap.h

#include "commandMap.h"
#include "internalCommands.h" 

struct {
	const char* name;
	CommandFunction function;
} commandMap[MAX_COMMANDS]; 

int initCommandMap(void) {
	int commandCount = 0; 

	commandMap[commandCount].name = "help";
	commandMap[commandCount].function = helpCommand;
	commandCount++; 

	commandMap[commandCount].name = "tishtime";
	commandMap[commandCount].function = timeCommand;
	commandCount++; 

	commandMap[commandCount].name = "lines";
	commandMap[commandCount].function = lineCommand;
	commandCount++; 

	commandMap[commandCount].name = "lastcom";
	commandMap[commandCount].function = lastCommand;
	commandCount++; 

	commandMap[commandCount].name = "maxprocesses";
	commandMap[commandCount].function = maxProcCommand;
	commandCount++; 

	commandMap[commandCount].name = "pagesize";
	commandMap[commandCount].function = pageSizeCommand;
	commandCount++; 

	commandMap[commandCount].name = "cwd";
	commandMap[commandCount].function = cwdPidCommand;
	commandCount++; 

	commandMap[commandCount].name = "size";
	commandMap[commandCount].function = sizePidCommand;
	commandCount++; 

	commandMap[commandCount].name = "pstate";
	commandMap[commandCount].function = pstatePidCommand;
	commandCount++; 

	commandMap[commandCount].name = "parent";
	commandMap[commandCount].function = parentPidCommand;
	commandCount++; 

	return commandCount; 
}

bool executeCommand(const char* userInput, int commandCount, time_t tishStartTime, int lineCount, char* lastCommand) {
    char commandName[COMMAND_MAX_LENGTH];
    sscanf(userInput, "%s", commandName);  // Extract only the name of the command.  

    for (int i = 0; i < commandCount; i++) {
        if (strcmp(commandName, commandMap[i].name) == 0) {
            return commandMap[i].function(tishStartTime, lineCount, lastCommand, commandCount, userInput);
        }
    }

    if (strcmp(userInput, "exit") == 0) {
    	return false; 
    }

    printf("\n\tInternal command not found. Attempting the command as an external command:\n\n");
    return false;
}