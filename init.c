#include "terrain.h"


/**
* init - initalizes a window and a renderer for an SDL program
* Exits if error happens returns nothing on success
*/
void init(void)
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		dprintf(2, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/*Create window */
	global_vars.instance.window = SDL_CreateWindow("Visualize terrain",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			global_vars.SCREEN_WIDTH,
			global_vars.SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (!global_vars.instance.window)
	{
		dprintf(2, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	/*Create a renderer*/
	global_vars.instance.renderer = SDL_CreateRenderer(
			global_vars.instance.window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!global_vars.instance.renderer)
	{
		dprintf(2, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}
/**
 *clean_close - cleans up during exit of the program
 *
 */
void clean_close(void)
{
	if (global_vars.fd)
		fclose(global_vars.fd);
	SDL_DestroyWindow(global_vars.instance.window);
	SDL_Quit();
}

