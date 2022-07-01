#include "util.h"

// read a line from stdin
// returns: a char string which is created by malloc. release by user
//          0 if stdin received a EOF
char *readline()
{
	char *buf=0;
	int bufSize=10;
	buf=(char*)malloc(bufSize);
    buf[0]=0;

	int index=0;
	while (1)
	{
        int c=getchar();
		if (c==EOF)
		{
			free(buf);
			return 0;
		}
		
		if (c=='\n')
			break;
		
        // if reached the buf's tail, expand its capacity
		if (index==bufSize-1)
		{
			bufSize+=10;
			buf=realloc(buf,bufSize);
		}
		buf[index]=c;
		index++;
	}

    buf[index]=0;
	return buf;
}

// print a prompt message like "username@hostname:  /home/user >"
void printPrompt()
{
    uid_t uid;
    gid_t gid;
    uid = getuid();

    char buf[256];

    // username
    printf("%s", getlogin());

    // hostname
    gethostname(buf, sizeof(buf));
    printf("@%s", buf);

    // current directory
    getcwd(buf, sizeof(buf));
    printf(": %s >", buf);
}


// split a command tobe multiple pointer array
int splitCommand(char line[], char *args[])
{
	args[0] = strtok(line, " "); // split string by space
	int i = 0;
	while (args[i] != NULL)
	{ // make sure that args has a NULL pointer at the end
		args[i + 1] = strtok(NULL, " ");
		i++;
	}
	return i;
}

// execute cd command
void exeCdCommand(const char arg[])
{
	if (arg == 0 || strcmp(arg, "~") == 0)
	{
		int ret = chdir(getenv("HOME"));
		if (ret != 0)
			fprintf(stderr, "error.\n");
		return;
	}

	int ret = chdir(arg);
	if (ret != 0)
		fprintf(stderr, "error.\n");
}

// execute the command except cd/bg/bglist
void exeCommand(char *args[])
{
	pid_t p = fork();
	if (p == 0)
	{
		// child process
		int ret = execvp(args[0], args);
		if (ret != 0)
			fprintf(stderr, "error.\n");
	}
	else
	{
		// parent process

		// wait for child process finish
		while (1)
		{
			pid_t w = waitpid(p, NULL, WNOHANG);
			if (w == -1)
				break;
		}
	}
}