#include "player.h"
#include "userinterface.h"

#define ANIM_TIMER 50
#define NO_OF_ANIMS 8

Player::Player(SDL_Renderer* renderer) : renderer(renderer) {
	health = 150;
	pos = { 496,272 };
	texture.Init(renderer, "player.png");
	texture.SetSrc({ 0,0,16,16 });
	texture.SetDst(pos.x, pos.y, 48, 48);
	xVelocity = yVelocity = 0;
	angle = 90;
	bulletManager = new BulletManager(renderer, this);
	flip = false;
	xMoving = false;
	yMoving = false;
	currentAnim = lastAnimaton = 0;
	alive = true;
}

Player::~Player() {
	delete bulletManager;
}

void Player::Input(bool* keyDown) {
	if (keyDown[SDL_SCANCODE_LEFT]) {
		xVelocity = -SPEED;
		angle = 270;
		flip = true;
		xMoving = true;
	}
	else if (keyDown[SDL_SCANCODE_RIGHT]) {
		xVelocity = SPEED;
		angle = 90;
		flip = false;
		xMoving = true;
	}
	else {
		xVelocity = 0;
		xMoving = false;
	}

	if (keyDown[SDL_SCANCODE_UP]) {
		yVelocity = -SPEED;
		angle = 0;
		yMoving = true;
	}
	else if (keyDown[SDL_SCANCODE_DOWN]) {
		yVelocity = SPEED;
		angle = 180;
		yMoving = true;
	}
	else {
		yVelocity = 0;
		yMoving = false;
	}
	bulletManager->Input(keyDown);
}

void Player::Update() {
	pos.x += xVelocity;
	pos.y += yVelocity;

	if (pos.x >= 975) {
		pos.x = 975;
	}
	else if (pos.x <= 0) {
		pos.x = 0;
	}

	if (pos.y >= 544 - 45) {
		pos.y = 544 - 45;
	}
	else if (pos.y <= 0) {
		pos.y = 0;
	}

	if (xMoving || yMoving) {
		if (SDL_GetTicks() - lastAnimaton > ANIM_TIMER) {
			currentAnim > NO_OF_ANIMS ? currentAnim = 0 : currentAnim < 0 ? currentAnim = 0 : currentAnim++;

			for (short i = 0; i < NO_OF_ANIMS; i++)
			{
				if (currentAnim == i) {
					texture.SetSrc(16 * i, 0, 16, 16);
				}
			}

			lastAnimaton = SDL_GetTicks();
		}
	}
	else {
		texture.SetSrc(48, 0, 16, 16);
	}

	texture.SetDst(pos);
	bulletManager->Update();
}

void Player::Draw() {
	flip ? texture.SetFlip(SDL_FLIP_HORIZONTAL) : texture.SetFlip(SDL_FLIP_NONE);
	bulletManager->Draw();
	texture.DrawEx();
}

SDL_Rect& Player::GetCollider() {
	return texture.GetDstRect();
}

void Player::Die() {
	alive = false;
}

void Player::Hit(UserInterface* ui, int damageAmount) {
	(health - damageAmount) < 0 ? Die() : health > 150 ? Die() : void(health-=damageAmount);
	ui->Health(health);
}

bool Player::Alive() {
	return alive;
}

