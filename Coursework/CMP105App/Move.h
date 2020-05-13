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

//CharState is kept here since moves need to know what state they can be performed from, and Characters include Move anyway, so they'll have access.
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
	//How long to stun the opponent for.
	int stunnedFrames;
	int blockedFrames;
	//Position of the moves hitbox relative to the character.
	sf::FloatRect hitbox;
	//For potentially several frames of input. Checked against the buffer which only updates when the frame changes.
	std::vector<InputFrame> moveInput;
	//Velocity to move the character by while the move is active.
	sf::Vector2f charVelocity;

	//State the character must be in to unlock the move.
	CharState availableFromState;

	//Sadly unused.
	bool isProjectileMove = false;

	bool isFlipped = false;
	bool isMoveActive = false;

	//To track if the move has done damage.
	bool moveDamaged = false;

	MoveState currentState = MoveState::inactive;
	Animation* currentAnimation = nullptr;

public:
	Move();
	~Move();

	//Setters for all move properties. Used in the move setups visible in the TestChar constructor.
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

	//Getters for the move properties. Not all of them, just the ones I needed at one point or another.
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