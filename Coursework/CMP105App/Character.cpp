#include "Character.h"
#include <iostream>

Character::Character() {
	//Set type on GameObject
	type = ObjectType::character;
}

Character::~Character()
{
}

float* Character::getMaxHealth()
{
	return &maxHealth;
}

float* Character::getHealth()
{
	return &health;
}

void Character::setFacingLeft(bool facingLe)
{
	facingLeft = facingLe;
}

bool Character::isPlayerOne()
{
	return playerOne;
}

void Character::setPlayerNumber(int i)
{
	//For positioning, stat tracking, etc.
	if (i == 1) {
		playerOne = true;
	}
	else {
		playerOne = false;
	}
}

InputFrame Character::handleInput()
{
	currentFrame = charController->frameDecision();

	return currentFrame;
}

void Character::update()
{
	//Check move list for move to run based on this frames input.
	for (std::vector<Move*>::iterator it = moveList.begin(); it != moveList.end(); ++it) {
		bool performMove = true;
		for (int i = 0; i < (*it)->getMoveInput().capacity(); i++) {
			if (!isFlipped) {
				if (!(*it)->getMoveInput()[i].Equals(charController->getInputBuffer()[i])) {
					performMove = false;
				}
			}
			else {
				if (!(*it)->getMoveInput()[i].Equals(charController->getInputBuffer()[i].Flipped(charController->getInputBuffer()[i]))) {
					performMove = false;
				}
			}
		}
		//If inputs check out and the current character state matches the move
		if (performMove && (*it)->getMoveStartingState() == state) {
			currentMove = (*it);
			currentMove->activateMove(isFlipped);
			state = CharState::moveInitial;
			break;
		}
	}

	//Death check
	if (health <= 0 && !hasDied) {
		hasDied = true;
		state = CharState::launched;
	}

	//If animation attached to state that doesn't loop finishes, reset state. Several unused here.
	if (!currentAnimation->getPlaying()) {
		switch (state)
		{
		case CharState::blocking:
			state = CharState::idle;
			break;
		case CharState::stunned:
			state = CharState::idle;
			break;
		case CharState::wakingUp:
			break;
		case CharState::hasWon:
			break;
		default:
			break;
		}
	}

	//Perform generic actions based on input. Running, jumping, etc.
	switch (currentFrame.direction) {
	case Direction::up:
		jump();
		break;
	case Direction::upRight:
		jump();
		break;
	case Direction::upLeft:
		jump();
		break;
	case Direction::down:
		if (state == CharState::idle ||
			state == CharState::running
			) {
			state = CharState::crouching;
		}
		break;
	case Direction::right:
		if (state == CharState::idle) {
			state = CharState::running;
			flip();
		}
		break;
	case Direction::left:
		if (state == CharState::idle) {
			state = CharState::running;
			flip();
		}
		break;
	case Direction::none:
		if (state == CharState::crouching || state == CharState::running) {
			state = CharState::idle;
		}
		break;
	}

	//Flip animation.
	if (isFlipped) {
		currentAnimation->setFlipped(true);
	}
	else {
		currentAnimation->setFlipped(false);
	}

	//Move progression and logic.
	if (state == CharState::moveInitial || state == CharState::moveActive || state == CharState::moveRecovery) {
		currentMove->performMoveFrame();
		setTextureRect(currentMove->getMoveFrame());
		if (currentMove->getMoveState() == MoveState::active) {
			state = CharState::moveActive;
		}
		else if (currentMove->getMoveState() == MoveState::recovery) {
			state = CharState::moveRecovery;
		}
		else if (currentMove->getMoveState() == MoveState::inactive) {
			state = currentMove->getMoveStartingState();
			currentMove = nullptr;
		}
	}
	else {
		currentAnimation->animate();
		setTextureRect(currentAnimation->getCurrentFrame());
	}

	//State transitions. When a state changes, values are adjusted here.
	if (lastFrameState != state) {
		currentAnimation->reset();

		switch (state) {
		case CharState::running:
			currentAnimation = &runningAnim;
			if (currentFrame.direction == Direction::left) {
				velocity.x = -moveSpeed;
			}
			else {
				velocity.x = moveSpeed;
			}
			break;
		case CharState::idle:
			velocity.x = 0;
			currentAnimation = &idleAnim;
			break;
		case CharState::jumping:
			if (lastFrameState == CharState::idle || lastFrameState == CharState::running) {
				move(0, -5);
				velocity.y = -jumpForce;
			}
			break;
		case CharState::launched:
			velocity.y = -jumpForce;
			move(0, -5);
			if (isFlipped) {
				velocity.x = moveSpeed * .2;
			}
			else {
				velocity.x = -moveSpeed * .2;
			}
			break;
		case CharState::crouching:
			velocity.x = 0;
			currentAnimation = &crouchingAnim;
			break;
		case CharState::stunned:
			velocity.x = 0;
			currentAnimation = &stunAnim;
			break;
		case CharState::blocking:
			velocity.x = 0;
			currentAnimation = &blockAnim;
			break;
		}
	}

	//Generic state logic. Used to adjust things like jumping frames since they're dependent on the y-velocity.
	switch (state)
	{
	case CharState::idle:
		break;
	case CharState::running:
		break;
	case CharState::jumping:
		if (velocity.y < -300) {
			setTextureRect(getJumpFrame(0));
		}
		else if (velocity.y > 300) {
			setTextureRect(getJumpFrame(2));
		}
		else {
			setTextureRect(getJumpFrame(1));
		}
		break;
	case CharState::moveInitial:
		setVelocity(currentMove->getCharVelocity().x * ((isFlipped) ? -1 : 1), currentMove->getCharVelocity().y);
		break;
	case CharState::moveActive:
		setVelocity(currentMove->getCharVelocity().x * ((isFlipped) ? -1 : 1), currentMove->getCharVelocity().y);
		break;
	case CharState::moveRecovery:
		break;
	case CharState::crouching:
		break;
	case CharState::launched:
		if (velocity.y < -300) {
			setTextureRect(getLaunchFrame(0));
		}
		else if (velocity.y > 300) {
			setTextureRect(getLaunchFrame(2));
		}
		else {
			setTextureRect(getLaunchFrame(1));
		}
		break;
	case CharState::grounded:
		setTextureRect(getGroundedFrame());
		velocity.x = 0;
		velocity.y = 0;
		state == CharState::idle;
		break;
	case CharState::blocking:
		break;
	case CharState::stunned:
		break;
	case CharState::wakingUp:
		break;
	case CharState::hasWon:
		break;
	case CharState::death:
		setTextureRect(getGroundedFrame());
		velocity.x = 0;
		velocity.y = 0;
		break;
	default:
		break;
	}
	
	//Position adjustments.
	if (state != CharState::moveInitial && state != CharState::moveActive) {
		setVelocity(getVelocity().x, getVelocity().y + (gravity * time));
	}
	
	setPosition(
		getPosition().x + (getVelocity().x * time),
		std::min(getPosition().y + (getVelocity().y * time), double(-getSize().y))
	);

	lastFrameState = state;
}

void Character::flip()
{
	//Flip to direction indicted by the GameManager.
	if (!facingLeft) {
		isFlipped = true;
	}
	else {
		isFlipped = false;
	}
}

void Character::jump()
{
	//Jump if states allow for it.
	if (state == CharState::idle ||
		state == CharState::running
		) {
		state = CharState::jumping;
	}
}

void Character::resetCharacter()
{
	//Reset character values.
	health = maxHealth;
	state = CharState::idle;
	hasDied = false;
	flip();
}

void Character::setController(Controller* tempController)
{
	charController = tempController;
}

void Character::hitResponse(Move* curMove)
{
	//Check if move has caused damage yet. If not, cause damage and run move hit logic.
	if (!curMove->getMoveDamaged()) {
		curMove->setIsMoveDamaged(true);
		health -= curMove->getDamage();
		stunAnim.setFrameSpeed(curMove->getStunnedFrames());
		if (state == CharState::launched) {
			velocity.x = ((isFlipped) ? std::abs(velocity.x) * launchForceMultiplier : std::abs(velocity.x) * -launchForceMultiplier);
			velocity.y = -jumpForce;
		}
		else if (state == CharState::jumping) {
			state == CharState::launched;
		}
		else {
			state = CharState::stunned;
		}
	}

}

void Character::collisionResponse(GameObject* collider)
{
	//Collision checks for other character and floor.
	if (collider->getType() == ObjectType::character) {
		if (collider->getPosition().x > getPosition().x) {
			move(-5, 0);
		}
		else {
			move(5, 0);
		}
	}

	if (collider->getType() == ObjectType::floor) {
		if (state == CharState::launched && health > 0) {
			state = CharState::grounded;
		}
		else if (state == CharState::launched && health <= 0) {
			state = CharState::death;
		}
		if (state == CharState::jumping) {
			state = CharState::idle;
		}
		setVelocity(getVelocity().x, std::min(getVelocity().y, float(0)));
	}
}

int Character::getRoundsWon()
{
	return roundsWon;
}

void Character::incrementRoundsWon()
{
	roundsWon++;
}

Move* Character::getCurrentMove()
{
	return currentMove;
}

sf::FloatRect Character::getMoveRect()
{
	sf::FloatRect temp;
	if (currentMove == nullptr) {
		return temp;
	}

	temp.height = currentMove->getMoveHitbox().height;
	temp.width = currentMove->getMoveHitbox().width;
	if (isFlipped) {
		temp.left = getPosition().x + (getSize().x / 2) - moveList[0]->getMoveHitbox().left - moveList[0]->getMoveHitbox().width;
	}
	else {
		temp.left = getPosition().x + (getSize().x / 2) + moveList[0]->getMoveHitbox().left;
	}
	temp.top = moveList[0]->getMoveHitbox().top + getPosition().y;
	return temp;
}

sf::FloatRect Character::getHighHitbox()
{
	sf::FloatRect temp;
	temp.height = highHitbox.height;
	temp.width = highHitbox.width;
	if (isFlipped) {
		temp.left = getPosition().x + (getSize().x / 2) - highHitbox.left - highHitbox.width;
	}
	else {
		temp.left = getPosition().x + (getSize().x / 2) + highHitbox.left;
	}
	temp.top = highHitbox.top + getPosition().y;
	return temp;
}

sf::FloatRect Character::getLowHitbox()
{
	sf::FloatRect temp;
	temp.height = lowHitbox.height;
	temp.width = lowHitbox.width;
	if (isFlipped) {
		temp.left = getPosition().x + (getSize().x / 2) - lowHitbox.left - lowHitbox.width;
	}
	else {
		temp.left = getPosition().x + (getSize().x / 2) + lowHitbox.left;
	}
	temp.top = lowHitbox.top + getPosition().y;
	return temp;
}

sf::IntRect Character::getJumpFrame(int frame)
{
	sf::IntRect temp = jumpFrames[frame];
	if (isFlipped) {
		temp = sf::IntRect(temp.left + temp.width, temp.top, -temp.width, temp.height);
	}
	return temp;
}

sf::IntRect Character::getLaunchFrame(int frame)
{
	sf::IntRect temp = launchFrames[frame];
	if (isFlipped) {
		temp = sf::IntRect(temp.left + temp.width, temp.top, -temp.width, temp.height);
	}
	return temp;
}

sf::IntRect Character::getGroundedFrame()
{
	sf::IntRect temp = groundedFrame;
	if (isFlipped) {
		temp = sf::IntRect(temp.left + temp.width, temp.top, -temp.width, temp.height);
	}
	return temp;
}
