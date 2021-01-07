#include "gameover.h"
#include "gameplay.h"

GameOver::GameOver(SDL_Renderer* renderer, Gameplay* gameplay)
{
	background.Init(renderer, "greypanel.png");
	background.SetNineSrc(5, 32, 32);
	background.SetNineDst(300, 100, 424, 376, 5);

	game.Init(renderer, "test.ttf", 50, "GAME", Vector2D<int>(420, 169), { 211,191,169,255 });
	over.Init(renderer, "test.ttf", 50, "OVER!", Vector2D<int>(412, 244), { 211,191,169,255 });

	buttonManager = new ButtonManager(renderer);
	buttonManager->AddButton({ 362, 330, 300, 100 }, "EXIT");
	buttonManager->SetButtons();

	gamePlay = gameplay;
}

GameOver::~GameOver()
{
	delete buttonManager;
}

void GameOver::Input(bool* keyDown) {
	if (keyDown[SDL_SCANCODE_RETURN]) {
		buttonManager->Select();
		gamePlay->SetMainMenu();
	}
}

void GameOver::Draw()
{
	background.DrawNine();
	game.Draw();
	over.Draw();
	buttonManager->Draw();
}
