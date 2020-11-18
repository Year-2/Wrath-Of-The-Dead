#include "bullet.h"
#include "player.h"

Bullet::Bullet(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer(renderer) {
	this->texture.Init(renderer, texture);
	this->texture.SetSrc(0, 0, 32, 32);
	this->texture.SetDst(0, 0, 32, 32);
	pos = { 0,0 };
	rotation = distance = 0;
	active = false;
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
	texture.SetDst(pos.x, pos.y, 32, 32);
	texture.SetSrc(0, 0, 32, 32);
}

void Bullet::Update()
{
	if (!Active()) return;
	pos.x += sin(rotation * M_PI / 180.0f) * BULLET_SPEED;
	pos.y -= cos(rotation * M_PI / 180.0f) * BULLET_SPEED;
	texture.SetDst(pos);
	distance -= BULLET_SPEED;
	if (distance <= 0) active = false;
}

void Bullet::Draw()
{
	if (!Active()) return;
	texture.Draw();
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




