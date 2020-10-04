#pragma once
#include <SDL_ttf.h>
#include <iostream>

#include "game.h"


class FontManager {
public:
	static TTF_Font* loadFont(const char* filename, int size);
	static void drawFont(TTF_Font* font, const char* message, int x, int y, SDL_Color& color);
	static SDL_Rect fontRect(TTF_Font* font, const char* message);
};

class FontError : public std::exception {
public:
	const char* what() const throw() { return "Font Error"; }
};
