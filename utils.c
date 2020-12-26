#include "terrain.h"


/**
 * isint - checks if everything inside a string is a number
 * @intstring: a string expected to contain all int chars
 * Return: returns 1 if everything is int 0 if not
 */
int isint(char *intstring)
{
	while (*intstring)
	{
		if ((*intstring > '9' || *intstring < '0') && *intstring != '-')
			return (0);
		intstring += 1;
	}
	return (1);
}

/**
 * to2D - changes a points position from 3d to 2d using an inclination
 * @x: the original x point in 3d space
 * @y: the original y point in 3d space
 * @z: the original z point in 3d space
 * @x1: a pointer to the new x point in 2d space
 * @y1: a pointer to the new y point in 2d space
 */
void to2D(int x, int y, int z, int *x1, int *y1)
{
	*x1 = global_vars.INCLINATION * x - global_vars.INCLINATION * y;
	*y1 = (1 - global_vars.INCLINATION) * x +
		(1 - global_vars.INCLINATION) * y - z;
}

/**
 * map - maps an integer x to mappedx based
 * on the ratio of the exmaple mapped (the ratio
 * of to to from)
 * @x: the value to be mapped
 * @from: sample value to be mapped
 * @to: sample value mapped to
 * Return: returns a mapped int
 */
int map(int x, int from, int to)
{
	float ratio = (float)(from) / (float)(to);

	ratio *= (ratio > 0) ? 1 : -1;
	return ((int)(x * ratio));
}


/**
 *smalloc - allocates a memory location and returns a pointer
 *@size: amount to be  allocated
 *Return: a generic pointer allocated or -1 on faliure
 */
void *smalloc(unsigned int size)
{
	char *pointer = malloc(size);
	void *_pointer = NULL;
	unsigned int i = 0;

	if (!pointer)
	{
		dprintf(2, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	while (i < size)
	{
		pointer[i] = '\0';
		i += 1;
	}
	_pointer = (void *)pointer;
	return (_pointer);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: string to be copied
 * Return: copied string
 */
char *_strdup(char *str)
{

	char *copy, *_copy;

	if (!str)
		return (NULL);
	copy = smalloc((strlen(str) + 1) * sizeof(char));
	_copy = copy;

	while (*str)
		*_copy = *str, str += 1, _copy += 1;

	*_copy = '\0';
	return (copy);
}
