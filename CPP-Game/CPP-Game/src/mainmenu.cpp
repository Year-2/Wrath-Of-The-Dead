#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu() {
	isRunning = true;
}

MainMenu::~MainMenu() {

}

void MainMenu::Input() {
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
				cout << "MainMenu" << endl;
				break;

			default:
				break;
			}
		}
	}
}

void MainMenu::Update() {
	SDL_RenderClear(Game::renderer);


	
	SDL_RenderPresent(Game::renderer);
}

void MainMenu::Draw() {

}
