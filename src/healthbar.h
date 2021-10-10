#pragma once
#include "datatypes.h"

class HealthBar {
public:

	HealthBar(SDL_Renderer* renderer, SDL_Rect& pos);

	void Draw(SDL_Rect& pos);
	void ChangeHealth(int health); //between 0-100

private:
	Texture bgSprite;
	Texture fgSprite;	
	int health;
};