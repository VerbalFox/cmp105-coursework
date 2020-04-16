#pragma once
#include <vector>
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Controller.h"
#include "Move.h"

#include <iostream>

class Character :
	public GameObject
{
protected:
	Animation idleAnim;
	Animation runningAnim;
	Animation crouchingAnim;
	Animation wakeupAnim;
	Animation victoryAnim;

	Animation stunAnim;
	Animation blockAnim;

	Animation* currentAnimation = &idleAnim;
	
	sf::IntRect jumpFrames[3];
	sf::IntRect launchFrames[3];
	sf::IntRect groundedFrame;

	sf::Texture charTexture;

	float maxHealth = 1;
	float health = maxHealth;
	sf::Vector2i characterSize;
	float moveSpeed = 10;
	float jumpForce = 10;
	int roundsWon = 0;

	bool facingLeft = false;
	bool isFlipped = false;

	bool playerOne = false;

	bool hasDied = false;

	CharState lastFrameState = CharState::idle;
	CharState state = CharState::idle;
	Controller* charController = nullptr;

	Move* currentMove = nullptr;
	std::vector<Move*> moveList;

	sf::FloatRect lowHitbox;
	sf::FloatRect highHitbox;

public:
	Character();
	~Character();

	float* getMaxHealth();
	float* getHealth();
	void setFacingLeft(bool facingLe);

	bool isPlayerOne();
	void setPlayerNumber(int);
	void update();
	void flip();
	void jump();

	void resetCharacter();

	void setController(Controller*);
	void hitResponse(Move*);
	void collisionResponse(GameObject*);

	Move* getCurrentMove();

	std::vector<sf::RectangleShape> getDebugMoveRects();
	sf::FloatRect getMoveRect();
	sf::FloatRect getHighHitbox();
	sf::FloatRect getLowHitbox();

	sf::IntRect getJumpFrame(int frame);
	sf::IntRect getLaunchFrame(int frame);
	sf::IntRect getGroundedFrame();
};