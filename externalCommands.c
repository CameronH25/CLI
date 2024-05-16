// File: externalCommands.c
// Horine, Cameron
// Operating Systems
// Implementation file for externalCommands.h

#include "externalCommands.h"

bool executeExternalCommand(const char* command) {
    pid_t pid; 
    int status; 

    pid = fork(); 
    if (pid == 0) {
        // Child process
        execlp("sh", "sh", "-c", command, (char *)NULL);
        perror("execlp"); // execlp only returns on error. 
        exit(EXIT_FAILURE);

    } else if (pid < 0) {
        // Error forking
        perror("fork");
        return false;

    } else {
        // Parent process
        if (waitpid(pid, &status, 0) == -1) { 
            perror("waitpid"); 
            return false;
        }

        return WIFEXITED(status); 
    }
}
