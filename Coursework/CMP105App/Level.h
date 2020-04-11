#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/GameState.h"
#include "PlayerController.h"
#include "GameManager.h"
#include <string>
#include <iostream>

#include "UIManager.h"

class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameManager* game, GameState* gs);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameManager* gm;
	GameState* gameState;

	UIManager uiManager;

	PlayerController control;
	Controller control1;

	GameObject floor;
};