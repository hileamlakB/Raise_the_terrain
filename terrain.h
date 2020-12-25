#ifndef TERRAIN
#define TERRAIN

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <limits.h>

/*constants*/
#define MAP_WIDTH 8

/**
 * struct SDL_Instance - instance for a program holding window and renderer
 * @window: window pointer to hold the window object
 * @renderer: a pointer to hold the renderer object
 */
typedef struct SDL_Instance 
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

typedef struct globals
{
	SDL_Instance instance;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	const int MARGIN;
	FILE *fd;
	const float INCLINATION;
} globals;

extern globals global_vars;


/*loader*/
void load(FILE *, int (*)[MAP_WIDTH][MAP_WIDTH]);
FILE *sopen(char *);

/*SDL_utils*/
void init(void);
void clean_close(void);

/*Graphic funcs*/
void transform_data(int [MAP_WIDTH][MAP_WIDTH], SDL_Point (*)[MAP_WIDTH][MAP_WIDTH], float);
void draw_grid(SDL_Point (*)[MAP_WIDTH][MAP_WIDTH]);
void rotate_grid(SDL_Point (*)[MAP_WIDTH][MAP_WIDTH], float);

/*memory utils*/
void *srealloc(void *, unsigned int);
void *smalloc(unsigned int);
char *_strdup(char *);

/*utils*/
int isint(char *);
int map(int, int, int);
void to2D(int, int, int, int *, int *);

#endif /*TERRAIN*/

