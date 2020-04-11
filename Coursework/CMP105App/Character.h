#pragma once
#include <vector>
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
	Animation wakeupAnim;
	Animation victoryAnim;

	Animation* currentAnimation = &idleAnim;
	
	sf::IntRect jumpFrames[3];
	sf::IntRect launchFrames[3];

	sf::Texture charTexture;

	float maxHealth = 1;
	float health = maxHealth;
	sf::Vector2i characterSize;
	float moveSpeed = 10;
	float jumpForce = 10;
	int roundsWon = 0;
	bool isFlipped = false;
	bool playerOne = false;

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

	bool isPlayerOne();
	void setPlayerNumber(int);
	void update();
	void flip();

	void jump();

	void setController(Controller*);
	void hitResponse(Move*);
	void collisionResponse(GameObject*);

	Move* getCurrentMove();

	std::vector<sf::RectangleShape> getDebugMoveRects();
	sf::FloatRect getMoveRect();
	sf::FloatRect getHighHitbox();
	sf::FloatRect getLowHitbox();
};