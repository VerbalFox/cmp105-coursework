#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Controller.h"
#include "Move.h"

enum class CharState
{
	idle,
	running,
	jumping,
	moveInitial,
	moveActive,
	moveRecovery,
	crouching,
	crouchRunning,
	launched,
	grounded,
	blocking,
	stunned,
	wakingUp,
	hasWon,
	death
};

class Character :
	public GameObject
{
protected:
	Animation idleAnim;
	Animation runningAnim;
	Animation crouchingAnim;
	Animation crouchRunAnim;
	Animation wakeupAnim;
	Animation victoryAnim;

	sf::IntRect jumpFrames[3];
	sf::IntRect launchFrames[3];

	sf::Texture charTexture;

	int maxHealth = 1;
	int health = maxHealth;
	sf::Vector2i characterSize;
	float moveSpeed = 10;
	float jumpForce = 10;
	int roundsWon = 0;
	bool isFlipped = false;
	bool playerOne = false;

	CharState state = CharState::idle;
	Controller* charController = nullptr;

public:
	Character();
	~Character();

	bool isPlayerOne();
	void setPlayerNumber(int);
	void update();
	void flip();

	void run(float speed);
	void jump();
	void crouch();

	void setController(Controller*);
	void collisionResponse(GameObject*);
};