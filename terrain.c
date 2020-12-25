#include "terrain.h"

globals global_vars = {{NULL, NULL}, 1400, 640, 20, NULL, 0.7};

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
	int data[MAP_WIDTH][MAP_WIDTH];/*, box_dimentions = 0;*/
	SDL_Point data_points[MAP_WIDTH][MAP_WIDTH];
	int angle = 0;
	float a;

	atexit(clean_close);

	if (argc != 2)
	{
		dprintf(2, "Usage: %s terrain_altitude_files\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*open the terrian file*/
	global_vars.fd = sopen(argv[1]);

	/*load the data from file in to an array*/
	load(global_vars.fd, &data);

	/*transform the cordinatees to fit into the window*/
	transform_data(data, &data_points, 0);

	/*Initialize SDL and get the window started*/
	init();


	draw_grid(&data_points);
	while (running)
	{
		//Handle events on queue
		while( SDL_PollEvent(&event_info) != 0 )
		{
			//User requests quit
			if(event_info.type == SDL_QUIT ||
					(event_info.key.keysym.sym == SDLK_ESCAPE))
				running = SDL_FALSE;
			if (event_info.key.keysym.sym == SDLK_RIGHT || event_info.key.keysym.sym == SDLK_LEFT)
			{
				angle = (event_info.key.keysym.sym == SDLK_RIGHT) ? angle + 1 : angle - 1;
				a = angle * M_PI / 180;
				printf("==>%f\n", a);

				SDL_SetRenderDrawColor(global_vars.instance.renderer, 0, 0, 0, 0);
				SDL_RenderClear(global_vars.instance.renderer);

				transform_data(data, &data_points, a);
				draw_grid(&data_points);

			}

		}


	}

	exit(EXIT_SUCCESS);
}
