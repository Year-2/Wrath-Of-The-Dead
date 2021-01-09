#pragma once

#include "vector2d.h"
#include "datatypes.h"
#include "bullet.h"
#define SPEED 4

class UserInterface;

class Player {
public:
	Player(SDL_Renderer* renderer, UserInterface* userInterface);
	~Player();

	void Input(bool* keyDown);
	void Update();
	void Draw();

	SDL_Rect& GetCollider();
	void Die();
	int& GetAngle() { return angle; }
	Vector2D<int>& GetPos() { return pos; }
	std::vector<Bullet*>& GetBullets() { return bulletManager->GetBullets(); }
	int GetScore() { return score; }

	void Hit(int damageAmount);
	void IncreaseScore(int scoreAmount);
	bool Alive();
	void Teleport();

private:
	SDL_Renderer* renderer;
	Vector2D<int> pos;
	Texture texture;
	int xVelocity, yVelocity;
	int angle;

	BulletManager* bulletManager;
	UserInterface* userInterface;

	int score;

	bool flip;
	unsigned int lastAnimaton;
	unsigned int lastTeleport;
	unsigned int lastWalkSound;
	unsigned int lastHurtSound;
	int currentAnim;
	bool xMoving, yMoving;

	int health;
	bool alive;

	Sound footsteps;
	Sound injury;
	Sound death;

	//Texture hitBox;
	SDL_Rect collider;

	enum FACING {
		LEFT = 270,
		RIGHT = 90,
		UP = 0,
		DOWN = 180
	};
};