// File: externalCommands.c
// Horine, Cameron
// Operating Systems
// Implementation file for externalCommands.h

#include "externalCommands.h"

bool executeExternalCommand(const char* command) {
    pid_t pid; // Ref 1 
    int status; // Ref 2 

    pid = fork(); // Ref 3 
    if (pid == 0) {
        // Child process
        execlp("sh", "sh", "-c", command, (char *)NULL); // Ref 4 
        perror("execlp"); // execlp only returns on error. Ref 5
        exit(EXIT_FAILURE); // Ref 6 

    } else if (pid < 0) {
        // Error forking
        perror("fork"); // Ref 7
        return false;

    } else {
        // Parent process
        if (waitpid(pid, &status, 0) == -1) { // Ref 8
            perror("waitpid"); // Ref 9
            return false;
        }

        return WIFEXITED(status); // Ref 10
    }
}