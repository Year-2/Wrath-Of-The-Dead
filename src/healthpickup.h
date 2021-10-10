#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

#include "vector2d.h"
#include "datatypes.h"
#include "objectpooler.h"

class HealthBottle : public ObjectPoolBase{
public:
	HealthBottle(SDL_Renderer* renderer);

	void Init(Vector2D<int> position);
	void Free() override;

	void Update() override;
	void Draw() override;

	bool Active() const override;
	void Deactivate() override;

	SDL_Rect& getCollider();

private:
	Texture bottle;
	SDL_Rect collider;

	bool active;
};

class PickUpManager {
public:
	PickUpManager(SDL_Renderer* renderer);
	~PickUpManager();

	void CreatePickup(Vector2D<int> position);

	void Draw();

	std::vector<HealthBottle*>& getPickups();

private:
	SDL_Renderer* renderer;
	ObjectPool<HealthBottle>* objPool;
};
