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
	*y1 = (1 - global_vars.INCLINATION) * x + (1 - global_vars.INCLINATION) * y - z;
	return;
}

/**
 * map - maps an integer x to mappedx based
 * on the ratio of the exmaple mapped (the ratio
 * of to to from)
 * @x: the value to be mapped
 * @mappedx: the mapped values adress
 * @from: sample value to be mapped
 * @to: sample value mapped to
 */
int map(int x, int from, int to)
{
	float ratio = (float)(from) / (float)(to);
	ratio *= (ratio > 0) ? 1 : -1;
	return ((int)(x * ratio));
}
