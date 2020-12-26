#include "terrain.h"

globals global_vars = {{NULL, NULL}, 1000, 680, 20, NULL, 0.7};

/**
 * main - entry point to the terrain program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char **argv)
{
	SDL_bool running = SDL_TRUE;
	SDL_Event event_info;
	int data[MAP_WIDTH][MAP_WIDTH], angle = 0;/*, box_dimentions = 0;*/
	SDL_Point data_points[MAP_WIDTH][MAP_WIDTH];
	float a;

	(void)a;
	atexit(clean_close);

	if (argc != 2)
	{
		dprintf(2, "Usage: %s terrain_altitude_files\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	global_vars.fd = sopen(argv[1]);
	load(global_vars.fd, &data);
	transform_data(data, &data_points, 0);

	init();

	draw_grid(&data_points);
	while (running)
	{
		/*Handle events on queue*/
		while (SDL_PollEvent(&event_info) != 0)
		{
			/*User requests quit*/
			if (event_info.type == SDL_QUIT ||
					(event_info.key.keysym.sym == SDLK_ESCAPE))
				running = SDL_FALSE;
			if (event_info.key.keysym.sym == SDLK_RIGHT
					|| event_info.key.keysym.sym == SDLK_LEFT)
			{
				angle = (event_info.key.keysym.sym == SDLK_RIGHT) ? angle + 1 : angle - 1;
				a = angle * M_PI / 180;

				SDL_RenderClear(global_vars.instance.renderer);

				rotate_grid(data, &data_points, 0);
				draw_grid(&data_points);
				angle = 0;
			}
		}

	}
	exit(EXIT_SUCCESS);
}
