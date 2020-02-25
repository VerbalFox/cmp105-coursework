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

class Move
{
private:
	Animation initialAnim;
	Animation activeAnim;
	Animation recoveryAnim;
	float damage;
	sf::FloatRect hitbox;
	int initialSpeed;
	int activeSpeed;
	int recoverySpeed;
	std::vector<InputFrame> moveInput;
	sf::Vector2f charVelocity;

	bool isProjectileMove = false;

	MoveState currentState = MoveState::inactive;

public:
	Move();
	~Move();

	sf::IntRect playMoveFrame();
	sf::FloatRect getMoveHitbox();
	void moveHit();
};

