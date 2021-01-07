#include "datatypes.h"

/// <summary>
///		Initalises variables so there's no garbage.
/// </summary>
Texture::Texture() {
	renderer = nullptr;
	texture = nullptr;
	nineSrc = nullptr;
	nineDst = nullptr;
	src = { 0,0,0,0 };
	dst = { 0,0,0,0 };
	direction = 0;
	flip = SDL_FLIP_NONE;
	del = true;
}

/// <summary>
///		Initalises variables ready for use.
/// </summary>
/// <param name="renderer">
///		Rednerer to draw to.
/// </param>
/// <param name="filename">
///		Image filename with extension.
/// </param>
void Texture::Init(SDL_Renderer* renderer, const char* filename) {
	this->renderer = renderer;
	texture = TextureManager::LoadTexture(renderer, filename);
	src = TextureManager::LoadTextureRect(filename);
	dst = src;
}

void Texture::Init(SDL_Renderer* renderer, SDL_Texture* texture) {
	this->renderer = renderer;
	this->texture = texture;
}

/// <summary>
///		Frees memory on delete.
/// </summary>
Texture::~Texture() {
	Free();
}

/// <summary>
///		Cleans memory and dangling pointers.
/// </summary>
void Texture::Free() {
	renderer = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
	if(del)
		delete nineSrc;
	delete nineDst;
}

/// <summary>
///		Draws texture.
/// </summary>
void Texture::Draw() {
	TextureManager::Draw(renderer, texture, src, dst);
}

void Texture::DrawEx()
{
	TextureManager::DrawEx(renderer, texture, src, dst, direction, NULL, flip);
}

/// <summary>
///		Draws 9-scale texture.
/// </summary>
void Texture::DrawNine() {
	TextureManager::DrawNine(renderer, texture, *nineSrc, *nineDst);
}

/// <summary>
///		Saves the grid for 9-scaling.
/// </summary>
/// <param name="borderWidth">
///		Width of the border in px.
/// </param>
/// <param name="width">
///		Width of the image in px.
/// </param>
/// <param name="height">
///		Height of the image in px.
/// </param>
void Texture::SetNineSrc(int borderWidth, int width, int height) {
	nineSrc = TextureManager::NineClipSrc(borderWidth, width, height);
}

void Texture::SetNineDst(int x, int y, int width, int height, int border) {
	nineDst = TextureManager::NineClipDst(x, y, width, height, border);
}

void Texture::SetNineDst(SDL_Rect& dst, int border) {
	nineDst = TextureManager::NineClipDst(dst.x, dst.y, dst.w, dst.h, border);
}

/// <summary>
///		Sets the source clip.
/// </summary>
/// <param name="x">
///		X position.
/// </param>
/// <param name="y">
///		Y position.
/// </param>
/// <param name="width">
///		Width of clip.
/// </param>
/// <param name="height">
///		Height of clip.
/// </param>
void Texture::SetSrc(int x, int y, int width, int height) {
	src = { x, y, width, height };
}

/// <summary>
///		Sets the source clip.
/// </summary>
/// <param name="rect">
///		Source clip.
/// </param>
void Texture::SetSrc(const SDL_Rect& rect) {
	src = rect;
}

/// <summary>
///		Sets the dst clip.
/// </summary>
/// <param name="x">
///		X position.
/// </param>
/// <param name="y">
///		Y position.
/// </param>
/// <param name="width">
///		Width of clip.
/// </param>
/// <param name="height">
///		Height of clip.
/// </param>
void Texture::SetDst(int x, int y, int w, int h) {
	dst = { x, y, w, h };
}

void Texture::SetDst(const SDL_Rect& rect) {
	dst = rect;
}

void Texture::SetDst(const Vector2D<int>& pos) {
	dst.x = pos.x;
	dst.y = pos.y;
}

/// <summary>
///		Prints the destination clip.
/// </summary>
void Texture::PrintDst() {
	std::cout << "DST: " << dst.x << ", " << dst.y << ", " << dst.w << ", " << dst.h << "\n";
}

/// <summary>
///		Prints the source clip.
/// </summary>
void Texture::PrintSrc() {
	std::cout << "SRC: " << src.x << ", " << src.y << ", " << src.w << ", " << src.h << "\n";
}

/////////////////////////////////////

/// <summary>
///		Initalises font to avoid garbage.
/// </summary>
Font::Font() {
	renderer = nullptr;
	font = nullptr;
	color = { 255,255,255,255 };
	texture = nullptr;
	dimensions = { 0,0,0,0 };
	message = nullptr;
}

void Font::Init(SDL_Renderer* renderer, const char* filename, int size, const char* msg, Vector2D<int> pos, SDL_Color color)
{
	this->renderer = renderer;
	this->message = msg;
	font = FontManager::LoadFont(filename, size);
	this->color = color;
	this->pos = pos;
	texture = FontManager::FontTexture(renderer, font, msg, color);
	dimensions = FontManager::FontRect(font, msg, pos);
}

void Font::Draw() {
	SDL_RenderCopy(renderer, texture, 0, &dimensions);
}

void Font::Color(SDL_Color color) {
	SDL_DestroyTexture(texture);
	texture = FontManager::FontTexture(renderer, font, message, color);
}


/// <summary>
///		Frees memory on delete.
/// </summary>
Font::~Font() {
	Free();
}

/// <summary>
///		Cleans memory and dangling pointers.
/// </summary>
void Font::Free() {
	renderer = nullptr;
	TTF_CloseFont(font);
	font = nullptr;
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

/////////////////////////////////////

/// <summary>
///		Initalises sound to avoid garbage.
/// </summary>
Sound::Sound() {
	music = nullptr;
	sfx = nullptr;
}

/// <summary>
///		Free memory on delete. 
/// </summary>
Sound::~Sound() {
	Free();
}

/// <summary>
///		Cleans memory and dangling pointers.
/// </summary>
void Sound::Free() {
	Mix_FreeChunk(sfx);
	sfx = nullptr;
	Mix_FreeMusic(music);
	music = nullptr;
}

/// <summary>
///		Loads music.
/// </summary>
/// <param name="filepath">
///		Music filename including extension.
/// </param>
void Sound::LoadMusic(const char* filepath) {
	music = SoundManager::LoadMusic(filepath);
}

/// <summary>
///		Loads sfx.
/// </summary>
/// <param name="filepath">
///		SFX filename including extension.
/// </param>
void Sound::LoadSfx(const char* filepath) {
	sfx = SoundManager::LoadSFX(filepath);
}

/// <summary>
///		Plays music.
/// </summary>
void Sound::PlayMusic() {
	SoundManager::PlayMusic(music);
}

/// <summary>
///		Plays sound effect.
/// </summary>
void Sound::PlaySfx() {
	SoundManager::PlaySFX(sfx);
}


