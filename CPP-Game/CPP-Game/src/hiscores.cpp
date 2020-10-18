#include "hiscores.h"

using std::cout;
using std::endl;

HiScores::HiScores(Game* game, SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->game = game;
	isRunning = true;
	std::memset(keyDown, false, sizeof(keyDown));

	background.Init(renderer, "test.png");
	background.SetDst(262, 26, 500, 100);
	title.Init(renderer, "test.ttf", "HISCORES", 40, 381, 59, white);
}

HiScores::~HiScores() {
	isRunning = false;
	std::memset(keyDown, false, sizeof(keyDown));
	renderer = nullptr;
	game = nullptr;
}

void HiScores::Input() {
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
}

void HiScores::Update() {

}

void HiScores::Draw() {
	SDL_RenderClear(renderer);

	background.Draw();
	title.Draw();

	SDL_RenderPresent(renderer);
}