#include "gameplay.h"

using std::cout;
using std::endl;

Gameplay::Gameplay(Game* game, SDL_Renderer* renderer) {
	isRunning = true;
	this->game = game;
	this->renderer = renderer;
	std::memset(keyDown, false, sizeof(keyDown));

	background.Init(renderer, "test.png");
	background.SetDst(262, 26, 500, 100);
	title.Init(renderer, "test.ttf", "GAMEPLAY", 40, 370, 59, white);

	tiles['D'] = { 0, 0 ,16,16 };
	tiles['W'] = { 16, 0 ,16,16 };
	tiles['S'] = { 0, 16 ,16,16 };
	tilesTexture.Init(renderer, "tiles.png");
}

Gameplay::~Gameplay() {
	isRunning = false;
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
	renderer = nullptr;
	game = nullptr;
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

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char tile = map[x + y * width];
			tilesTexture.SetSrc(tiles[tile]);
			tilesTexture.SetDst(x * 32, y * 32, 32, 32);
			tilesTexture.Draw();
		}
	}


	background.Draw();
	title.Draw();

	SDL_RenderPresent(renderer);

}