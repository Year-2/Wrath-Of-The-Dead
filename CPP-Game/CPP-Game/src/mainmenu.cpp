#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) : renderer(renderer), game(game) {
	isRunning = true;
	std::memset(keyDown, false, sizeof(keyDown));

	background.Init(renderer, "greypanel.png");
	background.SetDst(322, 122, 380, 400);
	background.SetNine(5, 32, 32);

	title.Init(renderer, "test.ttf", "MAIN MENU", 40, 369, 71, white);
	titleBorder.Init(renderer, "bluepanel.png");
	titleBorder.SetDst(322, 54, 380, 100);
	titleBorder.SetNine(5, 32, 32);

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 162, 300, 100 }, "PLAY");
	buttonManager->AddButton({ 362, 272, 300, 100 }, "HISCORES");
	buttonManager->AddButton({ 362, 382, 300, 100 }, "EXIT");
	buttonManager->SetButtons();
}

MainMenu::~MainMenu() {
	renderer = nullptr;
	game = nullptr;
	isRunning = false;
	std::memset(keyDown, false, sizeof(keyDown));
	delete buttonManager;
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
					isRunning = false;
					game->SetMenuOptions(Game::Menu::gameplay);
					break;
				}

				case 1:
				{
					isRunning = false;
					game->SetMenuOptions(Game::Menu::hiscores);
					break;
				}

				case 2:
				{
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

	titleBorder.DrawNine();
	title.Draw();
	background.DrawNine();
	buttonManager->Draw();

	SDL_RenderPresent(renderer);
}
