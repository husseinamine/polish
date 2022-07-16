#include <stdio.h>
#include <time.h>
#include "engine.h"
#include "game.h"

int main(int argc, char* argv[])
{
	int quit = 0;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS; 

	Uint64 frameStart;
	Uint64 frameTime;

	int err = PolishEngine_Init("Polish v0.1", 800, 600);

	if (err)
	{
		printf("bruh moment.\n");
	}
	else 
	{
		printf("game running successfully!\n");
	}

	init();

	while (!quit)
	{
		frameStart = PolishEngine_GetTicks();

		PolishEngine_Update(&quit, &update);
		PolishEngine_Render(&render);

		frameTime = PolishEngine_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return err;
}
