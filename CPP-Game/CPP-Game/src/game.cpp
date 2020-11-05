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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not be init! SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
			std::cout << "Warning: Linear texture filterint not enabled!" << "\n";
		}
		window = SDL_CreateWindow("Wrath Of The Dead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, APP_WIDTH_PX, APP_HEIGHT_PX, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			return false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
				return false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_image could not init! SDL_image error: " << IMG_GetError() << "\n";
					return false;
				}
			}
		}
	}
	if (TTF_Init() < 0) {
		std::cout << "SDL_TTF could not init! SDL_TTF error: " << TTF_GetError() << "\n";
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mix could not init! SDL_Mix error: " << Mix_GetError() << "\n";
		return false;
	}
	return true;
}

void Game::Start() {
	while (isRunning) {
		switch (menuOptions)
		{
		case Menu::mainmenu:
		{
			StartScene<MainMenu>();
			break;
		}
		case Menu::gameplay:
		{
			StartScene<Gameplay>();
			break;
		}
		case Menu::hiscores:
		{
			StartScene<HiScores>();
			break;
		}
		default:
			break;
		}
	}
	Free();
}


