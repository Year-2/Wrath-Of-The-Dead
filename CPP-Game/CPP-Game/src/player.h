#pragma once

#include "vector2d.h"
#include "datatypes.h"
#include "bullet.h"
#define SPEED 4

class Player {
public:
	Player(SDL_Renderer* renderer) : renderer(renderer) {
		pos = { 496,272 };
		texture.Init(renderer, "player.png");
		texture.SetSrc({ 0,0,32,32 });
		texture.SetDst(pos);
		xVelocity = yVelocity = 0;
		angle = 0;
		bulletManager = new BulletManager(renderer, this);
	}

	~Player() {
		delete bulletManager;
	}

	void Input(bool* keyDown) {
		if (keyDown[SDL_SCANCODE_LEFT]) {
			xVelocity = -SPEED;
			angle = 270;
		}
		else if (keyDown[SDL_SCANCODE_RIGHT]) {
			xVelocity = SPEED;
			angle = 90;
		}
		else {
			xVelocity = 0;
		}

		if (keyDown[SDL_SCANCODE_UP]) {
			yVelocity = -SPEED;
			angle = 0;
		}
		else if (keyDown[SDL_SCANCODE_DOWN]) {
			yVelocity = SPEED;
			angle = 180;
		}
		else {
			yVelocity = 0;
		}
		bulletManager->Input(keyDown);
	}


	void Update() {
		pos.x += xVelocity;
		pos.y += yVelocity;
		texture.SetDst(pos);
		bulletManager->Update();
	}

	void Draw() {
		texture.Draw();
		bulletManager->Draw();
	}

	Vector2D<int>& GetPos() { return pos; }
	int& GetAngle() { return angle; }

	std::vector<Bullet*>& GetBullets() {
		return bulletManager->GetBullets();
	}


private:
	SDL_Renderer* renderer;
	Vector2D<int> pos;
	Texture texture;
	int xVelocity, yVelocity;
	int angle;
	BulletManager* bulletManager;
};