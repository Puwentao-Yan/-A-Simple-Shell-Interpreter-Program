#include <stdio.h>

#include "util.h"
#include "bg_pro.h"

int main()
{
	char *args[1024];

	struct bg_pro *head=0;

	int quit = 0;
	while (!quit)
	{
		// print prompt
		printPrompt();

		// get a line
		char *line = readline();

		// check which bg_pro is terminated
		checkTerminatedBgPro(&head);

		if (line == 0)
			break;
			
		// split
		int cmdNums = splitCommand(line, args);
		if (cmdNums == 0)
			continue;

		// if want to exit
		if (strcmp(args[0], "exit") == 0)
		{
			quit = 1;
			free(line);
			printf("Bye Bye\n");
			break;
		}

		// if cmd is "cd"
		if (strcmp(args[0], "cd") == 0)
		{
			exeCdCommand(args[1]);
			free(line);
			continue;
		}

		// if cmd is "bglist"
		if (strcmp(args[0],"bglist")==0)
		{
			printBgList(head);
			continue;
		}

		// if cmd is "bg"
		if (strcmp(args[0],"bg")==0)
		{
			pid_t p = fork();
			if (p == 0)
			{
				// child process
				int ret = execvp(args[1], &args[1]);
				if (ret != 0)
					fprintf(stderr, "error.\n");

				// printf("finish.\n");
				free(line);
				break;
			}
			else
			{
				// parent process
				addBgPro(&head,cmdNums-1,&args[1]);
				getBgProTail(head)->pid=p;
			}

			free(line);
			continue;
		}

		// other command
		exeCommand(args);

		free(line);

		// check which bg_pro is terminated
		checkTerminatedBgPro(&head);
	}

	// release linked list
	releaseBgProLinkedList(head);

	return 0;
}
