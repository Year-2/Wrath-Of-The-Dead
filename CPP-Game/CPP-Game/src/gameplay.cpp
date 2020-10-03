#include "gameplay.h"

using std::cout;
using std::endl;

Gameplay::Gameplay() {
	isRunning = true;
}

Gameplay::~Gameplay() {

}

void Gameplay::Input() {
	while (SDL_PollEvent(&Game::e) != 0) {
		if (Game::e.type == SDL_QUIT)
		{
			isRunning = false;
			Game::isRunning = false;
		}
		else if (Game::e.type == SDL_KEYDOWN)
		{
			switch (Game::e.key.keysym.sym)
			{
			case SDLK_UP:
				isRunning = false;
				Game::menuOptions = Game::Menu::gameplay;
				break;

			case SDLK_DOWN:
				isRunning = false;
				Game::menuOptions = Game::Menu::hiscores;
				break;

			case SDLK_LEFT:
				isRunning = false;
				Game::menuOptions = Game::Menu::mainmenu;
				break;

			case SDLK_RIGHT:
				cout << "GamePlay" << endl;
				break;

			default:
				break;
			}
		}
	}
}

void Gameplay::Update() {

}

void Gameplay::Draw() {

}