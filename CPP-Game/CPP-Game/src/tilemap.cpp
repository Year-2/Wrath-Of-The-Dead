#include "tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer) : renderer(renderer) {
	SDL_Rect src = { 0, 0, 32, 32 };
	SDL_Rect dst = { 0, 0, 32, 32 };
	spritesheet = TextureManager::LoadTexture(renderer, "tiles.png");
	CreateMap();
}

Tilemap::~Tilemap() {
	SDL_DestroyTexture(spritesheet);
}

void Tilemap::CreateMap() {
	for (int y = 0; y < TILEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			SDL_Rect dst = { TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE, TILE_SIZE };
			SDL_Rect src = { (MAP_DATA[y][x] % 2) * 16, (MAP_DATA[y][x] / 2) * 16, 16, 16 };
			tiles.push_back(Tile(renderer, spritesheet, src, dst));
		}
	}
}

void Tilemap::Draw() {
	for (auto& t : tiles)
		t.Draw();
}

//////////////////////

Tile::Tile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect srcData, SDL_Rect dstData)
	: renderer(renderer), spritesheet(spritesheet), tileSrcData(srcData), tileDstData(dstData) {};

Tile::~Tile() {
	renderer = nullptr;
	spritesheet = nullptr;
}

void Tile::Draw() {
	TextureManager::Draw(renderer, spritesheet, tileSrcData, tileDstData);
}





