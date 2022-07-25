#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	if (!(*quit))
	{
		update(deltaTime);
	}
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

// loads texture
void PolishEngine_LoadTexture(Texture *texture, char* filename, int x, int y)
{
	SDL_Texture* sdlTexture;
	SDL_Rect dest;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s\n", filename);

	sdlTexture = IMG_LoadTexture(game.renderer, filename);

	if (sdlTexture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Cannot load texture %s\n", filename);
	}
	else
	{
		texture->texture = sdlTexture;
		SDL_QueryTexture(texture->texture, NULL, NULL, &dest.w, &dest.h);

		texture->w = dest.w;
		texture->h = dest.h;
		texture->scale = 1;
		texture->x = x;
		texture->y = y;
	}
}

// loads animated texture
void PolishEngine_LoadAnimatedTexture(AnimatedTexture* animatedTexture, char* jsonfile, int x, int y)
{
	animatedTexture->x = x;
	animatedTexture->y = y;

	JSON_Value* root = json_parse_file(jsonfile);
	JSON_Object* rootObject = json_value_get_object(root);

	JSON_Object* metaObject = json_object_get_object(rootObject, "meta");
	char* filename = json_object_dotget_string(metaObject, "image");
	animatedTexture->w = json_object_dotget_number(metaObject, "size.w");
	animatedTexture->h = json_object_dotget_number(metaObject, "size.h");
	animatedTexture->scale = json_object_get_number(metaObject, "scale");

	JSON_Object* columnObject = json_object_get_object(rootObject, "columnSize");
	animatedTexture->column.w = json_object_get_number(columnObject, "w");
	animatedTexture->column.h = json_object_get_number(columnObject, "h");

	JSON_Object* layoutObject = json_object_get_object(rootObject, "layout");
	animatedTexture->layout.rows = json_object_get_number(layoutObject, "rows");
	animatedTexture->layout.columns = json_object_get_number(layoutObject, "columns");

	JSON_Array* animationsArray = json_object_get_array(rootObject, "animations");
	animatedTexture->_animationsCount = json_array_get_count(animationsArray);
	animatedTexture->animations = malloc(sizeof(Animation) * animatedTexture->_animationsCount);
	
	for (int i = 0; i < animatedTexture->_animationsCount; i++)
	{
		JSON_Object* animationObject = json_array_get_object(animationsArray, i);

		char* _animationName = json_object_get_string(animationObject, "name");
		int _length = sizeof(char) * (strlen(_animationName) + 1);
		char* animationName = malloc(_length);
		strcpy_s(animationName, _length, _animationName);

		animatedTexture->animations[i].name = animationName;

		JSON_Object* fromObject = json_object_get_object(animationObject, "from");
		animatedTexture->animations[i].fromRow = json_object_get_number(fromObject, "row");
		animatedTexture->animations[i].fromColumn = json_object_get_number(fromObject, "column");

		animatedTexture->animations[i].frames = json_object_get_number(animationObject, "frames");
		animatedTexture->animations[i].frameDuration = json_object_get_number(animationObject, "frameDuration");
	}

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s\n", filename);

	animatedTexture->texture = IMG_LoadTexture(game.renderer, filename);

	if (animatedTexture->texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Cannot load texture %s\n", filename);
	}

	json_value_free(root);
}

// draws static texture
void PolishEngine_Blit(Texture* texture)
{
	SDL_Rect dest = {
		texture->x, texture->y,
		texture->w * texture->scale, 
		texture->h * texture->scale
	};

	SDL_RenderCopy(game.renderer, texture->texture, NULL, &dest);
}

// draws animated texture
void PolishEngine_BlitAnimatedTexture(AnimatedTexture* texture, char* animation)
{
	Animator* animator = &texture->animator;
	int foundAnimation = 0;
	int animationIndex = 0;

	for (int i = 0; i < texture->_animationsCount; i++)
	{
		if (foundAnimation)
			break;

		if (!strcmp(animation, texture->animations[i].name))
		{
			foundAnimation = 1;
			animationIndex = i;
		}
	}

	if (foundAnimation)
	{
		int fromColumn = texture->animations[animationIndex].fromColumn;
		int fromRow = texture->animations[animationIndex].fromRow;
		int frames = texture->animations[animationIndex].frames;
		int frameDuration = texture->animations[animationIndex].frameDuration;
		Layout layout = texture->layout;
		Column column = texture->column;

		if (!(animator->_currentAnimation == animationIndex))
		{
			animator->_currentAnimation = animationIndex;
			animator->frameStarted = 0; 
			animator->frameCurrent = 0; 
			animator->currentColumn = -1;
			animator->currentRow = -1;
		}

		if (animator->currentColumn < 0 && animator->currentRow < 0)
		{
			animator->currentColumn = fromColumn - 1;
			animator->currentRow = fromRow - 1;
		}

		if (!animator->frameStarted)
		{
			animator->frameStarted = 1;
			animator->frameStart = PolishEngine_GetTicks();
		}

		animator->frameNow = PolishEngine_GetTicks() - animator->frameStart;

		if (animator->frameNow >= frameDuration)
		{
			animator->frameStarted = 0;

			if (animator->currentColumn < layout.columns)
			{	
				SDL_Rect src = {
					column.w * animator->currentColumn, column.h * animator->currentRow,
					column.w,
					column.h
				};

				SDL_Rect dest = {
					texture->x, texture->y,
					texture->w * texture->scale,
					texture->h * texture->scale
				};

				animator->currentSrc = src;
				animator->currentDst = dest;

				animator->currentColumn++;
				animator->frameCurrent++;
			}
			else
			{
				animator->currentRow++;
				animator->currentColumn = 0;
			}
		}

		if (animator->frameCurrent > frames - 1)
		{
			animator->currentColumn = fromColumn - 1;
			animator->currentRow = fromRow - 1;
			animator->frameCurrent = 0;
		}
	}

	SDL_RenderCopy(game.renderer, texture->texture, &animator->currentSrc, &animator->currentDst);
}
