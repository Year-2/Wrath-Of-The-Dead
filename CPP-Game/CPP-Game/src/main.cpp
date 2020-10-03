#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>

const int WIDTH = 1024;
const int HEIGHT = 576;
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;

bool init() {
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

int main(int argc, char* args[])
{
	if (!init()) {
		std::cout << "Error could not init!" << std::endl;
	}
	SDL_Delay(10000);

	return 0;
}