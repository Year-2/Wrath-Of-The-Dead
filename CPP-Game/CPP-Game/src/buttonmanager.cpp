#include "buttonmanager.h"

/// <summary>
///		Creates a button by loading a texture and font. Sets the size and position.
/// </summary>
/// <param name="renderer">
///		Points to the renderer to draw to.
/// </param>
/// <param name="texture">
///		Texture to be drawn.
/// </param>
/// <param name="dst">
///		Button destination on-screen.
/// </param>
/// <param name="message">
///		Text overlayed onto button.
/// </param>
Button::Button(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& dst,
	const char* message, std::array<SDL_Rect, 9>* srcNine) : renderer(renderer), message(message), buttonSrc(srcNine)
{
	buttonTexture = texture;
	buttonDst = TextureManager::NineClipDst(dst.x, dst.y, dst.w, dst.h, 5);
	font = FontManager::LoadFont("test.ttf", 20);
	textPos = FontManager::FontRect(font, message);
	buttonSize = dst;
	textColor = { 0,0,0,0 };
}

/// <summary>
///		Free's memory on delete.
/// </summary>
Button::~Button() {
	Free();
}

/// <summary>
///		Cleans the object's memory. Cleans any dangling pointers.
/// </summary>
void Button::Free() {
	renderer = nullptr;
	buttonTexture = nullptr;
	TTF_CloseFont(font);
	font = nullptr;
	buttonSrc = nullptr;
	delete buttonDst;
	buttonDst = nullptr;
	message = "";
	textPos = { 0,0,0,0 };
	buttonSize = { 0,0,0,0 };
	textColor = { 0,0,0,0 };
}

/// <summary>
///		Renders the button on screen with the message being centered.
/// </summary>
void Button::Draw() {
	TextureManager::DrawNine(renderer, buttonTexture, *buttonSrc, *buttonDst);
	FontManager::DrawFont(renderer, font, message, buttonDst->at(0).x + ((buttonSize.w / 2) - (textPos.w / 2)),
		buttonDst->at(0).y + ((buttonSize.h / 2) - (textPos.h / 3)), textColor);
}

// -----------------------------------------------------------

/// <summary>
///		Loads the texture for the buttons to hold a reference to.
/// </summary>
/// <param name="renderer">
///		Renderer to be drawn to.
/// </param>
ButtonManager::ButtonManager(SDL_Renderer* renderer) : renderer(renderer){
	texture = TextureManager::LoadTexture(renderer, "button.png");
	srcNine = TextureManager::NineClipSrc(5, 49, 45);
	currentIndex = 0;
	increment = 0;
	noOfButtons = 0;
}

/// <summary>
///		Free's memory on delete.
/// </summary>
ButtonManager::~ButtonManager() {
	Free();
}

/// <summary>
///		Cleans the objects memory. Cleans any dangling pointers.
/// </summary>
void ButtonManager::Free() {
	renderer = nullptr;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Free();
		delete buttons[i];
	}
	SDL_DestroyTexture(texture);
	texture = nullptr;
	delete srcNine;
	white = { 0,0,0,0 };
	black = { 0,0,0,0 };
	noOfButtons = 0;
	currentIndex = 0;
	increment = 0;
}

/// <summary>
///		Draws all the buttons. 
/// </summary>
void ButtonManager::Draw() {
	for (auto& item : buttons)
		item->Draw();
}

/// <summary>
///		Creates a button, then adds it to the list of buttons.
/// </summary>
/// <param name="dst">
///		Destination for the button to be drawn.
/// </param>
/// <param name="message">
///		Text on the button
/// </param>
void ButtonManager::AddButton(SDL_Rect dst, const char* message) {
	buttons.push_back(new Button(renderer, texture, dst, message, srcNine));
}

/// <summary>
///		Sets all the buttons to black text and the first button to white text. 
/// </summary>
void ButtonManager::SetButtons() {
	noOfButtons = buttons.size();
	for (int i = 0; i < noOfButtons; i++)
		buttons[i]->SetTextColor(black);
	buttons[currentIndex]->SetTextColor(white);
}

/// <summary>
///		Moves the selected button up. Sets all the buttons to black text and the currently selected
///		button to white text.
/// </summary>
void ButtonManager::MoveUp() {
	currentIndex--;
	if (currentIndex < 0)
		currentIndex = noOfButtons - 1;
	for (int i = 0; i < noOfButtons; i++)
		buttons[i]->SetTextColor(black);
	buttons[currentIndex]->SetTextColor(white);
}

/// <summary>
///		Moves the selected button down. Sets all the buttons to black text and the currently selected
///		button to white text.
/// </summary>
void ButtonManager::MoveDown() {
	currentIndex++;
	if (currentIndex > noOfButtons - 1)
		currentIndex = 0;
	for (int i = 0; i < noOfButtons; i++)
		buttons[i]->SetTextColor(black);
	buttons[currentIndex]->SetTextColor(white);
}

/// <summary>
///		Returns the current index of which button was pressed. 
/// </summary>
/// <returns>
///		Current selected button.
/// </returns>
int ButtonManager::Select() {
	return currentIndex;
}