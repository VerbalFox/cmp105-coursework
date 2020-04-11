#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Character.h"
#include "TestChar.h"

static class GameManager
{
private:
	Character* characters[2] = {nullptr, nullptr};
	sf::View gameCamera;

public:
	GameManager();
	~GameManager();
	void positionCamera();

	sf::View* getCamera();

	void initialiseCharacters();

	//Returns the first character if charNum = 0, and the second if charNum = 1
	Character* getCharacter(int charNum);

	void startRound();
	void roundEnd();
};