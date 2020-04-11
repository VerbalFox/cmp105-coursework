#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include "Framework/GameState.h"

#include "UIManager.h"

class Menu{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Menu();

	void handleInput();
	void update();
	void render();

	void toGame();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();


	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	UIManager uiManager;
};