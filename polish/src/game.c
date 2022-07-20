#include "game.h"
#include "engine.h"

Texture backgroundImage;

struct player
{
	SDL_Texture* texture;
	int x, y;
} player;

void init()
{
	backgroundImage = PolishEngine_LoadTexture("res/images/bg.png", 0, 0);
	//player.texture = PolishEngine_LoadTexture("res/player.png");
	player.x = 0;
	player.y = 0;

	PolishEngine_LoadAnimatedTexture("res/data/ball.json");
}

void update(double deltaTime)
{
	if (PolishEngine_GetKey("d"))
	{
		player.x += 90 * deltaTime;
		backgroundImage.scale = 2;
	}
	else
	{
		backgroundImage.scale = 1;
	}
}

void render()
{
	PolishEngine_Blit(&backgroundImage, backgroundImage.x, backgroundImage.y);
	//PolishEngine_Blit(player.texture, player.x, player.y);
}
