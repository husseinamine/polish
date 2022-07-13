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

	do 
	{
		running = PolishEngine_Update();
		printf("%i", PolishEngine_GetMouse(MOUSE_LEFT, NULL, NULL));
		
	} while (running);

	return err;
}
