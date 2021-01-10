#include "chest.h"
#include "vector2d.h"
#include "coin.h"

#define ANIMATION_TIMER 300
#define RANGE_OFFSET 96

Chest::Chest(SDL_Renderer* renderer)
{
	position = {
		(rand() % 28 + 2) * 32,
		(rand() % 14 + 2) * 32
	};

	chest.Init(renderer, "chest.png");
	chest.SetSrc(0, 0, 16, 16);
	chest.SetDst(position.x, position.y, 32, 32);

	collider = { (position.x + 16 / 2) - RANGE_OFFSET / 2, (position.y + 16 / 2) - RANGE_OFFSET / 2,RANGE_OFFSET,RANGE_OFFSET };
	lastAnimation = 0;
	currentAnimation = 0;
	alreadyOpen = false;
	animationCount = 0;
}

Chest::~Chest()
{

}

void Chest::SpawnChest()
{

}

void Chest::OpenChest(CoinPS* coinPS)
{
	if (!alreadyOpen) {
		if (SDL_GetTicks() - lastAnimation > ANIMATION_TIMER) {
			currentAnimation + 1 > 2 ? alreadyOpen = true : currentAnimation++;
			chest.SetSrc(16 * currentAnimation, 0, 16, 16);
			lastAnimation = SDL_GetTicks();

			if (animationCount == 0) {
				coinPS->Spawn();
				animationCount++;
			}
		}
	}
}

void Chest::Draw()
{
	chest.Draw();
}

SDL_Rect& Chest::GetCollider()
{
	return collider;
}
