#include "textureManager.h"

using std::cout;
using std::endl;
using std::string;

/// <summary>
///		Try's to load the texture, if it fails an exception is thrown. 
/// </summary>
/// <param name="renderer">
///		Pointer to renderer which is used to create texture.
/// </param>
/// <param name="filename">
///		Image filename with extension.
/// </param>
/// <returns>
///		Texture.
/// </returns>
SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* filename) {
	try {
		string dir = projectDir + "/assets/sprites/";
		SDL_Surface* surface = IMG_Load((dir + string(filename)).c_str());
		if (surface == nullptr) throw TextureError();
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, surface);
		if (result == nullptr) throw TextureError();
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
		return nullptr;
	}
}

/// <summary>
///		Try's to load a texture an retrieve it's dimensions, if it fails an exception is thrown.
/// </summary>
/// <param name="filename">
///		Image filename with extension.
/// </param>
/// <returns>
///		Surface source rect.
/// </returns>
SDL_Rect TextureManager::LoadTextureRect(const char* filename) {
	try {
		string dir = projectDir + "/assets/sprites/";
		SDL_Surface* surface = IMG_Load((dir + string(filename)).c_str());
		SDL_Rect result = { 0,0, surface->w, surface->h };
		if (surface == nullptr) throw TextureError();
		SDL_FreeSurface(surface);
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << IMG_GetError();
		return { 0,0,0,0 };
	}
}

/// <summary>
///		Draws an image.
/// </summary>
/// <param name="renderer">
///		A pointer to the renderer to draw to.
/// </param>
/// <param name="texture">
///		Texture to draw.
/// </param>
/// <param name="src">
///		Source clip.
/// </param>
/// <param name="dest">
///		Destination clip.
/// </param>
void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* texture,
	const SDL_Rect& src, const SDL_Rect& dest) 
{
	SDL_RenderCopy(renderer, texture, &src, &dest);
}

void TextureManager::DrawEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst, int& direction, SDL_Point* center, const SDL_RendererFlip& flip)
{
	SDL_RenderCopyEx(renderer, texture, &src, &dst, direction, center, flip);
}

/// <summary>
///		Creates a 3x3 grid of src clips using an images dimensions. Sets the src dimensions 
///		for more accurate upscaling of small sprites.
///		-------------
///		|0|   1   |2|
///		-------------
///		| |       | |
///		|3|   4   |5|
///		| |       | |
///     -------------
///		|6|   7   |8|
///		------------- 
/// </summary>
/// <param name="border">
///		The border width of the image in px. (1,2,3,4,6,7,8,9)
/// </param>
/// <param name="width">
///		Width of the image in px.
/// </param>
/// <param name="height">
///		Height of the image in px.
/// </param>
/// <returns>
///		Array of src clips.
/// </returns>
std::array<SDL_Rect, 9>* TextureManager::NineClipSrc(int border, int width, int height) {
	std::array<SDL_Rect, 9>* borderClip = new std::array<SDL_Rect, 9>;
	memset(borderClip, 0, sizeof(*borderClip));

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

/// <summary>
///		Creates a 3x3 grid of dst clips with respect to how big you wish to upscale an image.
///		-------------
///		|0|   1   |2|
///		-------------
///		| |       | |
///		|3|   4   |5|
///		| |       | |
///     -------------
///		|6|   7   |8|
///		------------- 
/// </summary>
/// <param name="x">
///		X position of texture.
/// </param>
/// <param name="y">
///		Y position of texture.
/// </param>
/// <param name="width">
///		Width of desired texture.
/// </param>
/// <param name="height">
///		Height of desired texture.
/// </param>
/// <param name="border">
///		Border of source texture.
/// </param>
/// <returns>
///		Array of dst clips.
/// </returns>
std::array<SDL_Rect, 9>* TextureManager::NineClipDst(int x, int y, int width,
	int height, int border) 
{
	std::array<SDL_Rect, 9>* borderPos = new std::array<SDL_Rect, 9>;
	memset(borderPos, NULL, sizeof(borderPos));

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

/// <summary>
///		Draws a 9-scaled image. 
/// </summary>
/// <param name="renderer">
///		A pointer to the renderer to draw to.
/// </param>
/// <param name="texture">
///		Texture to draw.
/// </param>
/// <param name="src">
///		Array of source clips.
/// </param>
/// <param name="dest">
///		Array of destination clips.
/// </param>
void TextureManager::DrawNine(SDL_Renderer* renderer, SDL_Texture* texture,
	std::array<SDL_Rect, 9>& src, std::array<SDL_Rect, 9>& dst) 
{
	for (int i = 0; i < 9; i++)
	{
		TextureManager::Draw(renderer, texture, src.at(i), dst.at(i));
	}
}