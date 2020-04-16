#include "TestChar.h"

TestChar::TestChar()
{
	maxHealth = 10;
	health = maxHealth;
	characterSize = sf::Vector2i(225, 238);
	moveSpeed = 300;
	jumpForce = 400;
	roundsWon = 0;

	setSize(sf::Vector2f(characterSize.x, characterSize.y));
	setCollisionBox(0, 0, characterSize.x, characterSize.y);

	if (charTexture.loadFromFile("gfx/fighter.png")) {
		setTexture(&charTexture);
	}

	std::vector<InputFrame> tempMoveInput;
	InputFrame tempFrame;

	tempFrame.direction = Direction::none;
	tempFrame.attack = AttackButton::b1;
	tempMoveInput.push_back(tempFrame);

	lArmJab.setIsProjectileMove(false);
	lArmJab.setMoveInput(tempMoveInput);
	lArmJab.setAnimations(formAnimation(17, 3), formAnimation(20, 1), formAnimation(21, 2));
	lArmJab.setMoveSpeeds(9, 3, 10);
	lArmJab.setDamage(3);
	lArmJab.setHitbox(sf::FloatRect(45, 100, 2000, 10));
	lArmJab.setCharVelocity(sf::Vector2f(10, 0));
	lArmJab.setAvailableFromState(CharState::idle);
	lArmJab.setStunnedFrames(10);
	lArmJab.setBlockedFrames(10);

	moveList.push_back(&lArmJab);

	highHitbox = sf::FloatRect(-40, 70, 60, 80);
	lowHitbox = sf::FloatRect(-40, 155, 60, 90);

	idleAnim = formAnimation(6, 10);
	idleAnim.setFrameSpeed(60);

	runningAnim = formAnimation(482, 6);
	runningAnim.setFrameSpeed(40);

	wakeupAnim = formAnimation(315, 11);
	wakeupAnim.setFrameSpeed(30);

	crouchingAnim = formAnimation(729, 1);
	crouchingAnim.setFrameSpeed(40);

	victoryAnim = formAnimation(281, 9);
	victoryAnim.setFrameSpeed(40);

	stunAnim = formAnimation(492, 4);
	stunAnim.setFrameSpeed(10);

	blockAnim = formAnimation(917, 1);
	blockAnim.setFrameSpeed(10);

	stunAnim.setLooping(false);
	blockAnim.setLooping(false);

	jumpFrames[0] = getFrame(556);
	jumpFrames[1] = getFrame(559);
	jumpFrames[2] = getFrame(560);

	launchFrames[0] = getFrame(962);
	launchFrames[1] = getFrame(964);
	launchFrames[2] = getFrame(967);

	groundedFrame = getFrame(973);
}

TestChar::~TestChar()
{

}

sf::IntRect TestChar::getFrame(int frameNum)
{
	int frameCounter = frameNum;

	int xResolution = 8015;
	int yResolution = 6902;
	int xSize = 229;
	int ySize = 238;
	int yMargin = 16;

	int xCels = 35;
	int yCels = 29;

	int xFrame = 0;
	int yFrame = 0;

	while (frameCounter >= xCels) {
		frameCounter -= xCels;
		yFrame++;
	}

	xFrame = frameCounter;

	return sf::IntRect((xFrame * xSize), (yFrame * ySize), xSize, ySize - yMargin);
}

Animation TestChar::formAnimation(int firstFrame, int length)
{
	Animation temp;

	for (int i = 0; i < length; i++) {
		temp.addFrame(getFrame(i + firstFrame));
	}

	return temp;
}
