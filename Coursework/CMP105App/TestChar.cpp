#include "TestChar.h"

TestChar::TestChar()
{
	maxHealth = 100;
	health = maxHealth;
	characterSize = sf::Vector2i(100, 100);
	moveSpeed = 100;
	jumpForce = 400;
	roundsWon = 0;
}

TestChar::~TestChar()
{

}
