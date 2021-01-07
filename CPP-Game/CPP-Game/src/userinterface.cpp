#include "userinterface.h"

UserInterface::UserInterface(SDL_Renderer* renderer) {
	healthTexture.Init(renderer, "greypanel.png");
	healthTexture.SetNineSrc(5, 32, 32);
	healthTexture.SetNineDst(50, 50, 100, 50, 5);
	healthTitleFont.Init(renderer, "test.ttf", 16, "HEALTH:", Vector2D<int>(55, 55), { 211,191,169,255 });
	healthFont.Init(renderer, "test.ttf", 16, "150", Vector2D<int>(82, 75), { 211,191,169,255 });

	scoreTexture.Init(renderer, "greypanel.png");
	scoreTexture.SetNineSrc(5, 32, 32);
	scoreTexture.SetNineDst(850, 50, 100, 50, 5);
	scoreTitleFont.Init(renderer, "test.ttf", 16, "SCORE:", Vector2D<int>(861, 55), { 211,191,169,255 });
	scoreFont.Init(renderer, "test.ttf", 16, "0", Vector2D<int>(894, 75), { 211,191,169,255 });

	ammoTexture.Init(renderer, "greypanel.png");
	ammoTexture.SetNineSrc(5, 32, 32);
	ammoTexture.SetNineDst(850, 500, 100, 50, 5);
	ammoTitleFont.Init(renderer, "test.ttf", 16, "AMMO:", Vector2D<int>(868, 505), { 211,191,169,255 });
	ammoFont.Init(renderer, "test.ttf", 16, "10", Vector2D<int>(890, 525), { 211,191,169,255 });
}

void UserInterface::Score(int score) {
	scoreFont.Message(std::to_string(score).c_str());
}

void UserInterface::Health(int health) {
	healthFont.Message(std::to_string(health).c_str());
}


void UserInterface::Draw() {
	healthTexture.DrawNine();
	healthTitleFont.Draw();
	healthFont.Draw();

	scoreTexture.DrawNine();
	scoreTitleFont.Draw();
	scoreFont.Draw();

	ammoTexture.DrawNine();
	ammoTitleFont.Draw();
	ammoFont.Draw();
}
