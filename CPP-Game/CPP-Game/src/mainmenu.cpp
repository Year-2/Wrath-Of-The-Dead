#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->game = game;
	isRunning = true;
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}


	background.Init(renderer, "test.png");
	background.SetDst(262, 26, 500, 100);
	title.Init(renderer, "test.ttf", "MAIN MENU", 40, 369, 59, white);
}

MainMenu::~MainMenu() {

}

void MainMenu::Input() {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
			game->SetIsRunning(false);
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
		}
	}
	if (getKeyDown(SDL_SCANCODE_UP)) {
		isRunning = false;
		game->SetMenuOptions(Game::Menu::gameplay);
	}
	if (getKeyDown(SDL_SCANCODE_DOWN)) {
		isRunning = false;
		game->SetMenuOptions(Game::Menu::hiscores);
	}
	if (getKeyDown(SDL_SCANCODE_LEFT)) {
		isRunning = false;
		game->SetMenuOptions(Game::Menu::mainmenu);
	}
	if (getKeyDown(SDL_SCANCODE_RIGHT)) {
		cout << "MAIN MENU" << endl;
	}
}

void MainMenu::Update() {
}

void MainMenu::Draw() {
	SDL_RenderClear(renderer);

	background.Draw();
	title.Draw();

	SDL_RenderPresent(renderer);
}
