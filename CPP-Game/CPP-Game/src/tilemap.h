#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <vector>
#include <iostream>

#include "texturemanager.h"
#include "fileparser.h"

#include "datatypes.h"

#define TILEMAP_WIDTH 32
#define TILEMAP_HEIGHT 18

#define TILE_SIZE 32

//TODO: Collidable tiles?
class Tile {
public:
	Tile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect srcData, SDL_Rect dstData);
	~Tile();

	SDL_Rect& GetCollider();

	void Animated();
	void Collideable();

	void Update();
	void Draw();

private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	SDL_Rect tileSrcData;
	SDL_Rect tileDstData;
	SDL_Rect storedSrc;

	bool animated;
	unsigned int lastAnimaton;
	int currentAnim;

	bool collideable;
	SDL_Rect collider;
	//Texture hitbox;
};

class Tilemap {
public:
	Tilemap(SDL_Renderer* renderer);
	~Tilemap();

	void CreateMap();

	void Update();
	void Draw();

	std::vector<Tile*>& GetCollidableTiles();

private:
	enum TileType {
		Grass,
		Dirt,
		Water,
		Stone
	};

	int MAP_DATA[TILEMAP_HEIGHT][TILEMAP_WIDTH];

	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	std::vector<Tile*> tiles;
	std::vector<Tile*> collidableTiles;
	std::vector<Tile*> animatedTiles;
};
