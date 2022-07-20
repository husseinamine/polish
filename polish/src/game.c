#include "game.h"
#include "engine.h"

struct player
{
	SDL_Texture* texture;
	int x, y;
} player;

void init()
{
	player.texture = PolishEngine_LoadTexture("res/player.png");
	player.x = 0;
	player.y = 0;
}

void update(double deltaTime)
{
	if (PolishEngine_GetKey("d"))
	{
		player.x += 90 * deltaTime;
	}

	PolishEngine_LoadAnimatedTexture("TEST", "res/data/test.json");
}

void render()
{
	PolishEngine_Blit(player.texture, player.x, player.y);
}
