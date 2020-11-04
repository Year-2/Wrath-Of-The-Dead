#include "scene.h"
Scene::Scene(Game* game, SDL_Renderer* renderer) : game(game), renderer(renderer) {
	isRunning = true;
	std::memset(keyDown, false, sizeof(keyDown));
	white = { 255, 255, 255, 255 };
}

Scene::~Scene() {
	renderer = nullptr;
	game = nullptr;
	isRunning = false;
	std::memset(keyDown, false, sizeof(keyDown));
}