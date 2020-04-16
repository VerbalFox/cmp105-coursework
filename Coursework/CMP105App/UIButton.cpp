#include "UIButton.h"

UIButton::UIButton(float posX, float posY, float sizeX, float sizeY, sf::RenderWindow* wi, Input* in)
{
	setInput(in);
	setWindow(wi);
	setPositionPercent(posX, posY);
	setSizePercent(sizeX, sizeY);

	setCollisionBox(sf::FloatRect(0, 0, getSize().x, getSize().y));
}

void UIButton::setGameState(GameState* gs)
{
	gameState = gs;
}

void UIButton::setTargetState(State s)
{
	targetState = s;
}

void UIButton::changeState(State s)
{
	gameState->setCurrentState(s);
}

void UIButton::setInput(Input* in)
{
	input = in;
}

void UIButton::update()
{
	sf::Vector2f windowSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	setPosition(
		(windowSize.x * (xPercentage / 100)) + (window->getView().getCenter().x - (windowSize.x / 2)),
		(windowSize.y * (yPercentage / 100)) + (window->getView().getCenter().y - (windowSize.y / 2))
	);

	setSize(sf::Vector2f(windowSize.x * (widthPercentage / 100), windowSize.y * (heightPercentage / 100)));

	sf::Vector2i temp = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

	if (Collision::checkBoundingBox(this, temp)) {
		setFillColor(sf::Color::White);
		if (isMouseDownLastFrame && !input->isMouseLDown()) {
			changeState(targetState);
		}
	}
	else {
		setFillColor(sf::Color::Blue);
	}

	isMouseDownLastFrame = input->isMouseLDown();
}

void UIButton::draw() {
	window->draw(*this);
}