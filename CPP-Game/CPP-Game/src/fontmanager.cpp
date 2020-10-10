#include "fontManager.h"

using std::cout;
using std::endl;
using std::string;


TTF_Font* FontManager::LoadFont(const char* filename, int size) {
	try {
		const char* dir = "assets/fonts/";
		TTF_Font* result = TTF_OpenFont(string(string(dir) + string(filename)).c_str(), size);
		if (result == nullptr) throw FontError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
	}
}

void FontManager::DrawFont(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y, SDL_Color& color) {
	try {
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
		surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect rect = { x, y, surface->w, surface->h };

		SDL_FreeSurface(surface);
		SDL_RenderCopy(renderer, texture, 0, &rect);
		SDL_DestroyTexture(texture);
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
	}
}

SDL_Rect FontManager::FontRect(TTF_Font* font, const char* message) {
	try {
		SDL_Surface* surface = nullptr;
		SDL_Color color = { 154,217,65,255 };
		surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		SDL_Rect result = { 0, 0, surface->w, surface->h };
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
	}
}