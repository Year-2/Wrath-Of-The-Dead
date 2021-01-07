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
#include "vector2d.h"

class Texture {
public:
	Texture();
	~Texture();

	void Init(SDL_Renderer* renderer, const char* path);
	void Init(SDL_Renderer* renderer, SDL_Texture* texture);
	void Free();

	void Draw();
	void DrawEx();
	void DrawNine();

	void SetSrc(int x, int y, int w, int h);
	void SetSrc(const SDL_Rect& rect);
	void SetDst(int x, int y, int w, int h);
	void SetDst(const SDL_Rect& rect);
	void SetDst(const Vector2D<int>& pos);

	void SetNineSrc(int b, int w, int h);
	void SetNineSrc(std::array<SDL_Rect, 9>* src) {
		nineSrc = src;
		del = false;
	}
	void SetNineDst(int x, int y, int width, int height, int border);
	void SetNineDst(SDL_Rect& dst, int border);

	void SetDirection(int dir) { direction = dir; }
	void SetFlip(SDL_RendererFlip flip) { this->flip = flip; }

	void PrintSrc();
	void PrintDst();

	void Print() {
		std::cout << renderer << ":R\n" << texture << ":T\n" << del << ":D\n";
	}

	SDL_Rect& GetDstRect() { return dst; }

private:
	bool del;
	SDL_Renderer* renderer;

	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
	int direction;
	SDL_RendererFlip flip;

	std::array<SDL_Rect, 9>* nineSrc;
	std::array<SDL_Rect, 9>* nineDst;
};

class Font {
public:
	Font();
	~Font();

	void Init(SDL_Renderer* renderer, const char* filename, int size, const char* msg, Vector2D<int> pos, SDL_Color color);
	void Free();

	void Color(SDL_Color color);
	void Draw();

	void Message(const char* msg) {
		message = msg;
		SDL_DestroyTexture(texture);
		texture = FontManager::FontTexture(renderer, font, message, color);

		dimensions = FontManager::FontRect(font, msg, pos);

		//	dimensions is dst.
		//	take in source rect get y 
		//	figure out x center.
	}

	void Print() {
		std::cout << "====================\n" <<
			"renderer: " << renderer << "\n" <<
			"message: " << message << "\n" <<
			"font: " << font << "\n" <<
			"color: " << color.r << ", " << color.g << ", " << color.b << "\n" <<
			"texture: " << texture << "\n" <<
			"dimensions: " << dimensions.x << ", " << dimensions.y << ", " << dimensions.w << ", " << dimensions.h << "\n";
	}

private:
	SDL_Renderer* renderer;

	TTF_Font* font;
	const char* message;
	SDL_Color color;
	SDL_Texture* texture;
	SDL_Rect dimensions;
	Vector2D<int> pos;
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

