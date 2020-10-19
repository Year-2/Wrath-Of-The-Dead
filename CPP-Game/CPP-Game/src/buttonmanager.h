#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <array>
#include <vector>

#include "texturemanager.h"
#include "fontmanager.h"

class ButtonManager;

class Button {
public:

	Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect, const char* message);
	~Button();
	void Free();

	void SetColor(SDL_Color color) { this->color = color; }
	void Draw();

private:
	SDL_Renderer* renderer;
	SDL_Texture* buttonTexture = nullptr;
	TTF_Font* font = nullptr;
	std::array<SDL_Rect, 9>* buttonSrc;
	std::array<SDL_Rect, 9>* buttonDst;
	const char* message;
	SDL_Color color = { 154,217,65,255 };
	SDL_Rect textPos;
	SDL_Rect buttonSize;
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
	SDL_Texture* texture;
	SDL_Color white = { 255,255,255,255 };
	SDL_Color black = { 0, 0, 0, 255 };
	int noOfButtons;
	int currentIndex;
	int increment;
};
