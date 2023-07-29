#include "shell.h"

/**
 * env_key - gets the value of an environment variable.
 * @key: the environment variable of interest.
 * @data: struct of the program's data.
 * Return: a pointer to the value of the variable or NULL if it doesn't exist.
 */
char *env_key(char *key, data_of_program *data)
{
	int i, length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], length) &&
		 data->env[i][length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[i] + length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int set_key(char *key, char *value, data_of_program *data)
{
	int i, length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], length) &&
		 data->env[i][length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int remove_key(char *key, data_of_program *data)
{
	int i, length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[i], length) &&
		 data->env[i][length] == '=')
		{/* if key already exists, remove them */
			free(data->env[i]);

			/* move the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environment - prints the current environment.
 * @data: struct for the program's data.
 * Return: void.
 */
void print_environment(data_of_program *data)
{
	int k;

	for (k = 0; data->env[k]; k++)
	{
		_print(data->env[k]);
		_print("\n");
	}
}

