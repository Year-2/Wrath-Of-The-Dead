#include "hiscores.h"

using std::cout;
using std::endl;

HiScores::HiScores(Game* game, SDL_Renderer* renderer) : game(game), renderer(renderer){
	isRunning = true;
	std::memset(keyDown, false, sizeof(keyDown));

	background.Init(renderer, "greypanel.png");
	background.SetDst(322, 122, 380, 400);
	background.SetNine(5, 32, 32);

	title.Init(renderer, "test.ttf", "HI-SCORES", 40, 369, 71, white);
	titleBorder.Init(renderer, "bluepanel.png");
	titleBorder.SetDst(322, 54, 380, 100);
	titleBorder.SetNine(5, 32, 32);

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 382, 300, 100 }, "RETURN");
	buttonManager->SetButtons();
}

HiScores::~HiScores() {
	isRunning = false;
	std::memset(keyDown, false, sizeof(keyDown));
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