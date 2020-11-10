#include "hiscores.h"

using std::cout;
using std::endl;

HiScores::HiScores(Game* game, SDL_Renderer* renderer) : Scene(game, renderer){
	background.Init(renderer, "greypanel.png");
	background.SetNineDst(322, 122, 380, 400, 5);
	background.SetNineSrc(5, 32, 32);

	title.Init(renderer, "test.ttf", 40, "HI-SCORES", Vector2D<int>(369, 71), { 255, 255, 255, 255 });
	titleBorder.Init(renderer, "bluepanel.png");
	titleBorder.SetNineDst(322, 54, 380, 100, 5);
	titleBorder.SetNineSrc(5, 32, 32);

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 382, 300, 100 }, "RETURN");
	buttonManager->SetButtons();
}

HiScores::~HiScores() {
	renderer = nullptr;
	game = nullptr;
	delete buttonManager;
}

void HiScores::Input() {
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
			if (e.key.keysym.sym == SDLK_RETURN) {
				if (buttonManager->Select() == 0) {
					isRunning = false;
					game->SetMenuOptions(Game::Menu::mainmenu);
				}
			}
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				keyDown[e.key.keysym.scancode] = false;
			}
		}
	}
}

void HiScores::Update() {

}

void HiScores::Draw() {
	SDL_RenderClear(renderer);

	titleBorder.DrawNine();
	background.DrawNine();
	title.Draw();

	buttonManager->Draw();

	SDL_RenderPresent(renderer);
}