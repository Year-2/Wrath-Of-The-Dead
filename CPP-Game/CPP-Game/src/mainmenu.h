#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "game.h"
#include "fontmanager.h"

class FontManager;

class MainMenu {
public:

	MainMenu();
	~MainMenu();

	void Input();
	void Update();
	void Draw();

	bool isRunning;

	bool getKeyDown(int keyCode) {
		if (keyCode > 0 && keyCode < 512) {
			return keyDown[keyCode];
		}
		return false;
	}

private:
	bool keyDown[512];

	SDL_Color white = { 255, 255, 255, 255 };
	TTF_Font* title;


};