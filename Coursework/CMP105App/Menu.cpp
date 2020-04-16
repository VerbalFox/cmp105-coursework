#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs)
{
	window = hwnd;
	input = in;
	gameState = gs;

	uiManager.setWindow(window);
	uiManager.setInput(input);

	uiManager.addButton(10, 10, 80, 20, gameState, State::LEVEL);
}

Menu::~Menu()
{

}

// handle user input
void Menu::handleInput()
{

}

// Update game objects
void Menu::update()
{
	uiManager.update();
}

// Render level
void Menu::render()
{
	beginDraw();
	uiManager.draw();
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to black.
void Menu::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Menu::endDraw()
{
	window->display();
}

void Menu::toGame()
{
	gameState->setCurrentState(State::LEVEL);
}
