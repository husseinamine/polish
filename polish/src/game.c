#include <stdio.h>
#include "game.h"
#include "engine.h"

Texture backgroundImage;
AnimatedTexture ball;
Uint64 time;
Uint64 timeNow;
Uint64 timeBefore;

void init()
{
	time = PolishEngine_GetTicks();
	PolishEngine_LoadTexture(&backgroundImage, "res/images/bg.png", 0, 0);
	PolishEngine_LoadAnimatedTexture(&ball, "res/data/ball.json", 0, 0);
}

void update(double deltaTime)
{
	timeBefore = timeNow % 100;
	timeNow = (PolishEngine_GetTicks() - time) % 100;
}

void render()
{
	PolishEngine_Blit(&backgroundImage);
	PolishEngine_BlitAnimatedTexture(&ball, "bigBall");
}

void cleanup()
{
	SDL_DestroyTexture(backgroundImage.texture);
	SDL_DestroyTexture(ball.texture);
	printf("cleaned up game!\n");
}
