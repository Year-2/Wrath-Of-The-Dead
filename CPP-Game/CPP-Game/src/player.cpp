#include "player.h"

Player::Player(SDL_Renderer* renderer) : renderer(renderer) {
	pos = { 496,272 };
	texture.Init(renderer, "player.png");
	texture.SetSrc({ 0,0,32,32 });
	texture.SetDst(pos);
	xVelocity = yVelocity = 0;
	angle = 0;
	bulletManager = new BulletManager(renderer, this);
}

Player::~Player() {
	delete bulletManager;
}

void Player::Input(bool* keyDown) {
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

void Player::Update() {
	pos.x += xVelocity;
	pos.y += yVelocity;

	if (pos.x >= 990) {
		pos.x = 992;
	}
	else if (pos.x <= 0) {
		pos.x = 0;
	}

	if (pos.y >= 544) {
		pos.y = 544;
	}
	else if (pos.y <= 0) {
		pos.y = 0;
	}

	texture.SetDst(pos);
	bulletManager->Update();
}

void Player::Draw() {
	texture.Draw();
	bulletManager->Draw();
}


