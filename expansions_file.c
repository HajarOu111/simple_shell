#include "shell.h"

/**
 * _expand_variables - expand variables.
 * @data: a pointer to a struct of the program's data.
 * Return: nothing, but sets error.
 */
void _expand_variables(data_of_program *data)
{
	int i, h;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (h = 1; line[i + h] && line[i + h] != ' '; h++)
				expansion[h - 1] = line[i + h;
			temp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + h);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * _expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void _expand_alias(data_of_program *data)
{
	int i, h, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (h = 0; line[i + h] && line[i + h] != ' '; h++)
			expansion[h] = line[i + h];
		expansion[h] = '\0';

		temp = get_aliass(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + h);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * add_buffer - append string at end of the buffer.
 * @buffer: buffer to be filled.
 * @str_to_add: string to be copied in the buffer.
 * Return: nothing, but sets errno.
 */
int add_buffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}

