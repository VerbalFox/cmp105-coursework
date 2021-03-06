#include "UISlider.h"

UISlider::UISlider(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi)
{
	setWindow(wi);
	setPositionPercent(posX, posY);
	setSizePercent(sizeX, sizeY);
}

void UISlider::setSliderValues(float* maxVal, float* repVal)
{
	//I should probably have just done these by value. Does make it easier to work with.
	representedValue = repVal;
	maxValue = maxVal;
}

void UISlider::setSliderColours(sf::Color out, sf::Color sli)
{
	outline.setFillColor(sf::Color::Transparent);
	slider.setOutlineColor(sf::Color::Transparent);

	outline.setOutlineThickness(3);

	outline.setOutlineColor(out);
	outline.setFillColor(sf::Color::Red);
	slider.setFillColor(sli);
}

void UISlider::update()
{
	sf::Vector2f windowSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	outline.setSize(getSize());
	slider.setSize(sf::Vector2f(std::max(getSize().x * (*representedValue / *maxValue), 0.f), getSize().y));

	setPositionPercent(xPercentage, yPercentage);
	setSizePercent(widthPercentage, heightPercentage);

	outline.setPosition(getPosition());
	slider.setPosition(getPosition());
}

void UISlider::draw()
{
	window->draw(outline);
	window->draw(slider);
}