#pragma once
#include "datatypes.h"

class CoinPS;

class Chest {
public:
	Chest(SDL_Renderer* renderer);
	~Chest();

	void SpawnChest();
	void OpenChest(CoinPS* coinPS);

	void Draw();

	SDL_Rect& GetCollider();
	Vector2D<int>& GetPosition() { return position; }
	bool IsOpen() { return alreadyOpen; }

private:
	Texture chest;
	SDL_Rect collider;
	Vector2D<int> position;

	unsigned int lastAnimation;
	short currentAnimation;
	short animationCount;
	bool alreadyOpen;
};