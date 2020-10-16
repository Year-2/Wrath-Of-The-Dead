#include "textureManager.h"

using std::cout;
using std::endl;
using std::string;

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* filename) {
	try {
		const char* dir = "assets/sprites/";
		SDL_Surface* surface = IMG_Load(string(string(dir) + string(filename)).c_str());
		if (surface == nullptr) throw TextureError();
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, surface);
		if (result == nullptr) throw TextureError();
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
	}
}

SDL_Rect TextureManager::LoadTextureRect(const char* filename) {
	try {
		const char* dir = "assets/sprites/";
		SDL_Surface* surface = IMG_Load(string(string(dir) + string(filename)).c_str());
		SDL_Rect result = { 0,0, surface->w, surface->h };
		if (surface == nullptr) throw TextureError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
	}
}

void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest) {
	SDL_RenderCopy(renderer, texture, &src, &dest);
}

std::array<SDL_Rect, 9>* TextureManager::NineClipSrc(int border, int width, int height) {
	std::array<SDL_Rect, 9>* borderClip = new std::array<SDL_Rect, 9>;
	borderClip->at(0) = { 0, 0, border, border };
	borderClip->at(1) = { border, 0, width - (2 * border), border };
	borderClip->at(2) = { width - border, 0, border, border };

	borderClip->at(3) = { 0, border, border, height - (2 * border) };
	borderClip->at(4) = { border,border, width - (2 * border),height - (2 * border) };
	borderClip->at(5) = { width - border, border, border, height - (2 * border) };

	borderClip->at(6) = { 0, height - border, border, border };
	borderClip->at(7) = { border, height - border, width - (2 * border), border };
	borderClip->at(8) = { width - border, height - border, border, border };

	return borderClip;
}

std::array<SDL_Rect, 9>* TextureManager::NineClipDst(int x, int y, int width, int height, int border) {
	std::array<SDL_Rect, 9>* borderPos = new std::array<SDL_Rect, 9>;

	borderPos->at(0) = { x,y,border,border };
	borderPos->at(1) = { x + border,y,width - (2 * border),border };
	borderPos->at(2) = { x + (width - border), y, border, border };

	borderPos->at(3) = { x, y + border, border, height - (2 * border) };
	borderPos->at(4) = { x + border, y + border, width - (2 * border), height - (2 * border) };
	borderPos->at(5) = { x + (width - border),y + border, border, height - (2 * border) };

	borderPos->at(6) = { x, y + (height - border), border, border };
	borderPos->at(7) = { x + border,y + (height - border), width - (2 * border),border };
	borderPos->at(8) = { x + (width - border), y + (height - border), border, border };

	return borderPos;
}

void TextureManager::DrawNine(SDL_Renderer* renderer, SDL_Texture* texture, std::array<SDL_Rect, 9>& src, std::array<SDL_Rect, 9>& dst) {
	for (int i = 0; i < 9; i++)
	{
		TextureManager::Draw(renderer, texture, src.at(i), dst.at(i));
	}
}