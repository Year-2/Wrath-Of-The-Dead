#include "gameplay.h"
#include "collision.h"

using std::cout;
using std::endl;

Gameplay::Gameplay(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	title.Init(renderer, "test.ttf", 40, "GAMEPLAY", Vector2D<int>(370, 59), { 255, 255, 255, 255 });
	background.Init(renderer, "bluepanel.png");
	background.SetNineDst(262, 26, 500, 100, 5);
	background.SetNineSrc(5, 32, 32);

	tileMap = new Tilemap(renderer);
	enemyManager = new EnemyManager(renderer);
	userInterface = new UserInterface(renderer);
	player = new Player(renderer);
	score = 0;
}

Gameplay::~Gameplay() {
	isRunning = false;
	for (int i = 0; i < 512; i++) {
		keyDown[i] = false;
	}
	delete tileMap;
	delete enemyManager;
	delete userInterface;
	delete player;
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
	if (getKeyDown(SDL_SCANCODE_Q)) {
		isRunning = false;
		game->SetMenuOptions(Game::Menu::mainmenu);
	}
	player->Input(keyDown);
}

void Gameplay::Update() {
	enemyManager->Update();
	player->Update();

	auto& bullets(player->GetBullets());
	auto& enemies(enemyManager->GetEnemies());

	for (auto& bullet : bullets) {
		if(bullet->Active())
			for (auto& enemy : enemies) {
				if (enemy->Active())
					if (Collision::boxCollision(bullet->GetCollider(), enemy->GetCollider())) {
						bullet->Deactivate();
						enemy->Deactivate();
						userInterface->Score(++score);
					}
			}
	}
}

void Gameplay::Draw() {
	SDL_RenderClear(renderer);

	tileMap->Draw();
	enemyManager->Draw();
	background.DrawNine();
	title.Draw();
	userInterface->Draw();
	player->Draw();

	SDL_RenderPresent(renderer);
}