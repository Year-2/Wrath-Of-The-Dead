#include "gameplay.h"

using std::cout;
using std::endl;

Gameplay::Gameplay(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	background.Init(renderer, "bluepanel.png");
	background.SetDst(262, 26, 500, 100);
	background.SetNine(5, 32, 32);
	title.Init(renderer, "test.ttf", "GAMEPLAY", 40, 370, 59, white);

	tileMap = new Tilemap(renderer);
}

Gameplay::~Gameplay() {
	isRunning = false;
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
	renderer = nullptr;
	game = nullptr;
	delete tileMap;
	tileMap = nullptr;
}

void Gameplay::Input() {
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

void Gameplay::Update() {

}

void Gameplay::Draw() {
	SDL_RenderClear(renderer);

	tileMap->Draw();
	background.DrawNine();
	title.Draw();

	SDL_RenderPresent(renderer);

}