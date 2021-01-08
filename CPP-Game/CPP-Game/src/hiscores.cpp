#include "hiscores.h"

using std::cout;
using std::endl;

HiScores::HiScores(Game* game, SDL_Renderer* renderer) : Scene(game, renderer) {
	background.Init(renderer, "beigePanel.png");
	background.SetNineDst(322, 122, 380, 400, 5);
	background.SetNineSrc(5, 32, 32);

	title.Init(renderer, "font.ttf", 40, "HI-SCORES", Vector2D<int>(369, 71), { 255, 255, 255, 255 });
	titleBorder.Init(renderer, "brownPanel.png");
	titleBorder.SetNineDst(322, 54, 380, 100, 5);
	titleBorder.SetNineSrc(5, 32, 32);

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 382, 300, 100 }, "RETURN");
	buttonManager->SetButtons();

	//Sorting player scores.
	fileParser = new TextFileParser<PlayerInfo>("scores.txt", [](std::vector<PlayerInfo*>& value) {
		sort(begin(value), end(value), [](PlayerInfo* one, PlayerInfo* two) -> bool {
			return one->GetScore() > two->GetScore();
			});
		}
	);

	std::vector<PlayerInfo*> items = fileParser->GetList();

	first.Init(renderer, "font.ttf", 32, "1", Vector2D<int>(420, 160), { 211,191,169,255 });
	first.BoundingBox({ 362, 382, 300, 100 });
	first.Message(to_string(items[0]->GetScore()).c_str());

	second.Init(renderer, "font.ttf", 32, "2", Vector2D<int>(420, 240), { 211,191,169,255 });
	second.BoundingBox({ 362, 382, 300, 100 });
	second.Message(to_string(items[1]->GetScore()).c_str());

	third.Init(renderer, "font.ttf", 32, "3", Vector2D<int>(420, 320), { 211,191,169,255 });
	third.BoundingBox({ 362, 382, 300, 100 });
	third.Message(to_string(items[2]->GetScore()).c_str());
}

HiScores::~HiScores() {
	renderer = nullptr;
	game = nullptr;
	delete buttonManager;
	delete fileParser;
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
	first.Draw();
	second.Draw();
	third.Draw();
	buttonManager->Draw();

	SDL_RenderPresent(renderer);
}