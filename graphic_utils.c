#include "terrain.h"


/**
 *print_points - prints an array of SDL_Point object
 *@data: the datat
 */
void print_points(SDL_Point data[MAP_WIDTH][MAP_WIDTH])
{
	int i =0, j = 0;
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
int abs(int num)
{

	return ((num < 0)? -1 *num : num);
}

/**
 * rotate_gird - rotates a grid by an angle @angle
 * @data_points: the grid
 * @angle: the angle to rotate the grid by
 */
void rotate_grid(SDL_Point (*data_points)[MAP_WIDTH][MAP_WIDTH], float angle)
{
	int Rx = 0, Ry = 0, i = 0, j = 0, x = 0, y = 0;
	/*int min_x = 0, min_y = 0, max_x = 0, max_y = 0, X = 0, Y = 0;*/
	int centerX = global_vars.SCREEN_WIDTH / 2;
	int centerY = global_vars.SCREEN_HEIGHT / 2;
	/*int box_height = min_dim - 2 * global_vars.MARGIN;*/


(void)(centerX);
(void)(centerY);
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			x = (*data_points)[i][j].x;
			y = (*data_points)[i][j].y;

			Rx = ((x - centerX) * cos(angle) - (y - centerY) * sin(angle)) + centerX + 0.5;
			Ry = ((x - centerX) * sin(angle) + (y - centerY) * cos(angle)) + centerY + 0.5;
			/*Rx = (int)(x  * cos(angle) - y * sin(angle));
			Ry = (int)(x * sin(angle) + y * cos(angle));*/
printf("old{ %i, %i } new {%i, %i}\n", x, y, Rx, Ry);
			(*data_points)[i][j].x = Rx;
			(*data_points)[i][j].y = Ry;
			j++;
		}
		i++;
	}

}


/**
 * apply_transform - apply transformation from 3d to 2d
 * @data: the int pointer containing the data
 */
void transform_data(int data[MAP_WIDTH][MAP_WIDTH], SDL_Point (*data_points)[MAP_WIDTH][MAP_WIDTH], float angle)
{
	int i = 0, j = 0, Rx = 0, Ry = 0, x = 0, y = 0;
	int X = 0, Y = 0;
	int min_y = 0, min_x = 0, max_x = INT_MIN, max_y = INT_MIN;
	/*int min_dim = (global_vars.SCREEN_HEIGHT < global_vars.SCREEN_WIDTH) ? global_vars.SCREEN_HEIGHT : global_vars.SCREEN_WIDTH;*/
	/*int box_width = min_dim - 2 * global_vars.MARGIN;*/
	int box_width = global_vars.SCREEN_WIDTH - 2 * global_vars.MARGIN;
	/*int box_height = min_dim - 2 * global_vars.MARGIN;*/
	int box_height = global_vars.SCREEN_HEIGHT - 2 * global_vars.MARGIN;
	int dy = (box_height / (MAP_WIDTH - 1)) - 2;
	int dx = (box_width / (MAP_WIDTH - 1)) - 2;
	int xOffset = (global_vars.SCREEN_WIDTH - box_width) / 2;
	int yOffset = (global_vars.SCREEN_HEIGHT - box_height) / 2;
	const SDL_Rect rect = {xOffset, yOffset, box_width, box_height};
SDL_SetRenderDrawColor(global_vars.instance.renderer, 0xff, 0, 0, 0xff);
	SDL_RenderDrawRect(global_vars.instance.renderer, &rect);

	SDL_SetRenderDrawColor(global_vars.instance.renderer, 0xff, 0, 0xff, 0xff);

	/*Transform the data from 3d space to into 2d*/
	while (i < MAP_WIDTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			x = j * dx;
			y = i *dy;
			Rx = x  * cos(angle) - y * sin(angle);
			Ry = x * sin(angle) + y * cos(angle);
			to2D(Rx, Ry, data[i][j], &X, &Y);
			(*data_points)[i][j].x = X;
			(*data_points)[i][j].y = Y;
			if (X < min_x)
				min_x = X;
			if (Y < min_y)
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
			if (X > max_x)
				max_x = X;
			if (Y > max_y)
				max_y = Y;

			j++;
		}
		i++;
	}
	if (angle == INT_MIN){
		/*constrict the size so that it is inside the window*/
		i = 0;
		while (i < MAP_WIDTH)
		{
			j = 0;
			while (j < MAP_WIDTH)
			{
				/*old_x = (*(*data_points)[i][j].x;
				  ratio = ((float)((*(*data_points)[i][j].y) / (float)(old_x));
				 */

				(*data_points)[i][j].y = map((*data_points)[i][j].y, yOffset + box_height, max_y);
				(*data_points)[i][j].x = map((*data_points)[i][j].x, xOffset + box_width, max_x);
				/*(*(*data_points)[i][j].y = (int)((*(*data_points)[i][j].x * ratio);*/

				X = (*data_points)[i][j].x;
				Y = (*data_points)[i][j].y;
				SDL_RenderDrawPoint(global_vars.instance.renderer, X, Y);

				j++;
			}
			i++;

		}
	}
	print_points(*data_points);
}
/**
 * draw_grid - draws a grid based on point arrays
 * @data: the array containing all the points
 */
void draw_grid(SDL_Point (*data)[MAP_WIDTH][MAP_WIDTH])
{
	int i = 0, j = 0, Wy = 0, Wx = 0, X = 0, Y = 0;

	/*SDL_RenderSetScale(global_vars.instance.renderer, 5, 5);*/

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

			X = (*data)[i][j].x;
			Y = (*data)[i][j].y;

			Wx = (*data)[i + 1][j].x;
			Wy = (*data)[i + 1][j].y;

			SDL_RenderDrawLine(global_vars.instance.renderer, X, Y, Wx, Wy);
			j++;
		}
		i++;

	}
	SDL_RenderPresent(global_vars.instance.renderer);
}

