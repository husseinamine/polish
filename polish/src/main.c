#include <stdio.h>
#include <time.h>
#include "engine.h"
#include "game.h"

int main(int argc, char* argv[])
{
	int quit = 0;
	const Uint64 frameDelay = 1000 / FPS; 

	Uint64 tickTime = 0;
	double deltaTime = 0.000f, lastDelta = 0.000f; 

	Uint64 frameStart = 0, frameTime = 0;

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
		tickTime = PolishEngine_GetTicks();
		deltaTime = (((double)tickTime) * 0.001f) - lastDelta;
		lastDelta = ((double) tickTime) * 0.001f;

		frameStart = PolishEngine_GetTicks();

		PolishEngine_Update(&quit, &update, deltaTime);
		PolishEngine_Render(&render);

		frameTime = PolishEngine_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return err;
}
