#include "player.h"
#include "userinterface.h"

#define ANIM_TIMER 50
#define TELEPORT_TIMER 1000
#define WALK_SOUND 300
#define INJURY_SOUND 300
#define NO_OF_ANIMS 8

Player::Player(SDL_Renderer* renderer, UserInterface* userInterface) : renderer(renderer), userInterface(userInterface) {
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
	currentAnim = lastAnimaton = lastWalkSound = 0;
	lastHurtSound = 301;
	alive = true;

	footsteps.LoadSfx("footsteps.wav");
	injury.LoadSfx("injury.wav");
	death.LoadSfx("death.wav");

	//hitBox.Init(renderer, "healthbarBlack.png");
	//hitBox.SetDst(pos.x + 3, pos.y + 9, 39, 36);
	collider = { pos.x + 3, pos.y + 9, 39, 36 };

	score = 0;
}

Player::~Player() {
	delete bulletManager;
}

void Player::Input(bool* keyDown) {
	if (keyDown[SDL_SCANCODE_LEFT]) {
		xVelocity = -SPEED;
		angle = LEFT;
		flip = true;
		xMoving = true;
	}
	else if (keyDown[SDL_SCANCODE_RIGHT]) {
		xVelocity = SPEED;
		angle = RIGHT;
		flip = false;
		xMoving = true;
	}
	else {
		xVelocity = 0;
		xMoving = false;
	}

	if (keyDown[SDL_SCANCODE_UP]) {
		yVelocity = -SPEED;
		angle = UP;
		yMoving = true;
	}
	else if (keyDown[SDL_SCANCODE_DOWN]) {
		yVelocity = SPEED;
		angle = DOWN;
		yMoving = true;
	}
	else {
		yVelocity = 0;
		yMoving = false;
	}

	if (keyDown[SDL_SCANCODE_B]) {
		if (SDL_GetTicks() - lastTeleport > TELEPORT_TIMER) {

			Teleport();
			lastTeleport = SDL_GetTicks();
		}
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

	if (pos.y >= 499) {
		pos.y = 499;
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

		if (SDL_GetTicks() - lastWalkSound > WALK_SOUND) {

			footsteps.PlaySfx();
			lastWalkSound = SDL_GetTicks();
		}
	}
	else {
		texture.SetSrc(48, 0, 16, 16);
	}

	texture.SetDst(pos);
	collider = { pos.x + 3, pos.y + 9, 39, 36 };
	//hitBox.SetDst(pos.x + 3, pos.y + 9, 39, 36);
	bulletManager->Update();
	std::cout << score << std::endl;
}

void Player::Draw() {
	flip ? texture.SetFlip(SDL_FLIP_HORIZONTAL) : texture.SetFlip(SDL_FLIP_NONE);
	bulletManager->Draw();
	texture.DrawEx();
	//hitBox.Draw();
}

SDL_Rect& Player::GetCollider() {
	return collider;
}

void Player::Die() {
	death.PlaySfx();
	alive = false;
}

void Player::Hit(int damageAmount) {
	(health - damageAmount) < 0 ? Die() : health > 150 ? Die() : void(health -= damageAmount);
	userInterface->Health(health);

	if (SDL_GetTicks() - lastHurtSound > INJURY_SOUND) {

		injury.PlaySfx();
		lastHurtSound = SDL_GetTicks();
	}
}

void Player::IncreaseScore(int scoreAmount)
{
	score += abs(scoreAmount);
	userInterface->Score(score);
}

bool Player::Alive() {
	return alive;
}

//	PLayer handle score not gameplay loop.
void Player::Teleport()
{
	if (score - 5 <= 0)
		return;
	score -= 5;
	userInterface->Score(score);
	//	 6 Tiles
	int teleportDistance = 6 * 32;

	switch (angle)
	{
		case UP:
			std::cout << pos.y << std::endl;
			(pos.y - teleportDistance) <= 0 ? pos.y = 0 : pos.y -= teleportDistance;
			break;
		case DOWN:
			(pos.y + teleportDistance) >= 499 ? pos.y = 499 : pos.y += teleportDistance;
			break;
		case LEFT:
			(pos.x - teleportDistance) <= 0 ? pos.x = 0 : pos.x -= teleportDistance;
			break;
		case RIGHT:
			(pos.x + teleportDistance) >= 975 ? pos.x = 975 : pos.x += teleportDistance;
			break;

		default:
			std::cout << "TELEPORTING BROKE!" << std::endl;
			break;
	}

}

