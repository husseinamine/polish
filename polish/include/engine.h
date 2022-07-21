#pragma once

#include <SDL2/SDL.h>
#include "textures.h"

#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 2
#define MOUSE_RIGHT 3

struct Game 
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} game;

// returns 0, if succeed or -1 if something went wrong.
int PolishEngine_Init(char* title, Uint16 width, Uint16 height);

// engine related updates
void PolishEngine_Update(int *quit, void (* update)(double), double deltaTime);

// updating screen
void PolishEngine_Render(void (* render)());

// returns 1 if key is pressed
Uint8 PolishEngine_GetKey(const char* key);

// returns sdl bitmask of mouse index (left = 1 / middle = 2 / right = 3) if it is pressed
Uint32 PolishEngine_GetMouse(int index, int* x, int* y);

// return ticks from sdl
Uint64 PolishEngine_GetTicks();

// loads texture
void PolishEngine_LoadTexture(Texture* texture, char* filename, int x, int y);

// loads animated texture
void PolishEngine_LoadAnimatedTexture(AnimatedTexture* animatedTexture, char* jsonfile, int x, int y);

// draws static texture
void PolishEngine_Blit(Texture* texture);

// draws animated texture
void PolishEngine_BlitAnimatedTexture(AnimatedTexture* texture, char* animation);