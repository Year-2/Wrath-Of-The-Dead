#include "gameplay.h"
#include "collision.h"
#include "circle.h"
#include "gameover.h"
#include "fileparser.h"
#include <algorithm>

using std::cout;
using std::endl;

Gameplay::Gameplay(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	tileMap = new Tilemap(renderer);
	enemyManager = new EnemyManager(renderer);
	userInterface = new UserInterface(renderer);
	player = new Player(renderer, userInterface);
	gameOver = new GameOver(renderer, this);
	score = 0;
	calledOnce = true;

	fileParser = new TextFileParser<PlayerInfo>("scores.txt", [](std::vector<PlayerInfo*>& value) {
		sort(begin(value), end(value), [](PlayerInfo* one, PlayerInfo* two) -> bool {
			return one->GetScore() > two->GetScore();
			});
		}
	);
	items = fileParser->GetList();

	music.LoadMusic("backgroundMusic.wav");
	music.PlayMusic();

	chest = new Chest(renderer);
	coinPS = new CoinPS(renderer, chest->GetPosition());

	//	TODO: Circle colliison
	//Circle a = { 1,1,3 };
	//Circle b = { 5,5,3 };
	//if (Collision::CircleCollision(a, b))
	//	cout << "CUNT IT WORKED!" << "\n";
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
	delete gameOver;
	delete fileParser;
	delete chest;
	delete coinPS;
}

void Gameplay::Input() {
	if (player->Alive()) {
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
		player->Input(keyDown);
	}
	else { //	DEAD
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
		gameOver->Input(keyDown);
	}
}

void Gameplay::Update() {
	if (player->Alive()) {

		tileMap->Update();
		enemyManager->Update();
		player->Update();
		coinPS->Update();

		auto& bullets(player->GetBullets());
		auto& enemies(enemyManager->GetEnemies());
		auto& collTiles(tileMap->GetCollidableTiles());
		auto& coins(coinPS->GetParticles());

		for (auto& bullet : bullets)
			if (bullet->Active())
				for (auto& enemy : enemies)
					if (enemy->Active())
						if (Collision::ComplexCollision(bullet->GetCircleCollider(), enemy->GetCollider())) {
							bullet->Deactivate();
							if (enemy->TakeDamage(50)) {  // TRUE when enemy dies, false while alive.
								player->IncreaseScore(1);
							}
							return;
						}

		for (auto& tile : collTiles)
			if (tile->IsCollideable())
				if (Collision::BoxCollision(tile->GetCollider(), player->GetCollider()))
					player->Hit(15, *tile);
		if (!chest->IsOpen())
			if (Collision::BoxCollision(player->GetCollider(), chest->GetCollider())) {
				chest->OpenChest(coinPS);
				return;
			}

		for (auto& coin : coins)
			if (Collision::BoxCollision(player->GetCollider(), coin->GetCollider())) {
				player->IncreaseScore(5);
				coinPS->CoinCollected(coin);
				return;
			}
	}
	else {
		if (calledOnce) {

			items.push_back(new PlayerInfo(to_string(player->GetScore())));
			sort(begin(items), end(items), [](PlayerInfo* one, PlayerInfo* two) -> bool {
				return one->GetScore() > two->GetScore();
				});

			std::ofstream file("assets/files/scores.txt");
			if (file.is_open()) {
				file << items[0]->GetScore() << endl;
				file << items[1]->GetScore() << endl;
				file << items[2]->GetScore();
			}
			file.close();

			calledOnce = false;
		}
	}
}

void Gameplay::Draw() {
	SDL_RenderClear(renderer);

	tileMap->Draw();
	chest->Draw();
	player->Draw();
	enemyManager->Draw();
	userInterface->Draw();
	coinPS->Draw();

	if (!player->Alive()) {
		gameOver->Draw();
	}

	SDL_RenderPresent(renderer);
}

void Gameplay::SetMainMenu() {
	isRunning = false;
	game->SetMenuOptions(Game::Menu::mainmenu);
}