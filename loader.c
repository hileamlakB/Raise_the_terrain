#include "terrain.h"

/**
 * sopen - opens a file  to be processed by the terrian
 * representer if it is possible
 * @name: name of the file
 * Return: a FILE * if sucess full and NULL on faliure
 */
FILE *sopen(char *name)
{
	char *path = NULL, *currentdir = NULL;
	FILE *fd;

	if (!name || strlen(name) <= 0)
		return (NULL);

	if (name[0] != '.' && name[0] != '~' && name[0] != '/')
	{
		currentdir = getenv("PWD");
		path = smalloc(strlen(currentdir) + strlen(name) + 4);
		strcpy(path, currentdir);
		strcat(path, "/");
		strcat(path, name);
	}
	else
		path = _strdup(name);

	fd = fopen(path, "r");
	if (!fd)
	{
		dprintf(2, "Error: Can't open file %s\n", name);
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);

	return (fd);
}

/**
 * load - loads data from an opened file and strores it in the proper
 * array
 * @fd: file descriptor
 * @data: the int array to hold the data
 * Return: an array of arrays containing a terian information
 */
void load(FILE *fd, int (*data)[MAP_WIDTH][MAP_WIDTH])
{
	char *line = NULL, *data_str;
	size_t buffer_size = 0;
	unsigned int col = 0, line_number = 1;

	while (1)
	{
		if (getline(&line, &buffer_size, fd) == -1)
			break;
		/*remove the newline at the end*/
		line[strlen(line) - 1] = '\0';
		col = 0;
		data_str = strtok(line, " ");
		while (col < MAP_WIDTH)
		{
			if (!data_str)
			{
				dprintf(2, "L%i: Data doesn't have all the required cols", line_number);
				exit(EXIT_FAILURE);
			}
			if (isint(data_str))
				(*data)[line_number - 1][col] = atoi(data_str);
			else
			{
				dprintf(2, "L%i C%i: Data format should be integer->%s\n",
						line_number,
						col,
						data_str);
				exit(EXIT_FAILURE);
			}
			col++;
			data_str = strtok(NULL, " ");
		}
		line_number++;
	}
	if (line_number < MAP_WIDTH)
	{
		dprintf(2, "Data doesn't have all the required lines");
		exit(EXIT_FAILURE);

	}
}

