#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->game = game;
	isRunning = true;
	std::memset(keyDown, false, sizeof(keyDown));

	background.Init(renderer, "test.png");
	background.SetDst(262, 26, 500, 100);
	title.Init(renderer, "test.ttf", "MAIN MENU", 40, 369, 59, white);

	buttonManager = new ButtonManager(renderer);

	playDst = { 352, 150, 300, 100 };
	play = new Button(renderer, playDst, "PLAY", buttonManager);

	hiscoresDst = { 352, 260, 300, 100 };
	hiscores = new Button(renderer, hiscoresDst, "HISCORES", buttonManager);

	exitDst = { 352, 370, 300, 100 };
	exit = new Button(renderer, exitDst, "EXIT", buttonManager);

	buttonManager->SetButtons(3);
}

MainMenu::~MainMenu() {
	renderer = nullptr;
	game = nullptr;
	isRunning = false;
	std::memset(keyDown, false, sizeof(keyDown));
	white = { 0,0,0,0 };
	playDst = { 0,0,0,0 };
	hiscoresDst = { 0,0,0,0 };
	exitDst = { 0,0,0,0 };
	delete buttonManager;
	buttonManager = nullptr;
	delete play;
	play = nullptr;
	delete hiscores;
	hiscores = nullptr;
	delete exit;
	exit = nullptr;

	background.Free();
	title.Free();
	music.Free();
}

void MainMenu::Input() {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
			game->SetIsRunning(false);
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = true;
			}
			if (e.key.keysym.sym == SDLK_UP) buttonManager->MoveUp();
			if (e.key.keysym.sym == SDLK_DOWN) buttonManager->MoveDown();
			if (e.key.keysym.sym == SDLK_RETURN) {
				switch (buttonManager->Select())
				{
				case 0:
				{
					std::cout << "Play" << std::endl;
					isRunning = false;
					game->SetMenuOptions(Game::Menu::gameplay);
					break;
				}

				case 1:
				{
					std::cout << "Hiscores" << std::endl;
					isRunning = false;
					game->SetMenuOptions(Game::Menu::hiscores);
					break;
				}

				case 2:
				{
					std::cout << "Exit" << std::endl;
					isRunning = false;
					game->SetIsRunning(false);
					break;
				}
				default:
					break;
				}
			}

			else if (e.type == SDL_KEYUP) {
				if (e.key.keysym.scancode < 512) {
					keyDown[e.key.keysym.scancode] = false;
				}
			}
		}
	}
}

void MainMenu::Update() {
}

void MainMenu::Draw() {
	SDL_RenderClear(renderer);

	background.Draw();
	title.Draw();

	play->Draw();
	hiscores->Draw();
	exit->Draw();

	SDL_RenderPresent(renderer);
}
