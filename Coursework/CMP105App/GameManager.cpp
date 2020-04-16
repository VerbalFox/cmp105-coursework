#include "GameManager.h"

GameManager::GameManager()
{
	for (int i = 0; i < 2; i++) {
		characters[i] = new TestChar();
		characters[i]->setPlayerNumber(i + 1);

		if (i == 1) {
			characters[i]->flip();
		}
	}

	networkManager->setup();

	roundEnded = false;
}

GameManager::~GameManager()
{
	for (int i = 0; i < 2; i++) {
		delete characters[i];
	}
}

void GameManager::positionCamera()
{
	float xSmoothed = 
		gameCamera.getCenter().x + .1 * 
		(
		((characters[0]->getPosition().x + static_cast<float>(characters[0]->getSize().x * .5) + characters[1]->getPosition().x + static_cast<float>(characters[1]->getSize().x * .5)) * .5)
			- gameCamera.getCenter().x
		);
	
	gameCamera.setCenter(
		xSmoothed,
		-200
	);
}

void GameManager::update()
{
	frameTimestamp++;

	networkManager->playFrame(frameTimestamp);

	adjustCharacterFlip();

	if (*characters[0]->getHealth() <= 0 && !roundEnded) {
		roundEnded = true;
		cl.restart();
	}
	else if (*characters[1]->getHealth() <= 0 && !roundEnded) {
		roundEnded = true;
		cl.restart();
	}

	if (roundEnded && cl.getElapsedTime().asSeconds() > 5) {
		roundEnd();
	}
}

sf::View * GameManager::getCamera()
{
	return &gameCamera;
}

sf::Uint32 GameManager::getFrameTimestamp()
{
	return frameTimestamp;
}

void GameManager::initialiseCharacters()
{
	for (int i = 0; i < 2; i++) {
		if (characters[i]->isPlayerOne()) {
			characters[i]->setPosition(-300, -200);
		}
		else {
			characters[i]->setPosition(300, -200);
		}
		adjustCharacterFlip();
		characters[i]->setVelocity(sf::Vector2f(0, 0));
		characters[i]->resetCharacter();
	}
}

void GameManager::adjustCharacterFlip()
{
	if (characters[0]->getPosition().x < characters[1]->getPosition().x) {
		characters[0]->setFacingLeft(true);
		characters[1]->setFacingLeft(false);
	}
	else {
		characters[0]->setFacingLeft(false);
		characters[1]->setFacingLeft(true);
	}
}

Character* GameManager::getCharacter(int x)
{
	return characters[x];
}

void GameManager::startRound()
{
	initialiseCharacters();
}

void GameManager::roundEnd()
{
	roundEnded = false;
	startRound();
}
