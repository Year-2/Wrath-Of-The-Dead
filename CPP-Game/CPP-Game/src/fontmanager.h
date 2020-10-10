#pragma once
#include <SDL_ttf.h>
#include <iostream>

class FontManager {
public:
	static TTF_Font* LoadFont(const char* filename, int size);
	static void DrawFont(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y, SDL_Color& color);
	static SDL_Rect FontRect(TTF_Font* font, const char* message);
};

class FontError : public std::exception {
public:
	const char* what() const throw() { return "Font Error"; }
};
