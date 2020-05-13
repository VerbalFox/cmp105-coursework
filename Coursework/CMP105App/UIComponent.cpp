#include "UIComponent.h"

UIComponent::UIComponent()
{
}

void UIComponent::setPositionPercent(float x, float y)
{
	//Takes in percentages and adjusts the elements to be positioned at those percentages on the screen.
	sf::Vector2f viewSize = window->getView().getSize();
	xPercentage = x;
	yPercentage = y;

	setPosition(
		(viewSize.x * (xPercentage / 100)) + (window->getView().getCenter().x - (viewSize.x / 2)),
		(viewSize.y * (yPercentage / 100)) + (window->getView().getCenter().y - (viewSize.y / 2))
	);

}

void UIComponent::setSizePercent(float x, float y)
{
	//Takes in percentages and adjusts the elements to be sized by those percentages relative to the size of the screen.
	sf::Vector2f viewSize = window->getView().getSize();
	widthPercentage = x;
	heightPercentage = y;

	setSize(sf::Vector2f(viewSize.x * (widthPercentage / 100), viewSize.y * (heightPercentage / 100)));
}

void UIComponent::setWindow(sf::RenderWindow* wi)
{
	window = wi;
}

ElementID UIComponent::getID()
{
	return id;
}

void UIComponent::setID(ElementID newID)
{
	id = newID;
}

void UIComponent::update()
{
}

void UIComponent::draw()
{
}