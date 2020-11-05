#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "datatypes.h"
#include "buttonmanager.h"
#include "scene.h"
#include "game.h"

class Game;

class MainMenu : public Scene {
public:

	MainMenu(Game* game, SDL_Renderer* renderer);
	~MainMenu();

	void Input() override;
	void Update() override;
	void Draw() override;

private:

	Texture background;
	Font title;
	Texture titleBorder;

	ButtonManager* buttonManager;
};