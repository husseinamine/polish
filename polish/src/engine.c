#include "engine.h"

struct Game game;

// returns 0, if succeed or -1 if something went wrong.
int PolishEngine_Init(char* title, unsigned int width, unsigned int height)
{
	int err = SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	if (err) {
		printf("something went wrong while initiializing SDL SubSystems... %s", SDL_GetError());
	}


	game.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (game.window == NULL)
	{
		printf("something went wrong while creating SDL Window... %s", SDL_GetError());



		game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

		if (game.renderer == NULL)
		{
			printf("something went wrong while creating SDL Renderer... %s", SDL_GetError());
		}


		if ((err != 0) && (game.window != NULL) && (game.renderer != NULL))
		{
			return -1;
		}

		return 0;
	}
}