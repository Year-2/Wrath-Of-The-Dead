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
class Enemy;

#define NUMBER_OF_ENEMIES 24

class EnemyManager {
public:
	EnemyManager(SDL_Renderer* renderer) {
		texture = TextureManager::LoadTexture(renderer, "enemy.png");
		objPool = new ObjectPool<Enemy>(renderer, texture, NUMBER_OF_ENEMIES);
	}

	~EnemyManager() {
		delete objPool;
	}

	void Update() {
		objPool->Update();
		ind++;
		if (ind >= 5) {
			objPool->Create();
			ind = 0;
		}
	}

	void Draw() {
		objPool->Draw();
	}

	ObjectPool<Enemy>* objPool;
	SDL_Texture* texture;
	int ind = 0;
};

class Enemy : public ObjectPoolBase {
public:
	Enemy() {};

	Enemy(SDL_Renderer* renderer, SDL_Texture* texture, int id) : renderer(renderer) {
		onScreen = false;
		src = { 0,0,32,32 };
		dst = { 0,0,32,32 };
		this->texture = new Texture();
		this->texture->Init(renderer, texture);
		xVel = yVel = 0;
		time = 0;
	}

	void Free() override {
		delete texture;
	}

	void Init() override {
		InitPosition();
		target = { 512, 288 };
		xVel = (target.x - position.x) / 300;
		yVel = (target.y - position.y) / 300;
		time = 300;

		src = { 0,0,32,32 };
		dst = { int(position.x),int(position.y),32,32 };
		onScreen = true;

		texture->SetDst(dst);
		texture->SetSrc(src);
		texture->SetFlip(SDL_FLIP_NONE);
		texture->SetDirection(GetDirection());

	}

	void Update() override {
		if (!Active()) return;
		position.x += xVel;
		position.y += yVel;
		dst.x = int(position.x);
		dst.y = int(position.y);
		texture->SetDst(dst);
		time--;
		//if ((dst.x > 1024 - dst.w) || (dst.x < 0)) {
		//	xVel = -xVel;
		//	texture->SetDirection(GetDirection());
		//}
		//if ((dst.y > 576 - dst.h) || (dst.y < 0)) {
		//	yVel = -yVel;
		//	texture->SetDirection(GetDirection());
		//}
		if (time <= 0) onScreen = false;
	}

	void Draw() override {
		if (!Active()) return;
		texture->DrawEx();
	}

	bool Active() const override {
		return onScreen;
	}

	void InitPosition() {
		float probability = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float coinFlip = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (probability < .64f) {
			if (coinFlip < .5f)
				position = { float(rand() % 1088) - 32.0f,  -32.0f };
			else
				position = { float(rand() % 1088) - 32.0f,  608 };

		}
		else {
			if (coinFlip < .5f)
				position = { -32.0f,  float(rand() % 640) - 32.0f };
			else
				position = { 1056,  float(rand() % 640) - 32.0f };

		}
	}

	int GetDirection() {
		/*return static_cast<int>(std::atan2f((dst.y + yVel) - dst.y,
			(dst.x + xVel) - dst.x) * 180.0f / M_PI) + 90.0f;*/
		return static_cast<int>(std::atan2f(target.y - position.y, target.x - position.x) * 180.0f / float(M_PI)) + 90.0f;
	}

	SDL_Renderer* renderer = nullptr;
	Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
	float xVel, yVel;
	int time;
	bool onScreen = false;
	Vector2D<float> position;
	Vector2D<float> target;
};
