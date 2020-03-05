#include "TestChar.h"

TestChar::TestChar()
{
	maxHealth = 100;
	health = maxHealth;
	characterSize = sf::Vector2i(225, 238);
	moveSpeed = 100;
	jumpForce = 400;
	roundsWon = 0;

	setSize(sf::Vector2f(characterSize.x, characterSize.y));
	setCollisionBox(0, 0, characterSize.x, characterSize.y);
	setTexture(&charTexture);

	if (charTexture.loadFromFile("gfx/fighter.png")) {

	}

	int xResolution = 8015;
	int yResolution = 6902;
	int xCels = 35;
	int yCels = 29;
	int xSize = 229;
	int ySize = 238;
	int yMargin = 16;

	int startingFrame = 0;
	int xFrame = 0;
	int yFrame = 0;


	idleAnim.setFrameSpeed(30);

	startingFrame = 6;
	xFrame = startingFrame;

	while (startingFrame > xCels) {
		startingFrame -= xCels;
		yFrame++;
		xFrame = startingFrame;
	}

	for (int8_t i = 0; i < 10; i++)
	{
		idleAnim.addFrame(sf::IntRect((xFrame * xSize) + (i * xSize), (yFrame * ySize), xSize, ySize - yMargin));

		if (xFrame >= xCels) {
			yFrame++;
			xFrame = 0;
		}

	}
}

TestChar::~TestChar()
{

}
