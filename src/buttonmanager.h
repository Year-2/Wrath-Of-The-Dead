#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <array>
#include <vector>
#include <iostream>

#include "datatypes.h"

class ButtonManager;

//	TODO: Improve text renderer.
class Button {
public:
	Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect, const char* message, std::array<SDL_Rect, 9>* srcNine);
	~Button();
	void Free();

	void SetTextColor(SDL_Color color) { this->textColor = color; }
	void Draw();

private:
	SDL_Renderer* renderer;
	
	TTF_Font* font = nullptr;
	const char* message;
	SDL_Color textColor;
	SDL_Rect textPos;
	SDL_Rect buttonSize;

	Texture buttonImage;
	//Font buttonText; change texture color. have it centered
};

class ButtonManager {
public:
	ButtonManager(SDL_Renderer* renderer);
	~ButtonManager();
	void Free();

	void Draw();

	void AddButton(SDL_Rect rect, const char* message);
	void SetButtons();

	void MoveUp();
	void MoveDown();
	int Select();

private:
	SDL_Renderer* renderer;
	
	std::vector<Button*> buttons;
	std::array<SDL_Rect, 9>* srcNine;
	SDL_Texture* texture;

	SDL_Color white = { 211,191,169,255 };
	SDL_Color black = { 0, 0, 0, 255 };
	int noOfButtons;
	int currentIndex;
	int increment;
};
