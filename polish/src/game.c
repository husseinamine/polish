#include <stdio.h>
#include "game.h"
#include "engine.h"

Texture backgroundImage;
AnimatedTexture ball;

void init()
{
	PolishEngine_LoadTexture(&backgroundImage, "res/images/bg.png", 0, 0);
	PolishEngine_LoadAnimatedTexture(&ball, "res/data/ball.json", 0, 0);
}

void update(double deltaTime)
{
}

void render()
{

	PolishEngine_Blit(&backgroundImage);
	//PolishEngine_BlitAnimatedTexture(&ball, "monke");
	printf("%s", ball.animations[1].name);
}

void cleanup()
{
	SDL_DestroyTexture(backgroundImage.texture);
	SDL_DestroyTexture(ball.texture);
	printf("cleaned up game!\n");
}
