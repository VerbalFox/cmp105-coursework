#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "GameManager.h"
#include <string>
#include <iostream>

class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameManager* game);
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

	GameObject floor;
};