#include "shell.h"

/**
 * free_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_data(data_of_program *data)
{
	if (data->tokens)
		free_pointers_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * _free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void _free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_data(data);
	free_pointers_array(data->env);
	free_pointers_array(data->alias_list);
}

/**
 * free_pointers_array - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_pointers_array(char **array)
{
	int j;

	if (array != NULL)
	{
		for (j = 0; array[j]; j++)
			free(array[j]);

		free(array);
		array = NULL;
	}
}

