#include "healthpickup.h"

HealthBottle::HealthBottle(SDL_Renderer* renderer)
{
	bottle.Init(renderer, "healthPotion.png");
	bottle.SetSrc({ 0,0,16,16 });
	active = false;
	collider = { 0,0,0,0 };
}

void HealthBottle::Init(Vector2D<int> position)
{
	active = true;
	bottle.SetDst(position);
	collider = { position.x + 3,position.y + 4,10,11 };

}

void HealthBottle::Free()
{
}

void HealthBottle::Update()
{
}

void HealthBottle::Draw()
{
	if (!active) return;
	bottle.Draw();
}
bool HealthBottle::Active() const
{
	return active;
}

void HealthBottle::Deactivate()
{
	active = false;
}

SDL_Rect& HealthBottle::getCollider()
{
	return collider;
}

//===============================

PickUpManager::PickUpManager(SDL_Renderer* renderer) : renderer(renderer)
{
	objPool = new ObjectPool<HealthBottle>(15);
	objPool->Init(renderer);
}

PickUpManager::~PickUpManager() {
	delete objPool;
}

void PickUpManager::CreatePickup(Vector2D<int> position) {
	objPool->Create(position);
}

void PickUpManager::Draw()
{
	objPool->Draw();
}

std::vector<HealthBottle*>& PickUpManager::getPickups()
{
	return objPool->GetObjects();
}
