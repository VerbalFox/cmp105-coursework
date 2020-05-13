#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include "Framework/GameState.h"
#include "Framework/AudioManager.h"

#include "GameManager.h"

#include "UIManager.h"

class Menu {
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameManager* gm, GameState* gs, AudioManager* am);
	~Menu();

	void handleInput();
	void update();
	void render();

	void toLocalGame();
	void toNetworkedGame();

	void displayMainMenu();
	void displayOptions();
	void displayControls();

	void decreaseVolume();
	void increaseVolume();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	GameManager* gameManager;
	AudioManager* audioManager;

	UIManager uiManager;
};