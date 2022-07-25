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
	int fromColumn;

	int frames;
	int frameDuration;
} Animation;

typedef struct Animator
{
	int frameStart;
	int frameNow;
	int frameStarted; 
	int frameCurrent; 
	int currentRow;
	int currentColumn;
	SDL_Rect currentDst;
	SDL_Rect currentSrc;

	int _currentAnimation; // DO NOT MODIFY!
} Animator;

typedef struct AnimatedTexture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
	Layout layout;
	Column column;
	Animator animator;
	Animation* animations;
	int _animationsCount; // DO NOT MODIFY!
} AnimatedTexture;

typedef struct Texture
{
	SDL_Texture* texture;
	int w, h, scale;
	int x, y;
} Texture;