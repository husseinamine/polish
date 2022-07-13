#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>

#define MOUSE_LEFT 1
#define MOUSE_MIDDLE 2
#define MOUSE_RIGHT 3

typedef struct Game 
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
};

struct Game game;

// returns 0, if succeed or -1 if something went wrong.
int PolishEngine_Init(char* title, Uint16 width, Uint16 height);

// returns 1 if it will complete loop, and 0 if it quited
int PolishEngine_Update();

// returns 1 if key is pressed
Uint8 PolishEngine_GetKey(const char* key);

// returns sdl bitmask of mouse index (left = 1 / middle = 2 / right = 3) if it is pressed
Uint32 PolishEngine_GetMouse(int index, int* x, int* y);