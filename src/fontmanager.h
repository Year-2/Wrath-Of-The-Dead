#pragma once
#include <SDL_ttf.h>
#include <iostream>

#include "vector2d.h"

class FontManager {
public:
	static TTF_Font* LoadFont(const char* filename, int size);

	static SDL_Texture* FontTexture(SDL_Renderer* renderer, TTF_Font* font, const char* message, SDL_Color& color);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& dimensions);
	static void DrawFont(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y, SDL_Color& color);
	static SDL_Rect FontRect(TTF_Font* font, const char* message, Vector2D<int>& pos);
	static SDL_Rect FontRect(TTF_Font* font, const char* message);

	static inline std::string ProjectDirectory() {
		std::string projectDir = SDL_GetBasePath();
		std::string projectName = "Wrath-Of-The-Dead";
		auto deleteExcess = projectDir.find(projectName, 0) + projectName.size();
		projectDir.erase(begin(projectDir) + deleteExcess, end(projectDir));
		return projectDir;
	}
};

class FontError : public std::exception {
public:
	const char* what() const throw() { return "Font Error"; }
};
