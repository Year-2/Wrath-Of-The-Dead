#pragma once
#include "objectpooler.h"
#include "datatypes.h"
#include "vector2d.h"

#define NUMBER_OF_BULLETS 20
#define BULLET_SPEED 14
class Player;

class Bullet : public ObjectPoolBase {
public:
	Bullet(SDL_Renderer* renderer, SDL_Texture* texture);
	void Init(Vector2D<int>& pos, int angle, int distance);
	void Init() override {};

	void Free() override;

	bool Active() const override {
		return active;
	}

	void Deactivate() override{
		active = false;
	}

	void Update() override;
	void Draw() override;

	SDL_Rect& GetCollider() {
		return texture.GetDstRect();
	}

private:
	SDL_Renderer* renderer;
	Texture texture;
	Vector2D<int> pos;
	int rotation, distance;
	bool active;
};

class BulletManager {
public:
	BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {
		texture = TextureManager::LoadTexture(renderer, "bullet.png");
		objPool = new ObjectPool<Bullet>(NUMBER_OF_BULLETS);
		objPool->Init(renderer, texture);
	};

	~BulletManager() {
		delete objPool;
		SDL_DestroyTexture(texture);
	}

	void Input(bool* keyDown);

	void Update() {
		objPool->Update();
	}

	void Draw() {
		objPool->Draw();
	}

	std::vector<Bullet*>& GetBullets() {
		return objPool->GetObjects();
	}

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	ObjectPool<Bullet>* objPool;
	Player* player;

	const int SHOOT_TIMER_MS = 300;
	const int BULLET_VELOCITY = 10;
	unsigned int lastShot = 0;

};