#include "TestChar.h"

TestChar::TestChar()
{
	//Generic variable setup.
	maxHealth = 100;
	health = maxHealth;
	characterSize = sf::Vector2i(225, 238);
	moveSpeed = 300;
	jumpForce = 550;
	roundsWon = 0;

	setSize(sf::Vector2f(characterSize.x, characterSize.y));
	setCollisionBox(0, 0, characterSize.x, characterSize.y);

	//Texture loading.
	if (charTexture.loadFromFile("gfx/fighter.png")) {
		setTexture(&charTexture);
	}

	std::vector<InputFrame> tempMoveInput;
	InputFrame tempFrame;

	//Left Jab Setup
	tempFrame.direction = Direction::none;
	tempFrame.attack = AttackButton::b1;
	tempMoveInput.push_back(tempFrame);

	lArmJab.setIsProjectileMove(false);
	lArmJab.setMoveInput(tempMoveInput);
	lArmJab.setAnimations(formAnimation(17, 3), formAnimation(20, 1), formAnimation(21, 2));
	lArmJab.setMoveSpeeds(9, 3, 10);
	lArmJab.setDamage(20);
	lArmJab.setHitbox(sf::FloatRect(45, 100, 20, 10));
	lArmJab.setCharVelocity(sf::Vector2f(100, 0));
	lArmJab.setAvailableFromState(CharState::idle);
	lArmJab.setStunnedFrames(10);
	lArmJab.setBlockedFrames(10);

	tempMoveInput.clear();
	moveList.push_back(&lArmJab);

	//Dash Setup
	tempFrame.direction = Direction::right;
	tempFrame.attack = AttackButton::b1;
	tempMoveInput.push_back(tempFrame);

	dash.setIsProjectileMove(false);
	dash.setMoveInput(tempMoveInput);
	dash.setAnimations(formAnimation(456, 4), formAnimation(460, 2), formAnimation(462, 4));
	dash.setMoveSpeeds(12, 6, 18);
	dash.setDamage(34);
	dash.setHitbox(sf::FloatRect(30, 100, 20, 40));
	dash.setCharVelocity(sf::Vector2f(550, 0));
	dash.setAvailableFromState(CharState::running);
	dash.setStunnedFrames(10);
	dash.setBlockedFrames(10);

	tempMoveInput.clear();
	moveList.push_back(&dash);

	//Jump Kick Setup
	tempFrame.direction = Direction::none;
	tempFrame.attack = AttackButton::b3;
	tempMoveInput.push_back(tempFrame);

	jumpKick.setIsProjectileMove(false);
	jumpKick.setMoveInput(tempMoveInput);
	jumpKick.setAnimations(formAnimation(690, 3), formAnimation(693, 2), formAnimation(695, 2));
	jumpKick.setMoveSpeeds(12, 5, 20);
	jumpKick.setDamage(25);
	jumpKick.setHitbox(sf::FloatRect(50, 120, 30, 10));
	jumpKick.setCharVelocity(sf::Vector2f(400, 100));
	jumpKick.setAvailableFromState(CharState::jumping);
	jumpKick.setStunnedFrames(30);
	jumpKick.setBlockedFrames(10);

	tempMoveInput.clear();
	moveList.push_back(&jumpKick);

	//Crouch Jab Setup
	tempFrame.direction = Direction::down;
	tempFrame.attack = AttackButton::b1;
	tempMoveInput.push_back(tempFrame);

	crouchArmJab.setIsProjectileMove(false);
	crouchArmJab.setMoveInput(tempMoveInput);
	crouchArmJab.setAnimations(formAnimation(730, 1), formAnimation(731, 2), formAnimation(733, 2));
	crouchArmJab.setMoveSpeeds(3, 6, 6);
	crouchArmJab.setDamage(18);
	crouchArmJab.setHitbox(sf::FloatRect(45, 150, 20, 10));
	crouchArmJab.setCharVelocity(sf::Vector2f(100, 0));
	crouchArmJab.setAvailableFromState(CharState::crouching);
	crouchArmJab.setStunnedFrames(30);
	crouchArmJab.setBlockedFrames(10);

	tempMoveInput.clear();
	moveList.push_back(&crouchArmJab);

	//Assigning hitboxes.
	highHitbox = sf::FloatRect(-40, 70, 60, 80);
	lowHitbox = sf::FloatRect(-40, 155, 60, 90);

	//Creating generic animations using helper functions. These animations didn't need the speed format change but they still work fine.
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

	//Set the animations I didn't want to loop to no longer loop.
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

	//I did not enjoy writing any of this.
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
