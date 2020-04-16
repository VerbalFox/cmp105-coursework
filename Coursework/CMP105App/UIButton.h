#pragma once
#include "UIComponent.h"
#include "Framework/Collision.h"
#include "Framework/Input.h"
#include <functional>
#include "Framework/GameState.h"

class UIButton :
	public UIComponent
{
public:
	UIButton(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi, Input* in);
	void setGameState(GameState* gs);
	void setTargetState(State s);

	void changeState(State s);

	void setInput(Input* in);
	void update() override;
	void draw() override;

private:
	sf::Texture idleButton;
	sf::Texture hoverButton;

	Input* input;
	GameState* gameState;

	State targetState;

	bool isMouseDownLastFrame = false;

	sf::RectangleShape idleRect;
	sf::RectangleShape hoverRect;

};