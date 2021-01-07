#pragma once
#include "datatypes.h"

class UserInterface {
public:
	UserInterface(SDL_Renderer* renderer);

	void Draw();
	
	void Score(int score);
	void Health(int health);

	Texture healthTexture;
	Font healthTitleFont;
	Font healthFont;

	Texture scoreTexture;
	Font scoreTitleFont;
	Font scoreFont;
};