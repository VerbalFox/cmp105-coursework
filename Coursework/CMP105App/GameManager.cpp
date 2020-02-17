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

}

void GameManager::positionCamera()
{
	gameCamera.setCenter((characters[0]->getPosition().x + characters[1]->getPosition().x + characters[1]->getSize().x) * .5, 0);
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
