#pragma once
#include "datatypes.h"
#include <vector>

#define ANIM_TIMER 150
#define NO_OF_ANIMS 4

class Coin {
public:
	Coin(SDL_Renderer* renderer, SDL_Texture* texture, Vector2D<int> pos) : renderer(renderer) {
		src = { 0,0,8,9 };
		dst = { pos.x + (rand() % 16),pos.y + (rand() % 16),16,16 };

		sprite.Init(renderer, texture);
		sprite.SetSrc(src);
		sprite.SetDst(dst);

		lastAnimation = 0;
		currentAnimation = rand() % 4;

		collider = dst;
	}

	~Coin() {

	}

	void Update() {
		//	TODO: Move coin here, simulate gravity?????

		if (SDL_GetTicks() - lastAnimation > ANIM_TIMER) {
			currentAnimation > NO_OF_ANIMS ? currentAnimation = 0 : currentAnimation < 0 ? currentAnimation = 0 : currentAnimation++;

			for (short i = 0; i < NO_OF_ANIMS; i++)
			{
				if (currentAnimation == i) {
					sprite.SetSrc(8 * i, 0, 8, 9);
				}
			}

			lastAnimation = SDL_GetTicks();
		}
	}

	void Draw() {
		//TextureManager::Draw(renderer, texture, src, dst);
		sprite.Draw();
	}

	SDL_Rect& GetCollider() { return collider; }

private:
	SDL_Renderer* renderer;
	Texture sprite;

	SDL_Rect src;
	SDL_Rect dst;

	SDL_Rect collider;
	unsigned int lastAnimation;
	short currentAnimation;

};

class CoinPS {
public:
	CoinPS(SDL_Renderer* renderer, Vector2D<int>& pos) : renderer(renderer), pos(pos) {
		coinTex = TextureManager::LoadTexture(renderer, "coin.png");
	}

	~CoinPS() {
		SDL_DestroyTexture(coinTex);
		coinTex = nullptr;
		for (auto& item : particles)
			delete item;
	}

	void Spawn() {
		for (int i = 0; i < 5; i++)
		{
			particles.push_back(new Coin(renderer, coinTex, pos));
		}
	}

	void Update() {
		for (auto& particle : particles)
			particle->Update();
	}

	void Draw() {
		for (auto& particle : particles)
			particle->Draw();
	}

	void CoinCollected(Coin* coin) {
		particles.erase(std::remove_if(begin(particles), end(particles), [coin](Coin* item) {
			return item == coin;
			}));
		std::cout << particles.size() << "\n";
	}

	std::vector<Coin*>& GetParticles() { return particles; }

private:
	SDL_Renderer* renderer;
	SDL_Texture* coinTex;
	Vector2D<int> pos;
	std::vector<Coin*> particles;

};

