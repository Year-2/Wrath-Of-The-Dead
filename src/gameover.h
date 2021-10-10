#pragma once
#include "datatypes.h"
#include "buttonmanager.h"

class Gameplay;

class GameOver {
public:

	GameOver(SDL_Renderer* renderer, Gameplay* gameplay);
	~GameOver();

	void Input(bool* keyDown);
	void Draw();

private:
	Texture background;
	Font game;
	Font over;

	ButtonManager* buttonManager;
	Gameplay* gamePlay;
};
