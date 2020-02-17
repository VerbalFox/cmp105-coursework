#pragma once
#include <SFML/Graphics.hpp>
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
	Character* getCharacter(int);

	void startRound();
	void roundEnd();
};