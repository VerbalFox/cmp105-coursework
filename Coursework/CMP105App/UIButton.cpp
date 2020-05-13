#include "UIButton.h"

UIButton::UIButton(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi, Input* in)
{
	setInput(in);
	setWindow(wi);
	setPositionPercent(posX, posY);
	setSizePercent(sizeX, sizeY);

	setCollisionBox(sf::FloatRect(0, 0, getSize().x, getSize().y));
}

void UIButton::setInput(Input* in)
{
	input = in;
}

void UIButton::update()
{
	sf::Vector2f windowSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	//Adjust positions and sizes in case of window size change. Didn't need to do this every frame, seems to cause stuttering as a result. Didn't have time to fix.
	setPositionPercent(xPercentage, yPercentage);
	setSizePercent(widthPercentage, heightPercentage);

	setCollisionBox(sf::FloatRect(0, 0, getSize().x, getSize().y));

	//Map mouse position relative to screen.
	sf::Vector2i temp = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

	//Highlight if hovered over.
	if (Collision::checkBoundingBox(this, temp)) {
		setFillColor(sf::Color::Red);
	}
	else {
		setFillColor(sf::Color::Blue);
	}

	//If a click down and up has been detected while hovering over the button.
	if (isMouseDownLastFrame && !input->isMouseLDown() && Collision::checkBoundingBox(this, temp)) {
		isMouseDownLastFrame = false;
		//Call the function at the function pointer.
		buttonFunction();
	}
	else {
		//Keep track of presses to identify a button press later on.
		isMouseDownLastFrame = input->isMouseLDown();
	}
}

void UIButton::draw() {
	window->draw(*this);
}

void UIButton::setButtonFunction(std::function<void()> func)
{
	buttonFunction = func;
}