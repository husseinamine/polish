#pragma once

#include <SDL2/SDL.h>

typedef struct Column
{
	int w;
	int h;
} Column;

typedef struct Layout
{
	int rows;
	int columns;
} Layout;

typedef struct Animation
{
	char* name;

	int fromRow;
	int toRow;

	int fromColumn;
	int toColumn;
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