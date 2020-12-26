#include "terrain.h"


/**
 *print_points - prints an array of SDL_Point object
 *@data: the datat
 */
void print_points(SDL_Point data[MAP_WIDTH][MAP_WIDTH])
{
	int i = 0, j = 0;

	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("{%i, %i} ", data[i][j].x, data[i][j].y);
			j++;
		}
		printf("\n");
		i++;
	}

}

/**
 * rotate_gird - rotates a grid by an angle @angle
 * @data_points: the grid
 * @data: an array containing the altitudes
 * @angle: the angle to rotate the grid by
 */
void rotate_grid(int data[MAP_WIDTH][MAP_WIDTH],
		SDL_Point (*data_points)[MAP_WIDTH][MAP_WIDTH], float angle)
{
	int Rx = 0, Ry = 0, i = 0, j = 0, x = 0, y = 0;
	int centerX = global_vars.SCREEN_WIDTH / 2;
	int centerY = global_vars.SCREEN_HEIGHT / 2;
	(void)(data);

	/*int box_height = min_dim - 2 * global_vars.MARGIN;*/

	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			x = (*data_points)[i][j].x;
			y = (*data_points)[i][j].y;

			Rx = ((x - centerX) * cos(angle) - (y - centerY) * sin(angle)) + centerX;
			Ry = ((x - centerX) * sin(angle) + (y - centerY) * cos(angle)) + centerY;
			(*data_points)[i][j].x = Rx;
			(*data_points)[i][j].y = Ry;
			j++;
		}
		i++;
	}

}


/**
 * transform_data - apply transformation from 3d to 2d
 * to fit the points in the window
 * @data: the int pointer containing the data
 * @data_points: the array containing the points x and y
 * @angle: the rotation angle of the grid
 */
void transform_data(int data[MAP_WIDTH][MAP_WIDTH],
		SDL_Point (*data_points)[MAP_WIDTH][MAP_WIDTH], float angle)
{
	int i = 0, j = 0, Rx = 0, Ry = 0, x = 0, y = 0, X = 0, Y = 0;
	int min_y = 0, min_x = 0, max_x = INT_MIN, max_y = INT_MIN;
	int min_dim = (global_vars.SCREEN_HEIGHT < global_vars.SCREEN_WIDTH)
		? global_vars.SCREEN_HEIGHT : global_vars.SCREEN_WIDTH;
	int box_width = min_dim - 2 * global_vars.MARGIN;
	int box_height = min_dim - 2 * global_vars.MARGIN;
	int dy = (box_height / (MAP_WIDTH - 1)), dx = (box_width / (MAP_WIDTH - 1));
	int xOffset = (global_vars.SCREEN_WIDTH - box_width) / 2 - 100;
	int yOffset = (global_vars.SCREEN_HEIGHT - box_height) / 2 + 100;

	(void)(angle), (void)(Rx), (void)(Ry);
	/*Transform the data from 3d space to into 2d*/
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			x = j * dx;
			y = i * dy;
			to2D(x, y, data[i][j], &X, &Y);
			(*data_points)[i][j].x = X;
			(*data_points)[i][j].y = Y;
			if (min_x > X)
				min_x = X;
			if (min_y > Y)
				min_y = Y;
			j++;
		}
		i++;
	}

	/*Make the minimum value 0 and add the offsets*/
	i = 0;
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			(*data_points)[i][j].x += -1 * min_x + xOffset;
			(*data_points)[i][j].y += -1 * min_y + yOffset;

			X = (*data_points)[i][j].x;
			Y = (*data_points)[i][j].y;
			if (max_x < X)
				max_x = X;
			if (max_y < Y)
				max_y = Y;

			j++;
		}
		i++;
	}
	/*print_points(*data_points);*/
}
/**
 * draw_grid - draws a grid based on point arrays
 * @data: the array containing all the points
 */
void draw_grid(SDL_Point (*data)[MAP_WIDTH][MAP_WIDTH])
{
	int i = 0, j = 0, Wy = 0, Wx = 0, X = 0, Y = 0;

	/*Draw rows first*/
	i = 0;
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH - 1)
		{

			X = (*data)[i][j].x;
			Y = (*data)[i][j].y;

			Wx = (*data)[i][j + 1].x;
			Wy = (*data)[i][j + 1].y;

			SDL_RenderDrawLine(global_vars.instance.renderer, X, Y, Wx, Wy);
			j++;
		}
		i++;

	}
	i = 0;
	/*Draw colsggregate value used where a float was expected first*/
	while (i < MAP_WIDTH - 1)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{

			X = (*data)[i][j].x, Y = (*data)[i][j].y;
			Wx = (*data)[i + 1][j].x, Wy = (*data)[i + 1][j].y;

			SDL_RenderDrawLine(global_vars.instance.renderer, X, Y, Wx, Wy);
			j++;
		}
		i++;

	}
	SDL_RenderPresent(global_vars.instance.renderer);
}

