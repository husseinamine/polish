#include <stdio.h>
#include "engine.h"

int main(int argc, char* argv[])
{
	int running = 1;

	int err = PolishEngine_Init("Polish v0.1", 800, 600);

	if (err)
	{
		printf("bruh moment.");
	}
	else 
	{
		printf("game running successfully!");
	}

	int x, y;

	while (running) 
	{
		running = PolishEngine_Update();
		PolishEngine_GetMouse(1, &x, &y);

		printf("x: %d, y: %d\n", x, y);
	}

	return err;
}
