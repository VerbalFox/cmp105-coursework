#pragma once
#include "Framework/Animation.h"
#include "InputFrame.h"
#include <vector>

enum class MoveState {
	inactive,
	initial,
	active,
	recovery
}; 

enum class CharState
{
	idle,
	running,
	jumping,
	moveInitial,
	moveActive,
	moveRecovery,
	crouching,
	launched,
	grounded,
	blocking,
	stunned,
	wakingUp,
	hasWon,
	death
};

class Move
{
private:
	Animation initialAnim;
	Animation activeAnim;
	Animation recoveryAnim;
	float damage;
	int stunnedFrames;
	int blockedFrames;
	sf::FloatRect hitbox;
	std::vector<InputFrame> moveInput;
	sf::Vector2f charVelocity;

	CharState availableFromState;

	bool isProjectileMove = false;
	bool isFlipped = false;
	bool isMoveActive = false;
	bool moveDamaged = false;

	MoveState currentState = MoveState::inactive;
	Animation* currentAnimation = nullptr;

public:
	Move();
	~Move();

	void setIsMoveDamaged(bool newActive);
	void setIsProjectileMove(bool newProjectileSet);
	void setMoveInput(std::vector<InputFrame> newMoveInput);
	void setMoveSpeeds(int newInitialSpeed, int newActiveSpeed, int newRecoverySpeed);
	void setAnimations(Animation newInitial, Animation newActive, Animation newRecovery);
	void setDamage(float newDamage);
	void setHitbox(sf::FloatRect newHitbox);
	void setCharVelocity(sf::Vector2f newCharVelocity);
	void setAvailableFromState(CharState state);
	void setStunnedFrames(int stunnedFr);
	void setBlockedFrames(int blockedFr);

	void activateMove(bool flipped);

	void performMoveFrame();
	sf::IntRect getMoveFrame();

	bool getMoveDamaged();
	MoveState getMoveState();
	std::vector<InputFrame> getMoveInput();
	CharState getMoveStartingState();
	sf::FloatRect getMoveHitbox();
	float getDamage();
	sf::Vector2f getCharVelocity();
	int getStunnedFrames();
	int getBlockedFrames();
};