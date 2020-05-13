#pragma once
#include "UIComponent.h"
class UIText :
	public UIComponent
{
	sf::Text text;
public:
	UIText(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi);
	void setFont(sf::Font* font);
	void setTextString(std::string newString);
	void update() override;
	void draw() override;
};