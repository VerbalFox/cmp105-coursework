#pragma once
#include "UIButton.h"
#include "UISlider.h"
#include <vector>
#include <functional>
#include "Framework/GameState.h"
#include "Framework/Input.h"

class UIManager
{
	std::vector<UIButton> buttons;
	std::vector<UISlider> sliders;
	sf::RenderWindow* window;
	Input* input;
public:
	UIManager();
	void setWindow(sf::RenderWindow* wi);
	void setInput(Input* in);

	void addSlider(float posX, float posY, float sizeX, float sizeY, sf::Color outlineColour, sf::Color filledColour, float* maxValue, float* displayValue);
	void addButton(float posX, float posY, float sizeX, float sizeY);
	void update();
	void draw();
};