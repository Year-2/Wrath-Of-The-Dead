#include "tilemap.h"


Tilemap::Tilemap(SDL_Renderer* renderer) : renderer(renderer) {
	SDL_Rect src = { 0, 0, 32, 32 };
	SDL_Rect dst = { 0, 0, 32, 32 };
	spritesheet = TextureManager::LoadTexture(renderer, "tiles.png");
	CreateMap();
}

Tilemap::~Tilemap() {
	SDL_DestroyTexture(spritesheet);
	spritesheet = nullptr;
	renderer = nullptr;
}

void Tilemap::CreateMap() {
	for (int y = 0; y < TILEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			SDL_Rect dst = { TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE, TILE_SIZE };
			switch (MAP_DATA[y][x]) {
				case Grass:
					tiles.push_back(GrassTile(renderer, spritesheet, dst));
					break;
				case Dirt:
					tiles.push_back(DirtTile(renderer, spritesheet, dst));
					break;
				case Water:
					tiles.push_back(WaterTile(renderer, spritesheet, dst));
					break;
				case Stone:
					tiles.push_back(StoneTile(renderer, spritesheet, dst));
					break;
				default:
					std::cout << "Create map fell threw" << "\n";
					break;
			}
		}
	}
}

void Tilemap::Draw() {
	for (auto& t : tiles)
		t.Draw();
}

//////////////////////

Tile::Tile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect dstData)
	: renderer(renderer), tileDstData(dstData), spritesheet(spritesheet)
{
	tileSrcData = { 0,0,0,0 };
}

Tile::~Tile() {
	renderer = nullptr;
	spritesheet = nullptr;
}

void Tile::Draw() {
	TextureManager::Draw(renderer, spritesheet, tileSrcData, tileDstData);
}

///////////////////////

GrassTile::GrassTile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect dstData)
	: Tile(renderer, spritesheet, dstData)
{
	tileSrcData = { 16,16,16,16 };
}

DirtTile::DirtTile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect dstData)
	: Tile(renderer, spritesheet, dstData)
{
	tileSrcData = { 0,0,16,16 };
}

WaterTile::WaterTile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect dstData)
	: Tile(renderer, spritesheet, dstData)
{
	tileSrcData = { 16,0,16,16 };
}

StoneTile::StoneTile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect dstData)
	: Tile(renderer, spritesheet, dstData)
{
	tileSrcData = { 0,16,16,16 };
}





