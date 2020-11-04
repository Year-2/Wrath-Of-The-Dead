#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>

class Game;

//// TODO: Texture and Font here too??
class Scene
{
public:
	Scene(Game* game, SDL_Renderer* renderer);
	~Scene();

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool isRunning;

	bool getKeyDown(int keyCode) {
		if (keyCode > 0 && keyCode < 512) {
			return keyDown[keyCode];
		}
		return false;
	}

protected:
	Game* game;
	SDL_Renderer* renderer;

	bool keyDown[512];
	SDL_Event e;
	SDL_Color white;
};
