#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "datatypes.h"
#include "scene.h"
#include "fileparser.h"

#include "game.h"
class Game;

class HiScores : public Scene{
public:

	HiScores(Game* game, SDL_Renderer* renderer);
	~HiScores();
	
	void Input() override;
	void Update() override;
	void Draw() override;

private:
	Texture background;
	Font title;
	Texture titleBorder;

	ButtonManager* buttonManager;
	TextFileParser<PlayerInfo>* fileParser;
	std::vector<PlayerInfo> players;

	Font first;
	Font second;
	Font third;
};