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
	//Generic animations.
	Animation idleAnim;
	Animation runningAnim;
	Animation crouchingAnim;
	Animation wakeupAnim;
	Animation victoryAnim;

	Animation stunAnim;
	Animation blockAnim;

	//Current animation pointer.
	Animation* currentAnimation = &idleAnim;
	
	//Frames for logic based "animations"
	sf::IntRect jumpFrames[3];
	sf::IntRect launchFrames[3];
	sf::IntRect groundedFrame;

	sf::Texture charTexture;

	//Character variable setups.
	float maxHealth = 1;
	float health = maxHealth;
	sf::Vector2i characterSize;
	float moveSpeed = 10;
	float jumpForce = 10;
	int roundsWon = 0;

	float launchForceMultiplier = 2;
	double time = static_cast<float>(1) / 60;
	float gravity = 800;

	bool facingLeft = false;
	bool isFlipped = false;

	bool playerOne = false;

	//Don't really know why I set this variable up, the GameObject class has an 'isAlive' variable.
	bool hasDied = false;

	CharState lastFrameState = CharState::idle;
	CharState state = CharState::idle;

	//Controller pointer.
	Controller* charController = nullptr;

	InputFrame currentFrame;

	Move* currentMove = nullptr;
	std::vector<Move*> moveList;

	sf::FloatRect lowHitbox;
	sf::FloatRect highHitbox;

public:
	Character();
	~Character();

	//Returned as pointers for usage by the UISliders. Probably better to just update by value.
	float* getMaxHealth();
	float* getHealth();
	void setFacingLeft(bool facingLe);

	bool isPlayerOne();
	void setPlayerNumber(int);
	InputFrame handleInput();
	void update();
	void flip();
	void jump();

	void resetCharacter();

	void setController(Controller*);
	void hitResponse(Move*);
	void collisionResponse(GameObject*);

	//Getter and 'setter' for rounds. Used by the GameManager.
	int getRoundsWon();
	void incrementRoundsWon();

	Move* getCurrentMove();

	sf::FloatRect getMoveRect();
	sf::FloatRect getHighHitbox();
	sf::FloatRect getLowHitbox();

	sf::IntRect getJumpFrame(int frame);
	sf::IntRect getLaunchFrame(int frame);
	sf::IntRect getGroundedFrame();
};