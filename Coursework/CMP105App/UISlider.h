#pragma once
#include "UIComponent.h"
class UISlider :
	public UIComponent
{
	float* maxValue = nullptr;
	float* representedValue = nullptr;

	sf::RectangleShape slider;
	sf::RectangleShape outline;
public:
	UISlider(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi);
	void setSliderValues(float* maxVal, float* repVal);
	void setSliderColours(sf::Color outline, sf::Color slider);
	void update() override;
	void draw() override;
};