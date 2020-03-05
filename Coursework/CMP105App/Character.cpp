#include "Character.h"
#include <iostream>

Character::Character() {
	//setFillColor(sf::Color::White);
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

void Character::update()
{
	InputFrame thisFrame = charController->frameDecision();

	switch (thisFrame.direction) {
	case Direction::up:
		if (state == CharState::idle ||
			state == CharState::running
			) {
			velocity.y = -jumpForce;
			state = CharState::jumping;
		}
		break;
	case Direction::down:
		if (state == CharState::idle ||
			state == CharState::running
			) {
			state = CharState::crouching;
		}
		break;
	case Direction::right:
		velocity.x = moveSpeed;
		break;
	case Direction::left:
		velocity.x = -moveSpeed;
		break;
	case Direction::none:
		if (state == CharState::crouching) {
			state = CharState::idle;
		}
		velocity.x = 0;
		break;
	}

	if (state == CharState::idle) {
		idleAnim.animate();
		setTextureRect(idleAnim.getCurrentFrame());
	}

	double time = float(1) / 60;
	setVelocity(getVelocity().x, getVelocity().y + (750 * time));

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

void Character::run(float speed)
{
}

void Character::jump()
{
}

void Character::crouch()
{
}

void Character::setController(Controller* tempController)
{
	charController = tempController;
}

void Character::collisionResponse(GameObject* collider)
{
	if (collider->getType() == ObjectType::floor) {
		if (state == CharState::jumping) {
			state = CharState::idle;
		}
		setVelocity(getVelocity().x, std::min(getVelocity().y, float(0)));
	}
}