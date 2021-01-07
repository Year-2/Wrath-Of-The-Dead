#include "tilemap.h"
#define ANIM_TIMER 200
#define NO_OF_ANIMS 3

Tilemap::Tilemap(SDL_Renderer* renderer) : renderer(renderer) {
	spritesheet = TextureManager::LoadTexture(renderer, "tilemap.png");

	//BinaryFileParser().GenerateTilemapFile("tilemap2.bin");

	int index = 0;
	int* arr = BinaryFileParser().ReadFile("tilemap2.bin", 576);
	for (int y = 0; y < TILEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			MAP_DATA[y][x] = arr[index];
			index++;
		}
	}
	delete[] arr;

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
			//	Tile
			SDL_Rect dst = { TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE, TILE_SIZE };
			SDL_Rect src = { (MAP_DATA[y][x] % 6) * 16, (MAP_DATA[y][x] / 6) * 16, 16, 16 };
			tiles.push_back(new Tile(renderer, spritesheet, src, dst));

			//	Collision
			if (MAP_DATA[y][x] == 27) {
				tiles.at((y * TILEMAP_WIDTH) + x)->Collideable();
				collidableTiles.push_back(tiles[(y * TILEMAP_WIDTH) + x]);
			}

			//	Animation
			for (short tileID = 6; tileID < 18; tileID++)
			{
				if (MAP_DATA[y][x] == tileID) {
					tiles.at((y * TILEMAP_WIDTH) + x)->Animated();
					animatedTiles.push_back(tiles[(y * TILEMAP_WIDTH) + x]);
				}
			}
		}
	}
}

void Tilemap::Update() {
	for (auto& tile : animatedTiles) {
		tile->Update();
	}
}

void Tilemap::Draw() {
	for (auto& tile : tiles) {
		tile->Draw();
	}
}

std::vector<Tile*>& Tilemap::GetCollidableTiles() {
	return collidableTiles;
}

//////////////////////

Tile::Tile(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Rect srcData, SDL_Rect dstData)
	: renderer(renderer), spritesheet(spritesheet), tileDstData(dstData) {
	animated = false;
	collideable = false;
	tileSrcData = srcData;
	storedSrc = srcData;
	currentAnim = 0;
	lastAnimaton = 0;
};

Tile::~Tile() {
	renderer = nullptr;
	spritesheet = nullptr;
}

SDL_Rect& Tile::GetCollider() {
	return tileDstData;
}

void Tile::Animated()
{
	animated = true;
}

void Tile::Collideable()
{
	collideable = true;
}

void Tile::Update() {
	if (animated) {
		
		if (SDL_GetTicks() - lastAnimaton > ANIM_TIMER) {
			currentAnim > NO_OF_ANIMS ? currentAnim = 0 : currentAnim < 0 ? currentAnim = 0 : currentAnim++;

			for (short i = 0; i < NO_OF_ANIMS; i++)
			{
				if (currentAnim == i) {
					tileSrcData.x = storedSrc.x + (i * 16);
				}
			}

			lastAnimaton = SDL_GetTicks();
		}
	}
}

void Tile::Draw() {
	TextureManager::Draw(renderer, spritesheet, tileSrcData, tileDstData);
}





