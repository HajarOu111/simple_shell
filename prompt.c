#include "file.h"
#include <sys/wait.h>
#define MAX_COMMAND 20

void prompt(char **av, char **ev)
{
char *lineptr = 0;
int i = 0;
size_t n = 0;
int status;
int h = 0;
ssize_t char_num;
char *argv[MAX_COMMAND];
pid_t child_p;
while(1)
{
printf("#cisfun$ ");
char_num = getline(&lineptr, &n, stdin);
if (char_num == -1)
{
free(lineptr);
exit(EXIT_FAILURE);
}
while(lineptr[i])
{
if (lineptr[i] == '\n')
lineptr[i] = 0;
i++;
}
argv[h] = strtok(lineptr, " ");
while(argv[h])
{
h++;
argv[h] = strtok(NULL, " ");
}
child_p = fork();
if (child_p == -1)
{
free(lineptr);
exit(EXIT_FAILURE);
}
if (child_p == 0)
{
if (execve(argv[0], argv, ev) == -1)
printf("%s: No such file or directory\n", av[0]);
}
else
wait(&status);
}
}
