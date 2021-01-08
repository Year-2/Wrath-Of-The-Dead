#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>

#include "datatypes.h"
#include "scene.h"

#include "tilemap.h"
#include "userinterface.h"
#include "enemy.h"
#include "game.h"
#include "player.h"

class Game;
class GameOver;

class Gameplay : public Scene {
public:

	Gameplay(Game* game, SDL_Renderer* renderer);
	~Gameplay();

	void Input() override;
	void Update() override;
	void Draw() override;

	void SetMainMenu();

private:
	Tilemap* tileMap;	
	EnemyManager* enemyManager;
	UserInterface* userInterface;
	Player* player;
	GameOver* gameOver;
	int score;
	bool calledOnce;
	TextFileParser<PlayerInfo>* fileParser;
	std::vector<PlayerInfo*> items;
	Sound music;
};
