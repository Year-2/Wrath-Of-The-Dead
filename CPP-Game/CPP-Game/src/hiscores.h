#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "game.h"

class HiScores{
public:

	HiScores();
	~HiScores();
	
	void Input();
	void Update();
	void Draw();

	bool isRunning;

private:

};