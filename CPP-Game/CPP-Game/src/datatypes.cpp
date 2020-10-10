#include "datatypes.h"

Texture::Texture() {
	renderer = nullptr;
	texture = nullptr;
	src = { 0,0,0,0 };
	dst = { 0,0,0,0 };
}
void Texture::Init(SDL_Renderer* renderer, const char* path) {
	this->renderer = renderer;
	texture = TextureManager::LoadTexture(renderer, path);
	src = TextureManager::LoadTextureRect(path);
	dst = src;
}

Texture::~Texture() {
	Free();
}

void Texture::Free() {
	renderer = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
	src = { 0,0,0,0 };
	dst = { 0,0,0,0 };
}

void Texture::Draw() {
	TextureManager::Draw(renderer, texture, src, dst);
}

void Texture::DrawNine(std::array<SDL_Rect, 9>& src, std::array<SDL_Rect, 9>& dst) {
	TextureManager::DrawNine(renderer, texture, src, dst);
}

void Texture::SetSrc(int x, int y, int w, int h) {
	src = { x, y, w, h };
}

void Texture::SetDst(int x, int y, int w, int h) {
	dst = { x, y, w, h };
}

void Texture::PrintDst() {
	std::cout << dst.x << ", " << dst.y << ", " << dst.w << ", " << dst.h << std::endl;
}
void Texture::PrintSrc() {
	std::cout << src.x << ", " << src.y << ", " << src.w << ", " << src.h << std::endl;
}

Font::Font() {
	renderer = nullptr;
	font = nullptr;
	fontSize = 0;
	msg = "";
	fontRect = { 0,0,0,0 };
	xPos = 0;
	yPos = 0;
	color = { 255, 255, 255, 255 };
}

void Font::Init(SDL_Renderer* renderer, const char* filename, std::string msg, int size, int x, int y, SDL_Color color) {
	this->renderer = renderer;

	font = FontManager::LoadFont(filename, size);
	this->fontSize = size;
	this->msg = msg;
	fontRect = FontManager::FontRect(font, msg.c_str());
	xPos = x;
	yPos = y;
	this->color = color;

}

Font::~Font() {
	Free();
}

void Font::Free() {
	renderer = nullptr;
	TTF_CloseFont(font);
	font = nullptr;
	fontSize = 0;
	msg = "";
	fontRect = { 0,0,0,0 };
	xPos = yPos = 0;
	color = { 0,0,0,0 };
}

void Font::Draw() {
	FontManager::DrawFont(renderer, font, msg.c_str(), xPos, yPos, color);
}

void Font::SetMsg(std::string msg) {
	this->msg = msg;
}

void Font::PrintMsg() {
	std::cout << msg << std::endl;
}

void Font::SetPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void Font::PrintPosition() {
	std::cout << xPos << ", " << yPos << std::endl;
}

void Font::SetColor(SDL_Color color) {
	this->color = color;
}

void Font::PrintFontRect() {
	std::cout << fontRect.x << ", " << fontRect.y << " : " << fontRect.w << ", " << fontRect.h << std::endl;
}

Sound::Sound() {
	music = nullptr;
	sfx = nullptr;
}

Sound::~Sound() {
	Free();
}

void Sound::Free() {
	Mix_FreeChunk(sfx);
	sfx = nullptr;
	Mix_FreeMusic(music);
	music = nullptr;
}

void Sound::LoadMusic(const char* filepath) {
	music = SoundManager::LoadMusic(filepath);
}

void Sound::LoadSfx(const char* filepath) {
	sfx = SoundManager::LoadSFX(filepath);
}

void Sound::PlayMusic() {
	SoundManager::PlayMusic(music);
}

void Sound::PlaySfx() {
	SoundManager::PlaySFX(sfx);
}


