#include "UIText.h"

UIText::UIText(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi)
{
	window = wi;

	setPositionPercent(posX, posY);
	setSizePercent(sizeX, sizeY);

	text.setFillColor(sf::Color::White);
	text.setString(" ");
}

void UIText::setFont(sf::Font* newFont)
{
	text.setFont(*newFont);
}

void UIText::setTextString(std::string newString)
{
	text.setString(newString);
}

void UIText::update()
{
	setPositionPercent(xPercentage, yPercentage);
	setSizePercent(widthPercentage, heightPercentage);

	text.setPosition(
		getPosition().x + (getSize().x / 2) - (text.getLocalBounds().width / 2), 
		getPosition().y + (getSize().y / 2) - (text.getLocalBounds().height)
	);
}

void UIText::draw()
{
	window->draw(text);
}