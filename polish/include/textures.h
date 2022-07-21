#pragma once

#include <SDL2/SDL.h>

typedef struct Column
{
	int w;
	int h;
} Column;

typedef struct Layout
{
	int totalRows;
	int totalColumns;
} Layout;


typedef struct Animation
{
	char* name; // pointer to a string
	int from;
	int to;
} Animation;

typedef struct AnimatedTexture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
	Layout layout;
	Column column;
	Animation* animations;
	int _animationsCount; // DO NOT MODIFY!!
} AnimatedTexture;

typedef struct Texture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
} Texture;