#include "buttonmanager.h"

Button::Button(SDL_Renderer* renderer, SDL_Rect& rect, const char* message, ButtonManager* buttonManager) {
	this->renderer = renderer;
	buttonTexture = TextureManager::LoadTexture(renderer, "test.png");
	buttonSrc = TextureManager::NineClipSrc(9, 48, 48);
	buttonDst = TextureManager::NineClipDst(rect.x, rect.y, rect.w, rect.h, 9);
	this->message = message;
	font = FontManager::LoadFont("test.ttf", 20);
	textPos = FontManager::FontRect(font, message);
	buttonSize = rect;
	buttonManager->AddButton(this);
}

Button::~Button() {
	Free();
}

void Button::Free() {
	renderer = nullptr;
	SDL_DestroyTexture(buttonTexture);
	buttonTexture = nullptr;
	TTF_CloseFont(font);
	font = nullptr;
	delete buttonSrc;
	buttonSrc = nullptr;
	delete buttonDst;
	buttonDst = nullptr;
	message = "";
	textPos = { 0,0,0,0 };
	buttonSize = { 0,0,0,0 };
	color = { 0,0,0,0 };
}

void Button::Draw() {
	TextureManager::DrawNine(renderer, buttonTexture, *buttonSrc, *buttonDst);
	FontManager::DrawFont(renderer, font, message, buttonDst->at(0).x + ((buttonSize.w / 2) - (textPos.w / 2)), buttonDst->at(0).y + ((buttonSize.h / 2) - (textPos.h / 3)), color);
}

// -----------------------------------------------------------

ButtonManager::ButtonManager(SDL_Renderer* renderer, int index) {
	this->renderer = renderer;
	currentIndex = index;
	increment = 0;
	noOfButtons = 0;
	std::memset(&buttons, NULL, sizeof(Button*));
}

ButtonManager::~ButtonManager() {
	Free();
}

void ButtonManager::Free() {
	renderer = nullptr;
	memset(&buttons, NULL, sizeof(buttons));
	white = { 0,0,0,0 };
	black = { 0,0,0,0 };
	noOfButtons = 0;
	currentIndex = 0;
	increment = 0;
}

void ButtonManager::AddButton(Button* button) {
	buttons[increment] = button;
	increment++;
}

void ButtonManager::SetButtons(int noOfButtons) {
	this->noOfButtons = noOfButtons;
	for (int i = 0; i < noOfButtons; i++)
	{
		buttons[i]->SetColor(black);
	}
	buttons[currentIndex]->SetColor(white);
}

void ButtonManager::MoveUp() {
	currentIndex--;
	if (currentIndex < 0) currentIndex = noOfButtons - 1;
	for (int i = 0; i < noOfButtons; i++)
	{
		buttons[i]->SetColor(black);
	}
	buttons[currentIndex]->SetColor(white);
}

void ButtonManager::MoveDown() {
	currentIndex++;
	if (currentIndex > noOfButtons - 1) currentIndex = 0;
	for (int i = 0; i < noOfButtons; i++)
	{
		buttons[i]->SetColor(black);
	}
	buttons[currentIndex]->SetColor(white);
}

int ButtonManager::Select() {
	return currentIndex;
}