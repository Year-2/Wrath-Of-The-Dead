#pragma once

#include "vector2d.h"
#include "datatypes.h"
#include "bullet.h"
#define SPEED 4

class Player {
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void Input(bool* keyDown);
	void Update();
	void Draw();

	int& GetAngle() { return angle; }
	Vector2D<int>& GetPos() { return pos; }
	std::vector<Bullet*>& GetBullets() { return bulletManager->GetBullets(); }

private:
	SDL_Renderer* renderer;
	Vector2D<int> pos;
	Texture texture;
	int xVelocity, yVelocity;
	int angle;
	BulletManager* bulletManager;
};