#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

#include "texturemanager.h"
#include "fontmanager.h"
#include "soundmanager.h"

class Texture {
public:
	Texture();
	~Texture();

	void Init(SDL_Renderer* renderer, const char* path);
	void Free();
	
	void Draw();
	void DrawNine(std::array<SDL_Rect, 9>& src, std::array<SDL_Rect, 9>& dst);

	void SetSrc(int x, int y, int w, int h);
	void SetSrc(const SDL_Rect& rect);
	void SetDst(int x, int y, int w, int h);

	void PrintSrc();
	void PrintDst();

private:
	SDL_Renderer* renderer;

	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
};

class Font {
public:
	Font();
	~Font();

	void Init(SDL_Renderer* renderer, const char* filename, std::string msg, int size, int x, int y, SDL_Color color);
	void Free();

	void Draw();

	void SetMsg(std::string msg);
	void SetPosition(int x, int y);
	void SetColor(SDL_Color color);
	
	void PrintMsg();
	void PrintPosition();
	void PrintFontRect();

private:
	SDL_Renderer* renderer;

	TTF_Font* font;
	int fontSize;
	std::string msg;
	int xPos, yPos;
	SDL_Color color;
	SDL_Rect fontRect;
};

class Sound {
public:
	Sound();
	~Sound();
	
	void Free();

	void LoadMusic(const char* filepath);
	void LoadSfx(const char* filepath);

	void PlayMusic();
	void PlaySfx();

private:
	Mix_Music* music;
	Mix_Chunk* sfx;
};

