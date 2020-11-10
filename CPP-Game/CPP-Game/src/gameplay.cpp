#include "gameplay.h"

using std::cout;
using std::endl;

Gameplay::Gameplay(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	title.Init(renderer, "test.ttf", 40, "GAMEPLAY", Vector2D<int>(370, 59), { 255, 255, 255, 255 });
	background.Init(renderer, "bluepanel.png");
	background.SetNineDst(262, 26, 500, 100, 5);
	background.SetNineSrc(5, 32, 32);

	tileMap = new Tilemap(renderer);
	enemyManager = new EnemyManager(renderer);
}

Gameplay::~Gameplay() {
	isRunning = false;
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
	delete tileMap;
	delete enemyManager;
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
	enemyManager->Update();
}

void Gameplay::Draw() {
	SDL_RenderClear(renderer);

	tileMap->Draw();
	background.DrawNine();
	title.Draw();
	enemyManager->Draw();

	SDL_RenderPresent(renderer);
}