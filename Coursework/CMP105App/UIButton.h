#pragma once
#include "UIComponent.h"
#include "Framework/Collision.h"
#include "Framework/Input.h"

#include "ButtonManager.h"
#include <functional>

class UIButton :
	public UIComponent
{
public:
	UIButton(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi, Input* in);

	void setInput(Input* in);
	void update() override;
	void draw() override;

	void setButtonFunction(std::function<void()> func);

private:
	//Function pointer. Attached from menu.
	std::function<void()> buttonFunction;

	Input* input;

	//Used to identify if the button has been pressed.
	bool isMouseDownLastFrame = false;

	sf::RectangleShape idleRect;
	sf::RectangleShape hoverRect;
};