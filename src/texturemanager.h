#pragma once
#include <SDL_image.h>
#include <string>
#include <array>
#include <iostream>

class TextureManager {
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* filename);
	static SDL_Rect LoadTextureRect(const char* filename);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest);
	static void DrawEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst,
		int& direction, SDL_Point* center, const SDL_RendererFlip& flip);
	static void DrawNine(SDL_Renderer* renderer, SDL_Texture* texture, std::array<SDL_Rect, 9>& src, std::array<SDL_Rect, 9>& dst);
	static std::array<SDL_Rect, 9>* NineClipSrc(int b, int w, int h);
	static std::array<SDL_Rect, 9>* NineClipDst(int x, int y, int w, int h, int b);

	static inline std::string ProjectDirectory() {
		std::string projectDir = SDL_GetBasePath();
		std::string projectName = "Wrath-Of-The-Dead";
		auto deleteExcess = projectDir.find(projectName, 0) + projectName.size();
		projectDir.erase(begin(projectDir) + deleteExcess, end(projectDir));
		return projectDir;
	}
};

class TextureError : public std::exception {
public:
	const char* what() const throw() { return "Texture Error"; }
};