#pragma once

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
} Game;

// returns 0, if succeed or -1 if something went wrong.
int PolishEngine_Init(char* title, unsigned int width, unsigned int height);