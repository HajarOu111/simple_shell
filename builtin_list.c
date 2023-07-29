#include "shell.h"

/**
 * builtin_list - search for match and execute the associate builtin.
 * @data: struct for the program's data.
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int builtin_list(data_of_program *data)
{
	int i;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (i = 0; options[i].builtin != NULL; i++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[i].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[i].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}

