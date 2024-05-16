// File: internalCommands.c
// Horine, Cameron
// Operating Systems
// Defines the implementation for the various function
// prototypes found in 'internalCommands.h'. 

#include "internalCommands.h" 
#include "commandMap.h"

bool helpCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
    printf(
        "\n\tWelcome to TISH! Here you will find a list of internal commands and what they do.\n\n"
        "'help': Prints out a helpful how-to.\n"
        "'exit': Gracefully exits TISH.\n"
        "'tishtime': Prints out how long TISH has been running in seconds.\n"
        "'lines': Prints out how many lines have been entered.\n"
        "'lastcom': Execute the last command entered.\n"
        "'maxprocesses': Prints out the maximum number of child processes on this system.\n"
        "'pagesize': Prints out the system page size.\n"
        "'cwd pid': Prints out the current working directory of a given PID.\n"
        "'size pid': Prints out the size of the given PID in pages.\n"
        "'pstate pid': Prints out the current state of the given PID.\n"
        "'parent pid': Returns the parent PID of the given PID.\n\n"
        "If the command does not match any of the internal commands listed here, TISH will treat the command as external, and attempt to fork and execute.\n"
        "Example: Try 'clear'.\n"
    );
    return true;
}

bool timeCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
	time_t currentTime = time(NULL);
	time_t realTime = currentTime - tishStartTime;
	printf("TISH time is: %ld secs\n\n", realTime); 
	return true;
}

bool lineCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
	printf("Number of lines entered: %d\n", lineCount); 
	return true;
}

bool lastCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {	
	if (strlen(lastCommand) == 0) {
		printf("No previous command found.\n"); 
		return false;
	}

	if (strcmp(lastCommand, "lastcom") == 0) {
		printf("Cannot execute 'lastcom' on itself.\n"); 
		return false;
	}

	executeCommand(lastCommand, commandCount, tishStartTime, lineCount, lastCommand);

	return true; 
}

bool maxProcCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
	long maxChildProc = sysconf(_SC_CHILD_MAX); 

	if(maxChildProc == -1) {
		return false; 
	}

	if (maxChildProc < 25) {
		printf("Max child process per user ID: %ld (Minumum required: %d) \n", maxChildProc, _SC_CHILD_MAX); 
	}
	else {
		printf("Max child processes per user ID: %ld\n\n", maxChildProc); 
	}
	return true;
}

bool pageSizeCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
	long pageSize = sysconf(_SC_PAGESIZE);

	if (pageSize == -1) {
		perror("Error in page size.\n"); 
		return false; 
	}

	printf("System page size: %ld\tbytes.\n\n", pageSize);
	return true;
}

bool cwdPidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
	int pid;
	if (sscanf(userInput, "cwd %d", &pid) != 1) {
		printf("Invalid command format. Follow the format: cwd <pid>\n"); 
		return false;
	}

	char cwdPath[256], newPath[256];
	sprintf(cwdPath, "/proc/%d/cwd", pid);

	ssize_t len = readlink(cwdPath, newPath, sizeof(newPath) - 1);
	if (len == -1) {
		printf("Error in read for cwd.\n");
		return false;
	}
	newPath[len] = '\0'; // Null terminate newPath.

	printf("Current working directory of PID %d is: %s\n", pid, newPath); 
	return true; 
}

bool sizePidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
    int pid;
    if (sscanf(userInput, "size %d", &pid) != 1) {
        printf("Invalid command format. Follow the format: size <pid>\n");
        return false;
    }

    long pageSizeInBytes = pageSizeCommand(tishStartTime, lineCount, lastCommand, commandCount, userInput);

    char sizePath[256];
    sprintf(sizePath, "/proc/%d/statm", pid);

    FILE* file = fopen(sizePath, "r");
    if (file == NULL) {
        perror("Error opening statm file");
        return false;
    }

    long sizeInBytes;
    if (fscanf(file, "%ld", &sizeInBytes) != 1) {
        printf("Failed to read size for PID %d.\n", pid);
        fclose(file);
        return false;
    }

    // Convert size to pages
    long sizeInPages = sizeInBytes / pageSizeInBytes;
    printf("Size of PID %d is: %ld pages\n", pid, sizeInPages);

    fclose(file);
    return true;
}

bool pstatePidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
    int pid;
    if (sscanf(userInput, "pstate %d", &pid) != 1) {
		printf("Invalid command format. Follow the format: pstate <pid>\n"); 
        return false;
    }

    char statusPath[256], buffer[256], state[256]; // Store as a string -- allows for more complex states to be printed.

    sprintf(statusPath, "/proc/%d/status", pid);

    FILE* file = fopen(statusPath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    bool stateFound = false;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "State: %s", state) == 1) {
            printf("State of PID %d is: %s\n", pid, state);
            stateFound = true;
            break;
        }
    }

    fclose(file);

    if (!stateFound) {
        printf("State information not found for PID %d.\n", pid);
        return false;
    }

    return true;
}

bool parentPidCommand(time_t tishStartTime, int lineCount, char* lastCommand, int commandCount, const char* userInput) {
    int pid;
    // Parse the PID from the user input
    if (sscanf(userInput, "parent %d", &pid) != 1) {
        printf("Invalid command format. Follow the format: parent <pid>\n");
        return false;
    }

    char filePath[256];
    char readString[256];
    char parentPID[256];

    sprintf(filePath, "/proc/%d/status", pid);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    while (fgets(readString, sizeof(readString), file)) {
        if (sscanf(readString, "PPid: %s", parentPID) == 1) {
            printf("Parent PID of %d is: %s\n", pid, parentPID);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    printf("Parent PID not found for PID %d.\n", pid);
    return false;
}