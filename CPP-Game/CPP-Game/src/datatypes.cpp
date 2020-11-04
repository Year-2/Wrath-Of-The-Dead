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
	delete nineSrc;
	delete nineDst;
}

/// <summary>
///		Draws texture.
/// </summary>
void Texture::Draw() {
	TextureManager::Draw(renderer, texture, src, dst);
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
void Texture::SetNine(int borderWidth, int width, int height) {
	nineSrc = TextureManager::NineClipSrc(borderWidth, width, height);
	nineDst = TextureManager::NineClipDst(dst.x, dst.y, dst.w, dst.h, borderWidth);
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

/// <summary>
///		Prints the destination clip.
/// </summary>
void Texture::PrintDst() {
	std::cout << dst.x << ", " << dst.y << ", " << dst.w << ", " << dst.h << std::endl;
}

/// <summary>
///		Prints the source clip.
/// </summary>
void Texture::PrintSrc() {
	std::cout << src.x << ", " << src.y << ", " << src.w << ", " << src.h << std::endl;
}

/////////////////////////////////////

/// <summary>
///		Initalises font to avoid garbage.
/// </summary>
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

/// <summary>
///		Initalises variables to be used.
/// </summary>
/// <param name="renderer">
///		Renderer to draw to.
/// </param>
/// <param name="filename">
///		Font filename with extension.
/// </param>
/// <param name="msg">
///		Message test to be drawn.
/// </param>
/// <param name="fontSize">
///		Font size.
/// </param>
/// <param name="x">
///		X Position.
/// </param>
/// <param name="y">
///		Y Position.
/// </param>
/// <param name="textColor">
///		Text color.
/// </param>
void Font::Init(SDL_Renderer* renderer, const char* filename, std::string msg,
	int fontSize, int x, int y, SDL_Color textColor) 
{
	this->renderer = renderer;
	this->fontSize = fontSize;
	this->msg = msg;
	this->color = textColor;
	font = FontManager::LoadFont(filename, fontSize);
	fontRect = FontManager::FontRect(font, msg.c_str());
	xPos = x;
	yPos = y;
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
	fontSize = 0;
	msg = "";
	xPos = yPos = 0;
	color = { 0,0,0,0 };
	fontRect = { 0,0,0,0 };
}

/// <summary>
///		Draws font.
/// </summary>
void Font::Draw() {
	FontManager::DrawFont(renderer, font, msg.c_str(), xPos, yPos, color);
}

/// <summary>
///		Sets the text.
/// </summary>
/// <param name="msg">
///		Text to save.
/// </param>
void Font::SetMsg(std::string msg) {
	this->msg = msg;
}

/// <summary>
///		Prints message.
/// </summary>
void Font::PrintMsg() {
	std::cout << msg << std::endl;
}

/// <summary>
///		Sets position.
/// </summary>
/// <param name="x">
///		X position.
/// </param>
/// <param name="y">
///		Y position.
/// </param>
void Font::SetPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

/// <summary>
///		Prints position.
/// </summary>
void Font::PrintPosition() {
	std::cout << xPos << ", " << yPos << std::endl;
}

/// <summary>
///		Sets colour.
/// </summary>
/// <param name="color">
///		Color to save.
/// </param>
void Font::SetColor(SDL_Color color) {
	this->color = color;
}

/// <summary>
///		Prints the fonts rectangle bounding box.
/// </summary>
void Font::PrintFontRect() {
	std::cout << fontRect.x << ", " << fontRect.y << " : " << fontRect.w << ", " << fontRect.h << std::endl;
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


