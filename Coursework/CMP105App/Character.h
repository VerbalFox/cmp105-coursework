#pragma once
#include "Framework/GameObject.h"

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
	wakingUp,
	hasWon,
	death
};

class Character :
	public GameObject
{
protected:
	int maxHealth = 1;
	int health = maxHealth;
	sf::Vector2i characterSize = sf::Vector2i(50, 100);
	float moveSpeed = 10;
	float jumpForce = 10;
	int roundsWon = 0;
	bool isFlipped = false;
	bool playerOne = false;

	CharState state = CharState::idle;
	
public:
	Character();
	~Character();

	bool isPlayerOne();
	void setPlayerNumber(int);
	void handleInput();
	void update();
	void flip();
	void collisionResponse(GameObject*);
};