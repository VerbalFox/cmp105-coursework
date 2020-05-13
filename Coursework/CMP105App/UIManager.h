#pragma once
#include "UIButton.h"
#include "UISlider.h"
#include "UIText.h"

#include <vector>
#include "Framework/GameState.h"
#include "Framework/Input.h"

class UIManager
{
	//Done as pointers to make it a little easier for me to sleep at night knowing I'm only pushing addresses to the vector, not entire class instances.
	//No idea if it's more efficient, does seem so from the surface.s
	std::vector<UIButton*> buttons;
	std::vector<UISlider*> sliders;
	std::vector<UIText*> texts;

	sf::RenderWindow* window;
	Input* input;

	sf::Font font;

public:
	UIManager();
	void setWindow(sf::RenderWindow* wi);
	void setInput(Input* in);

	void addSlider(ElementID newID, float posX, float posY, float sizeX, float sizeY, sf::Color outlineColour, sf::Color filledColour, float* maxValue, float* displayValue);
	void addButton(ElementID newID, float posX, float posY, float sizeX, float sizeY, std::function<void()> func);
	void addText(ElementID newID, float posX, float posY, float sizeX, float sizeY);
	void setTextStringById(ElementID id, std::string newString);
	void clearElements();
	void update();
	void draw();
};