#include "engine.h"

// returns 0, if succeed or -1 if something went wrong.
int PolishEngine_Init(char* title, Uint16 width, Uint16 height)
{
	int err = SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	if (err) 
	{
		printf("something went wrong while initiializing SDL SubSystems... %s", SDL_GetError());
	}


	game.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (game.window == NULL)
	{
		printf("something went wrong while creating SDL Window... %s", SDL_GetError());
	}

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

// returns 1 if it will complete loop, and 0 if it quited
int PolishEngine_Update()
{
	SDL_PollEvent(&game.event);

	switch (game.event.type)
	{
		case SDL_QUIT:
			SDL_DestroyWindow(game.window);
			SDL_DestroyRenderer(game.renderer);
			SDL_Quit();

			return 0;
			break;

		default:
			break;
	}

	return 1;
}

// returns 1 if key is pressed
Uint8 PolishEngine_GetKey(const char *key)
{
	SDL_PumpEvents();

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	return state[SDL_GetScancodeFromName(key)];
}

// returns sdl bitmask of mouse index (left = 1 / middle = 2 / right = 3) if it is pressed
Uint32 PolishEngine_GetMouse(int index, int *x, int *y)
{
	SDL_PumpEvents();

	const Uint32 state = SDL_GetMouseState(x, y);

	switch (index)
	{
		case MOUSE_LEFT:
			return state & SDL_BUTTON_LMASK;
			break;

		case MOUSE_MIDDLE:
			return state & SDL_BUTTON_MMASK;
			break;

		case MOUSE_RIGHT:
			return state & SDL_BUTTON_RMASK;
			break;

		default:
			break;
	}
}