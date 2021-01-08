#include "bullet.h"
#include "player.h"

#define ANIM_TIMER 100
#define NO_OF_ANIMS 8

Bullet::Bullet(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer(renderer) {
	this->texture.Init(renderer, texture);
	this->texture.SetSrc(0, 0, 32, 32);
	this->texture.SetDst(0, 0, 32, 32);
	pos = { 0,0 };
	rotation = distance = 0;
	active = false;

	lastAnimaton = 0;
	currentAnim = 0;

	fireball.LoadSfx("fireball.wav");
}

void Bullet::Free()
{
}

void Bullet::Init(Vector2D<int>& pos, int angle, int distance)
{
	this->pos = pos;
	rotation = angle;
	this->distance = distance;
	active = true;
	texture.SetDst(pos.x, pos.y, 64, 64);
	texture.SetSrc(0, 0, 32, 32);

	//	Checks left/right
	rotation == 270 ? texture.SetFlip(SDL_FLIP_HORIZONTAL) : texture.SetFlip(SDL_FLIP_NONE);
	//	Check up/down
	rotation == 0 ? texture.SetDirection(270) : rotation == 180 ? texture.SetDirection(90) : texture.SetDirection(0);

	fireball.PlaySfx();

}

void Bullet::Update()
{
	if (!Active()) return;
	pos.x += sin(rotation * M_PI / 180.0f) * BULLET_SPEED;
	pos.y -= cos(rotation * M_PI / 180.0f) * BULLET_SPEED;
	texture.SetDst(pos);
	distance -= BULLET_SPEED;

	if (SDL_GetTicks() - lastAnimaton > ANIM_TIMER) {
		currentAnim > NO_OF_ANIMS ? currentAnim = 0 : currentAnim < 0 ? currentAnim = 0 : currentAnim++;

		for (short i = 0; i < NO_OF_ANIMS; i++)
		{
			if (currentAnim == i) {
				texture.SetSrc(32 * i, 0, 32, 32);
			}
		}

		lastAnimaton = SDL_GetTicks();
	}

	if (distance <= 0) active = false;
}

void Bullet::Draw()
{
	if (!Active()) return;
	texture.DrawEx();
}

//=============================

void BulletManager::Input(bool* keyDown) {
	if (keyDown[SDL_SCANCODE_SPACE]) {
		if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
			objPool->Create(player->GetPos(), player->GetAngle(), 1200);
			lastShot = SDL_GetTicks();
		}
	}
}




