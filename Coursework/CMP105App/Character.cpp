#include "Character.h"
#include <iostream>

Character::Character() {
	setSize(sf::Vector2f(characterSize.x, characterSize.y));
	setCollisionBox(0, 0, characterSize.x, characterSize.y);
}

Character::~Character()
{
}

bool Character::isPlayerOne()
{
	return playerOne;
}

void Character::setPlayerNumber(int i)
{
	if (i == 1) {
		playerOne = true;
	}
	else {
		playerOne = false;
	}
}

void Character::handleInput() {

}

void Character::update()
{
	double time = float(1) / 60;
	setVelocity(getVelocity().x, getVelocity().y + ((9.8 * time) * jumpForce));

	setPosition(
		getPosition().x + (getVelocity().x * time),
		std::min(getPosition().y + (getVelocity().y * time), double(-getSize().y))
	);
}

void Character::flip()
{
	if (!isFlipped) {
		isFlipped = true;
	}
	else {
		isFlipped = false;
	}


}

void Character::collisionResponse(GameObject* collider)
{
	if (collider->getType() == ObjectType::floor) {
		setVelocity(getVelocity().x, std::min(getVelocity().y, float(0)));
	}
}