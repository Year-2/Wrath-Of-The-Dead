#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu() {
	isRunning = true;
	title = FontManager::loadFont("test.ttf", 20);
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
}

MainMenu::~MainMenu() {

}

void MainMenu::Input() {
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
		cout << "MAIN MENU" << endl;
	}
}

void MainMenu::Update() {
}

void MainMenu::Draw() {
	SDL_RenderClear(Game::renderer);

	FontManager::drawFont(title, "MAIN MENU", 200, 200, white);
	
	SDL_RenderPresent(Game::renderer);
}
