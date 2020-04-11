#include "UIComponent.h"

UIComponent::UIComponent()
{
}

void UIComponent::setPositionPercent(float x, float y)
{
	sf::Vector2u windowSize = window->getSize();
	xPercentage = x;
	yPercentage = y;

	setPosition(
		(windowSize.x * (xPercentage / 100)) + (window->getView().getCenter().x - (windowSize.x / 2)),
		(windowSize.y * (yPercentage / 100)) + (window->getView().getCenter().y - (windowSize.y / 2))
	);

}

void UIComponent::setSizePercent(float x, float y)
{
	sf::Vector2u windowSize = window->getSize();
	widthPercentage = x;
	heightPercentage = y;

	setSize(sf::Vector2f(windowSize.x * (widthPercentage / 100), windowSize.y * (heightPercentage / 100)));
}

void UIComponent::setWindow(sf::RenderWindow* wi)
{
	window = wi;
}

void UIComponent::update()
{
}

void UIComponent::draw()
{
}