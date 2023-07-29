#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int _execut(data_of_program *data)
{
	int retval = 0, statuss;
	pid_t pidd;

	/* check for program in built ins */
	retval = builtins_list(data);
	if (retval != -1)/* if program was found in built ins */
		return (retval);

	/* check for program file system */
	retval = find_program(data);
	if (retval)
	{/* if program not found */
		return (retval);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit statuss of the child */
			wait(&statuss);
			if (WIFEXITED(statuss))
				errno = WEXITSTATUS(statuss);
			else if (WIFSIGNALED(statuss))
				errno = 128 + WTERMSIG(statuss);
		}
	}
	return (0);
}
