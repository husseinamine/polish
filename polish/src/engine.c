#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include "parson.h"
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

// engine related updates
void PolishEngine_Update(int *quit, void (* update)(double), double deltaTime)
{
	SDL_PollEvent(&game.event);

	switch (game.event.type)
	{
		case SDL_QUIT:
			SDL_DestroyWindow(game.window);
			SDL_DestroyRenderer(game.renderer);
			SDL_Quit();

			*quit = 1;
			break;

		default:
			break;
	}

	update(deltaTime);
}

// updating screen
void PolishEngine_Render(void (* render)())
{
	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
	SDL_RenderClear(game.renderer);
	render();
	SDL_RenderPresent(game.renderer);
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
			return 0;
			break;
	}
} 

// return ticks from sdl
Uint64 PolishEngine_GetTicks()
{
	return SDL_GetTicks64();
}

// loads texture and returns it
SDL_Texture* PolishEngine_LoadTexture(char* filename)
{
	SDL_Texture* texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s\n", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Cannot load texture %s\n", filename);
	}

	return texture;
}

//TODO:COMplete this bruh 
struct AnimatedTexture* PolishEngine_LoadAnimatedTexture(char* imgfile, char* jsonfile)
{
	JSON_Value* root = json_parse_file(jsonfile);

	JSON_Object* rootObject = json_value_get_object(root);
	printf(json_object_get_string(rootObject, "test"));

	return NULL;
}

// draws static texture
void PolishEngine_Blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	dest.w *= 2;
	dest.h *= 2;

	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

//TODO:COMplete this bruh 
static SDL_Texture** _GetAnimation(struct AnimatedTexture* texture, char* animation)
{
}

//TODO:COMplete this bruh 
void PolishEngine_BlitAnimatedTexture(struct AnimatedTexture* texture, char* animation, int x, int y)
{
}
