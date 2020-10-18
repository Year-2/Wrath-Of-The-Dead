#include "buttonmanager.h"

Button::Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect, const char* message) {
	this->renderer = renderer;
	buttonTexture = texture;
	buttonSrc = TextureManager::NineClipSrc(5, 49, 45);
	buttonDst = TextureManager::NineClipDst(rect.x, rect.y, rect.w, rect.h, 5);
	this->message = message;
	font = FontManager::LoadFont("test.ttf", 20);
	textPos = FontManager::FontRect(font, message);
	buttonSize = rect;
}

Button::~Button() {
	Free();
}

void Button::Free() {
	renderer = nullptr;
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

ButtonManager::ButtonManager(SDL_Renderer* renderer) {
	texture = TextureManager::LoadTexture(renderer, "button.png");
	this->renderer = renderer;
	currentIndex = 0;
	increment = 0;
	noOfButtons = 0;
}

ButtonManager::~ButtonManager() {
	Free();
}

void ButtonManager::Free() {
	renderer = nullptr;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Free();
		delete buttons[i];
	}
	SDL_DestroyTexture(texture);
	texture = nullptr;
	white = { 0,0,0,0 };
	black = { 0,0,0,0 };
	noOfButtons = 0;
	currentIndex = 0;
	increment = 0;
}

void ButtonManager::Draw() {
	for (auto& item : buttons)
		item->Draw();
}

void ButtonManager::AddButton(SDL_Rect rect, const char* message) {
	buttons.push_back(new Button(renderer, texture, rect, message));
}

void ButtonManager::SetButtons() {
	this->noOfButtons = buttons.size();
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->SetColor(black);
	buttons[currentIndex]->SetColor(white);
}

void ButtonManager::MoveUp() {
	currentIndex--;
	if (currentIndex < 0)
		currentIndex = noOfButtons - 1;
	for (int i = 0; i < noOfButtons; i++)
		buttons[i]->SetColor(black);
	buttons[currentIndex]->SetColor(white);
}

void ButtonManager::MoveDown() {
	currentIndex++;
	if (currentIndex > noOfButtons - 1)
		currentIndex = 0;
	for (int i = 0; i < noOfButtons; i++)
		buttons[i]->SetColor(black);
	buttons[currentIndex]->SetColor(white);
}

int ButtonManager::Select() {
	return currentIndex;
}