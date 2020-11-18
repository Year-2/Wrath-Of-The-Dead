#include "enemy.h"

EnemyManager::EnemyManager(SDL_Renderer* renderer) {
	texture = TextureManager::LoadTexture(renderer, "enemy.png");
	objPool = new ObjectPool<Enemy>(NUMBER_OF_ENEMIES);
	objPool->Init(renderer, texture);
}

EnemyManager::~EnemyManager() {
	delete objPool;
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void EnemyManager::Update() {
	objPool->Update();
	ind++;
	if (ind >= 5) {
		objPool->Create();
		ind = 0;
	}
}

void EnemyManager::Draw() {
	objPool->Draw();
}

//====================================

Enemy::Enemy(SDL_Renderer* renderer, SDL_Texture* texture) : renderer(renderer) {
	onScreen = false;
	src = { 0,0,32,32 };
	dst = { 0,0,32,32 };
	this->texture.Init(renderer, texture);
	xVel = yVel = 0;
	time = 0;
}

void Enemy::Free(){
	// Nothing to clean yet.
}

void Enemy::Init(){
	InitPosition();
	target = { 512, 288 };
	xVel = (target.x - position.x) / 300;
	yVel = (target.y - position.y) / 300;
	time = 300;

	src = { 0,0,32,32 };
	dst = { int(position.x),int(position.y),32,32 };
	onScreen = true;

	texture.SetDst(dst);
	texture.SetSrc(src);
	texture.SetFlip(SDL_FLIP_NONE);
	texture.SetDirection(GetDirection());
}

void Enemy::Update() {
	if (!Active()) return;
	position.x += xVel;
	position.y += yVel;
	dst.x = int(position.x);
	dst.y = int(position.y);
	texture.SetDst(dst);
	time--;
	if (time <= 0) onScreen = false;
}

void Enemy::Draw(){
	if (!Active()) return;
	texture.DrawEx();
}

bool Enemy::Active() const{
	return onScreen;
}

void Enemy::Deactivate() {
	onScreen = false;
}

void Enemy::InitPosition() {
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

int Enemy::GetDirection() {
	return static_cast<int>(std::atan2f(target.y - position.y, target.x - position.x) * 180.0f / float(M_PI)) + 90.0f;
}