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

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Start();
	void Free();

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

	const int WIDTH = 1024;
	const int HEIGHT = 576;

	SDL_Window* window = nullptr;
	Menu menuOptions;
	bool isRunning;
};