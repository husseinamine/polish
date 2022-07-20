#pragma once

#include <SDL2/SDL.h>

typedef struct Layout
{
	int rows;
	int columns;
} Layout;

typedef struct Animation
{
	char* name;
	int from;
	int to;
} Animation;

typedef struct Column
{
	int w;
	int h;
} Column;

typedef struct AnimatedTexture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
	Layout layout;
	Column column;
	Animation* animations;
} AnimatedTexture;

typedef struct Texture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
} Texture;