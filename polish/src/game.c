#include "game.h"
#include "engine.h"

SDL_Texture* player;

void init()
{
	player = PolishEngine_LoadTexture("res/player.png");
}

void update()
{
}

void render()
{
	PolishEngine_Blit(player, 0, 0);
}
