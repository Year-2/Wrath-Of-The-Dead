#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "mainmenu.h"
#include "gameplay.h"
#include "hiscores.h"

//	MEMORY LEAK THINGY
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#define APP_WIDTH_PX 1024
#define APP_HEIGHT_PX 576

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Start();
	void Free();

	template <typename T>
	void StartScene();

	enum class Menu {
		mainmenu,
		gameplay,
		hiscores,
	};

	void SetMenuOptions(Menu item) { menuOptions = item; }
	void SetIsRunning(bool value) { isRunning = value; }

	SDL_Renderer* renderer;

private:
	const unsigned short UPDATE_STEP = 16;
	unsigned int totalTime = 0;
	unsigned int currentTime = 0;
	unsigned int newTime = 0;
	unsigned int frameTime = 0;

	SDL_Window* window = nullptr;
	Menu menuOptions;
	bool isRunning;
};

template <typename T>
void Game::StartScene() {
	totalTime = 0;
	currentTime = SDL_GetTicks();

	T scene = T(this, renderer);
	while (scene.isRunning) {
		newTime = SDL_GetTicks();
		frameTime = newTime - currentTime;
		currentTime = newTime;
		totalTime += frameTime;
		
		scene.Input();
		if (totalTime >= UPDATE_STEP)
		{
			scene.Update();
			totalTime -= UPDATE_STEP;
		}
		scene.Draw();
	}
}