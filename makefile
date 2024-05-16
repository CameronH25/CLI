tish: TISH.o commandMap.o internalCommands.o externalCommands.o
	gcc TISH.o commandMap.o internalCommands.o externalCommands.o -o TISH

TISH.o: TISH.c commandMap.h internalCommands.h externalCommands.h
	gcc -c TISH.c 

commandMap.o: commandMap.c commandMap.h internalCommands.h
	gcc -c commandMap.c

internalCommands.o: internalCommands.c commandMap.h internalCommands.h
	gcc -c internalCommands.c

externalCommands.o: externalCommands.c externalCommands.h
	gcc -c externalCommands.c