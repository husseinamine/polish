#include <stdio.h>
#include "game.h"
#include "engine.h"
#include "entity.h"
#include "player.h"

Texture backgroundImage;
AnimatedTexture player;
int moving = 0;

void init()
{
	PolishEngine_LoadTexture(&backgroundImage, "res/images/bg.png", 0, 0);
	PolishEngine_LoadAnimatedTexture(&player, "res/data/player.json", 0, 350);

	Entity* e = CreateEntity(50, 30);
	AddComponent(e, &playerInit);
	AddComponent(e, &playerUpdate);
	AddComponent(e, &playerRender);
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
