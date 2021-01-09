#include "healthbar.h"

#define HB_WIDTH 40
#define HB_HEIGHT 10
#define BORDER_OFFSET 4

#define CENTER_X -4
#define CENTER_Y -11

HealthBar::HealthBar(SDL_Renderer* renderer, SDL_Rect& pos)
{
	bgSprite.Init(renderer, "healthbarBlack.png");
	bgSprite.SetSrc({ 0,0,75,10 });
	bgSprite.SetDst({ pos.x CENTER_X,pos.y CENTER_Y,HB_WIDTH,HB_HEIGHT });

	fgSprite.Init(renderer, "healthbarRed.png");
	fgSprite.SetSrc({ 0,0,75,10 });
	fgSprite.SetDst({ pos.x + (BORDER_OFFSET / 2) CENTER_X , pos.y + (BORDER_OFFSET / 2) CENTER_Y,HB_WIDTH - BORDER_OFFSET,HB_HEIGHT - BORDER_OFFSET });

	health = 100;
}

void HealthBar::Draw(SDL_Rect& pos)
{
	bgSprite.SetDst(pos.x CENTER_X, pos.y CENTER_Y, HB_WIDTH, HB_HEIGHT);
	bgSprite.Draw();

	fgSprite.SetDst(pos.x + (BORDER_OFFSET / 2) CENTER_X, pos.y + (BORDER_OFFSET / 2) CENTER_Y, (health / 100.0 * 40.0) - BORDER_OFFSET, HB_HEIGHT - BORDER_OFFSET);
	fgSprite.Draw();
}

//	TODO: Check input. healht/100*40, range 0,100
void HealthBar::ChangeHealth(int health) {
	this->health = health;
}
