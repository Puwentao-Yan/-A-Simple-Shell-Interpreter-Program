#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// read a line from stdin
// returns: a char string which is created by malloc. release by user
//          0 if stdin received a EOF
char *readline();

// print a prompt message like "username@hostname:  /home/user >"
void printPrompt();

// split a command tobe multiple pointer array
int splitCommand(char line[], char *args[]);

// execute cd command
void exeCdCommand(const char arg[]);

// execute the command except cd/bg/bglist
void exeCommand(char *args[]);