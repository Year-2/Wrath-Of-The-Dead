#include "fontManager.h"

using std::cout;
using std::endl;
using std::string;

/// <summary>
///		Try's to load a font, if it fails an exception is thrown.
/// </summary>
/// <param name="filename">
///		Font filename with extension. 
/// </param>
/// <param name="size">
///		Size of desired font.
/// </param>
/// <returns>
///		Font.
/// </returns>
TTF_Font* FontManager::LoadFont(const char* filename, int size) {
	try {
		const char* dir = "assets/fonts/";
		TTF_Font* result = TTF_OpenFont(string(string(dir) + string(filename)).c_str(), size);
		if (result == nullptr) throw FontError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
		return nullptr;
	}
}

/// <summary>
///		Draws font.
/// </summary>
/// <param name="renderer">
///		Renderer to draw the font.
/// </param>
/// <param name="font">
///		Font to be drawn. 
/// </param>
/// <param name="message">
///		Message for the font to display.
/// </param>
/// <param name="x">
///		X position of font.
/// </param>
/// <param name="y">
///		Y position of font.
/// </param>
/// <param name="color">
///		Colour of the font.
/// </param>
void FontManager::DrawFont(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y, SDL_Color& color) {
	try {
		SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect rect = { x, y, surface->w, surface->h };

		SDL_FreeSurface(surface);
		SDL_RenderCopy(renderer, texture, 0, &rect);
		SDL_DestroyTexture(texture);
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
	}
}

/// <summary>
///		Try's to load a font's destination rect.
/// </summary>
/// <param name="font">
///		Font to be used.
/// </param>
/// <param name="message">
///		Message to be used.
/// </param>
/// <returns>
///		Destination rect of message using font.
/// </returns>

SDL_Rect FontManager::FontRect(TTF_Font* font, const char* message) {
	try {
		SDL_Color color = { 154,217,65,255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		SDL_Rect result = { 0, 0, surface->w, surface->h };
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
		return { 0,0,0,0 };
	}
}

/// TEST

SDL_Texture* FontManager::FontTexture(SDL_Renderer* renderer, TTF_Font* font, const char* message, SDL_Color& color)
{
	try {
		SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
		return nullptr;
	}
}

SDL_Rect FontManager::FontRect(TTF_Font* font, const char* message, Vector2D<int>& pos) {
	try {
		SDL_Color color = { 154,217,65,255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
		if (surface == nullptr) throw FontError();
		SDL_Rect result = { pos.x, pos.y, surface->w, surface->h };
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
		return { 0,0,0,0 };
	}
}

void FontManager::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& dst) {
	SDL_RenderCopy(renderer, texture, 0, &dst);
}


