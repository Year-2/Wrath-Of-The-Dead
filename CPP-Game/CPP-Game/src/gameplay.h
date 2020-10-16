#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>

#include "datatypes.h"
#include "texturemanager.h"

#include "game.h"
class Game;

//	TODO: Make functioning tilemap.
class Gameplay {
public:

	Gameplay(Game* game, SDL_Renderer* renderer);
	~Gameplay();

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

	const char* map =
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		"WWWWDDDDDDDDDDDDDDDDDDDDDDDWWWWW"
		"WWWWDDDDDDDDDDDDDDDDDDDDDDDWWWWW"
		"WWWWDDDDDSSSSSSSSSSSSSSSDDDWWWWW"
		"WWWWDDDDDSSSSSSSSSSSSSSSDDDWWWWW"
		"WWWWDDDDDSSSSSSSSSSSSSSSDDDWWWWW"
		"WWWWDDDDDSSSSSSSSSSSSSSSDDDWWWWW"
		"WWWWDDDDDSSSSSSSSSSSSSSSDDDWWWWW"
		"WWWWDDDDDDDDDDDDDSSSSSDDDDDWWWWW"
		"WWWWDDDDDDDDDDDDDSSSSSDDDDDWWWWW"
		"WWWWWWWWWWDDDDDDDSSSSSDDDDDWWWWW"
		"WWWWWWWWWWDDDDDDDSSSSSDDDDDWWWWW"
		"WWWWWWWWWWDDDDDDDDDDDDDDDDDWWWWW"
		"WWWWWWWWWWWWWWWWWWWWDDDDDWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWDDDDDWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWDDDDDWWWWWWW"
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

	std::unordered_map<char, SDL_Rect> tiles;
	int width = 32;
	int height = 18; // strlen(map) / 11;

private:
	bool keyDown[512];
	SDL_Event e;
	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Renderer* renderer;
	Game* game;

	Texture background;
	Font title;

	Texture tilesTexture;

	SDL_Texture* grass;
};
