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

sf::View * GameManager::getCamera()
{
	return &gameCamera;
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
	}
}

Character* GameManager::getCharacter(int x)
{
	return characters[x];
}
