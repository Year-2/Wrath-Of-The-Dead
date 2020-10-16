#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <unordered_map>

#include "texturemanager.h"

class Tile {
public:


private:

};

class Tilemap {
public:
	Tilemap();

	const char* map =
		"WWWDDSDDWWW"
		"WWWDDSDDWWW"
		"WWWDDSDDWWW"
		"WWWDDSDDWWW"
		"WWWDDSDDWWW"
		"WWWDDSDDWWW"
		"WWWDDSDDWWW";

	std::unordered_map<char, SDL_Texture*> tiles;

private:
	int width = 11;
	int height = strlen(map) / 11;
};
