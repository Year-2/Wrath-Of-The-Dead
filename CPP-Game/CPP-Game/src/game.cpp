#include "game.h"

using std::cout;
using std::endl;

Game::Game() {
	isRunning = true;
	renderer = nullptr;
	menuOptions = Menu::mainmenu;
}

Game::~Game() {
	Free();
}

void Game::Free() {
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

bool Game::Init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not be init! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
			std::cout << "Warning: Linear texture filterint not enabled!" << std::endl;
		}
		window = SDL_CreateWindow("CPP Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 1, 16, 76, 255);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_image could not init! SDL_image error: " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	if (TTF_Init() < 0) {
		std::cout << "SDL_TTF could not init! SDL_TTF error: " << TTF_GetError() << std::endl;
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mix could not init! SDL_Mix error: " << Mix_GetError() << std::endl;
		success = false;
	}
	return success;
}

void Game::Start() {
	while (isRunning) {
		switch (menuOptions)
		{
		case Menu::mainmenu:
		{
			cout << "Main Menu" << endl;
			totalTime = 0;
			currentTime = SDL_GetTicks();

			MainMenu mainMenu = MainMenu(this, renderer);
			while (mainMenu.isRunning) {

				newTime = SDL_GetTicks();
				frameTime = newTime - currentTime;
				currentTime = newTime;
				totalTime += frameTime;

				mainMenu.Input();
				if (totalTime >= UPDATE_STEP)
				{
					mainMenu.Update();
					totalTime -= UPDATE_STEP;

				}

				mainMenu.Draw();

			}
			break;
		}
		case Menu::gameplay:
		{
			cout << "GamePlay" << endl;
			totalTime = 0;
			currentTime = SDL_GetTicks();

			Gameplay gameplay = Gameplay(this, renderer);
			while (gameplay.isRunning) {

				newTime = SDL_GetTicks();
				frameTime = newTime - currentTime;
				currentTime = newTime;
				totalTime += frameTime;

				gameplay.Input();

				if (totalTime >= UPDATE_STEP)
				{
					gameplay.Update();
					totalTime -= UPDATE_STEP;
				}

				gameplay.Draw();
			}
			break;
		}
		case Menu::hiscores:
		{
			cout << "HiScores" << endl;
			totalTime = 0;
			currentTime = SDL_GetTicks();

			HiScores hiScores = HiScores(this, renderer);
			while (hiScores.isRunning) {

				newTime = SDL_GetTicks();
				frameTime = newTime - currentTime;
				currentTime = newTime;
				totalTime += frameTime;

				hiScores.Input();

				if (totalTime >= UPDATE_STEP)
				{
					hiScores.Update();
					totalTime -= UPDATE_STEP;
				}

				hiScores.Draw();
			}
			break;
		}
		default:
			break;
		}
	}
	Free();
}