#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// background process node, use to be a linked list
struct bg_pro
{
    pid_t pid;
    char command[1024];
    struct bg_pro *next;
};

// returns the tail node of bg_pro array
struct bg_pro *getBgProTail(struct bg_pro *head);

// print the bg_pro array
void printBgList(struct bg_pro *head);

// add a bg_pro to array
void addBgPro(struct bg_pro **pHead, int argc, char *args[]);

// release bg_pro array
void releaseBgProLinkedList(struct bg_pro *head);

// check which bg_pro is terminated
void checkTerminatedBgPro(struct bg_pro **head);
