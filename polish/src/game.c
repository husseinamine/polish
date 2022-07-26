#include <stdio.h>
#include "game.h"
#include "engine.h"
#include "entity.h"

Texture backgroundImage;
AnimatedTexture player;
int moving = 0;

void test(void* args)
{
	printf("test\n");
}

void test2(void *args)
{
	printf("test2\n");
}

void init()
{
	PolishEngine_LoadTexture(&backgroundImage, "res/images/bg.png", 0, 0);
	PolishEngine_LoadAnimatedTexture(&player, "res/data/player.json", 0, 350);
	Entity e = CreateEntity(0, 0);
	AddComponent(&e, &test);
	AddComponent(&e, &test2);

	e.components[0](NULL);
	e.components[1](NULL);
}

void update(double deltaTime)
{
	if (PolishEngine_GetKey("d"))
	{
		player.x += 3 * (deltaTime * FPS);
		moving = 1;
	}
	else if (PolishEngine_GetKey("a"))
	{
		player.x -= 3 * (deltaTime * FPS);
		moving = 1;
	}
	else
	{
		moving = 0;
	}
}

void render()
{
	PolishEngine_Blit(&backgroundImage);
	player.scale = 3;

	if (moving)
	{
		PolishEngine_BlitAnimatedTexture(&player, "walk");
	}
	else {
		PolishEngine_BlitAnimatedTexture(&player, "idle");
	}
}

void cleanup()
{
	SDL_DestroyTexture(backgroundImage.texture);
	SDL_DestroyTexture(player.texture);
	printf("cleaned up game!\n");
}
