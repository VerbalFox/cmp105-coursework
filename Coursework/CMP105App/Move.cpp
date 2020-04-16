#include "Move.h"

Move::Move()
{
}

Move::~Move()
{
}

void Move::setIsMoveDamaged(bool newActive)
{
	moveDamaged = newActive;
}

void Move::setIsProjectileMove(bool newProjectileSet)
{
	isProjectileMove = newProjectileSet;
}

void Move::setMoveInput(std::vector<InputFrame> newMoveInput)
{
	moveInput = newMoveInput;
}

void Move::setMoveSpeeds(int newInitialSpeed, int newActiveSpeed, int newRecoverySpeed)
{
	initialAnim.setFrameSpeed(newInitialSpeed);
	activeAnim.setFrameSpeed(newActiveSpeed);
	recoveryAnim.setFrameSpeed(newRecoverySpeed);
}

void Move::setAnimations(Animation newInitial, Animation newActive, Animation newRecovery)
{
	initialAnim = newInitial;
	activeAnim = newActive;
	recoveryAnim = newRecovery;

	initialAnim.setLooping(false);
	activeAnim.setLooping(false);
	recoveryAnim.setLooping(false);
}

void Move::setDamage(float newDamage)
{
	damage = newDamage;
}

void Move::setHitbox(sf::FloatRect newHitbox)
{
	hitbox = newHitbox;
}

void Move::setCharVelocity(sf::Vector2f newCharVelocity)
{
	charVelocity = newCharVelocity;
}

void Move::setAvailableFromState(CharState state)
{
	availableFromState = state;
}

void Move::setStunnedFrames(int stunnedFr)
{
	stunnedFrames = stunnedFr;
}

void Move::setBlockedFrames(int blockedFr)
{
	blockedFrames = blockedFr;
}

void Move::activateMove(bool flipped)
{
	if (!isMoveActive) {
		isMoveActive = true;
		moveDamaged = false;
		isFlipped = flipped;
		initialAnim.setFlipped(flipped);
		activeAnim.setFlipped(flipped);
		recoveryAnim.setFlipped(flipped);
	}
}

void Move::performMoveFrame()
{
	if (isMoveActive) {
		if (currentState == MoveState::inactive) {
			currentState = MoveState::initial;
			currentAnimation = &initialAnim;
		}

		if (!currentAnimation->getPlaying()) {
			if (currentState == MoveState::initial) {
				currentState = MoveState::active;
				currentAnimation = &activeAnim;
			}
			else if (currentState == MoveState::active) {
				currentState = MoveState::recovery;
				currentAnimation = &recoveryAnim;
			}
			else if (currentState == MoveState::recovery) {
				currentState = MoveState::inactive;
				initialAnim.reset();
				activeAnim.reset();
				recoveryAnim.reset();
				isMoveActive = false;
			}
		}
	}

	currentAnimation->animate();
}

sf::IntRect Move::getMoveFrame()
{
	return currentAnimation->getCurrentFrame();
}

bool Move::getMoveDamaged()
{
	return moveDamaged;
}

MoveState Move::getMoveState()
{
	return currentState;
}

std::vector<InputFrame> Move::getMoveInput()
{
	return moveInput;
}

CharState Move::getMoveStartingState()
{
	return availableFromState;
}

sf::FloatRect Move::getMoveHitbox()
{
	return hitbox;
}

float Move::getDamage()
{
	return damage;
}

sf::Vector2f Move::getCharVelocity()
{
	return charVelocity;
}

int Move::getStunnedFrames()
{
	return stunnedFrames;
}

int Move::getBlockedFrames()
{
	return blockedFrames;
}
