#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "texturemanager.h"
#include "objectpooler.h"
#include "vector2d.h"
#include "healthbar.h"
#include "pathfinding.h"

#define NUMBER_OF_ENEMIES 7
class Player;

class Enemy : public ObjectPoolBase {
public:
	Enemy(SDL_Renderer* renderer, SDL_Texture* texture, Player* player);
	~Enemy();
	void Free() override;
	void Init() override;
	void InitPosition();

	void Update() override;
	void Draw() override;

	bool Active() const override;
	void Deactivate() override;
	int GetDirection();

	void ChangeMovement();
	bool TakeDamage(int damageAmount);

	SDL_Rect& GetCollider() {
		return collider;
	}

private:
	SDL_Renderer* renderer = nullptr;
	Texture texture;
	SDL_Rect src;
	SDL_Rect dst;
	float xVel, yVel;
	int time;
	bool onScreen = false;

	Vector2D<float> position;
	Vector2D<float> target;

	HealthBar* healthBar;
	int health;

	unsigned int lastAnimaton;
	int currentAnim;

	SDL_Rect collider;
	//Texture hitbox;

	vector<Node> pathing;
	Vector2D<int> cachedPosition;

	Player* player;
};

class EnemyManager {
public:
	EnemyManager(SDL_Renderer* renderer, Player* player);
	~EnemyManager();

	void Update();
	void Draw();
	std::vector<Enemy*>& GetEnemies() {
		return objPool->GetObjects();
	}

private:
	ObjectPool<Enemy>* objPool;
	SDL_Texture* texture;
	int ind = 0;
};

//9,16

