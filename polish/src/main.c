#include <stdio.h>
#include <time.h>
#include "engine.h"
#include "entity.h"
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
	Entities _entities = GetEntities();
	Entity** entities = _entities.entities;
	int entities_count = _entities.entities_count;

	for (int i = 0; i < entities_count; i++)
	{
		Entity* e = entities[i];

		if (e->_components_count >= INIT_COMPONENTS_COUNT)
		{
			e->components[0](NULL); // init 
		}
		else
		{
			printf("please add the init, update and render components in the following order:\n0: init\n1: update\n2: render\n");
		}
	}

	while (!quit)
	{
		tickTime = PolishEngine_GetTicks();
		deltaTime = (((double)tickTime) * 0.001f) - lastDelta;
		lastDelta = ((double) tickTime) * 0.001f;

		frameStart = PolishEngine_GetTicks();

		PolishEngine_Update(&quit, &update, deltaTime);

		PolishEngine_Render(&render);

		Entities _entities = GetEntities();
		Entity** entities = _entities.entities;
		int entities_count = _entities.entities_count;

		for (int i = 0; i < entities_count; i++)
		{
			Entity* e = entities[i];

			if (e->_components_count >= INIT_COMPONENTS_COUNT)
			{
				e->components[1](NULL); // update 
				e->components[2](NULL); // render			
			}
			else
			{
				printf("please add the init, update and render components in the following order:\n0: init\n1: update\n2: render\n");
			}
		}

		frameTime = PolishEngine_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	cleanup();

	return 0;
}
