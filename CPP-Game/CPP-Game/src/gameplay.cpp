#include "gameplay.h"

using std::cout;
using std::endl;

Gameplay::Gameplay() {
	isRunning = true;
	title = FontManager::loadFont("test.ttf", 20);
}

Gameplay::~Gameplay() {

}

void Gameplay::Input() {
	while (SDL_PollEvent(&Game::e)) {
		if (Game::e.type == SDL_QUIT)
		{
			isRunning = false;
			Game::isRunning = false;
		}
		if (Game::e.type == SDL_KEYDOWN) {
			if (Game::e.key.keysym.scancode < 512) {
				keyDown[Game::e.key.keysym.scancode] = true;
			}
		}
		else if (Game::e.type == SDL_KEYUP) {
			if (Game::e.key.keysym.scancode < 512) {
				keyDown[Game::e.key.keysym.scancode] = false;
			}
		}
	}
	if (getKeyDown(SDL_SCANCODE_UP)) {
		isRunning = false;
		Game::menuOptions = Game::Menu::gameplay;
	}
	if (getKeyDown(SDL_SCANCODE_DOWN)) {
		isRunning = false;
		Game::menuOptions = Game::Menu::hiscores;
	}
	if (getKeyDown(SDL_SCANCODE_LEFT)) {
		isRunning = false;
		Game::menuOptions = Game::Menu::mainmenu;
	}
	if (getKeyDown(SDL_SCANCODE_RIGHT)) {
		cout << "GAMEPLAY" << endl;
	}
}

void Gameplay::Update() {

}

void Gameplay::Draw() {
	SDL_RenderClear(Game::renderer);

	FontManager::drawFont(title, "GAMEPLAY", 200, 200, white);

	SDL_RenderPresent(Game::renderer);

}