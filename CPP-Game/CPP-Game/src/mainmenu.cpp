#include "mainmenu.h"

using std::cout;
using std::endl;

MainMenu::MainMenu(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	background.Init(renderer, "greypanel.png");
	background.SetNineDst(322, 122, 380, 400, 5);
	background.SetNineSrc(5, 32, 32);

	title.Init(renderer, "test.ttf", 40, "MAIN MENU", Vector2D<int>(369, 71), { 255, 255, 255, 255 });
	titleBorder.Init(renderer, "bluepanel.png");
	titleBorder.SetNineDst(322, 54, 380, 100, 5);
	titleBorder.SetNineSrc(5, 32, 32);

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 162, 300, 100 }, "PLAY");
	buttonManager->AddButton({ 362, 272, 300, 100 }, "HISCORES");
	buttonManager->AddButton({ 362, 382, 300, 100 }, "EXIT");
	buttonManager->SetButtons();
}

MainMenu::~MainMenu() {
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
