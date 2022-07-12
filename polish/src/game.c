#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	return 0;
}