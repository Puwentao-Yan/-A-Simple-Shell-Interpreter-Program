#include "bg_pro.h"

#include <sys/wait.h>

// returns the tail node of bg_pro array
struct bg_pro *getBgProTail(struct bg_pro *head)
{
    struct bg_pro *prev = head;
    while (head)
    {
        prev = head;
        head = head->next;
    }
    return prev;
}

// print the bg_pro array
void printBgList(struct bg_pro *head)
{
    char buf[256];
    int counter = 0;
    getcwd(buf, sizeof(buf));
    while (head)
    {
        printf("%d: %s/%s\n", head->pid, buf, head->command);
        head = head->next;
	counter++;
    }
    printf("Total Background jobs: %d\n", counter);
}

// add a bg_pro to array
void addBgPro(struct bg_pro **pHead, int argc, char *args[])
{
    struct bg_pro *bg = (struct bg_pro *)malloc(sizeof(struct bg_pro));
    bg->next = 0;

    // assembly command string
    strcpy(bg->command, args[0]);
    for (int i = 1; i < argc; ++i)
    {
        strcat(bg->command, " ");
        strcat(bg->command, args[i]);
    }

    // if no head node
    if (*pHead == 0)
    {
        *pHead = bg;
        return;
    }

    getBgProTail(*pHead)->next = bg;
}

// release bg_pro array
void releaseBgProLinkedList(struct bg_pro *head)
{
    while (head)
    {
        struct bg_pro *temp = head->next;
        free(head);
        head = temp;
    }
}

// check which bg_pro is terminated
void checkTerminatedBgPro(struct bg_pro **head)
{
    // printf("before:\n");
    // printBgList(*head);

    struct bg_pro *cur = *head;
    struct bg_pro *prev = 0;
    while (cur)
    {
        pid_t w = waitpid(cur->pid, NULL, WNOHANG);
        if (w == -1) // closed
        {
            printf("%d: %s has terminated.\n", cur->pid, cur->command);

            struct bg_pro *temp = cur->next;
            if (cur == *head)
            {
                *head = temp;
            }
            else
            {
                if (prev)
                    prev->next = temp;
            }

            free(cur);

            cur = temp;
            continue;
        }
        prev = cur;
        cur = cur->next;
    }

    // printf("after:\n");
    // printBgList(*head);
}
