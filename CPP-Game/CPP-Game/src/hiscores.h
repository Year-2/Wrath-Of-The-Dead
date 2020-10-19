#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "datatypes.h"

#include "game.h"
class Game;

class HiScores{
public:

	HiScores(Game* game, SDL_Renderer* renderer);
	~HiScores();
	
	void Input();
	void Update();
	void Draw();

	bool getKeyDown(int keyCode) {
		if (keyCode > 0 && keyCode < 512) {
			return keyDown[keyCode];
		}
		return false;
	}
	bool isRunning;

private:
	bool keyDown[512];
	SDL_Event e;
	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Renderer* renderer;
	Game* game;

	Texture background;
	Font title;
	Texture titleBorder;

	ButtonManager* buttonManager;

};