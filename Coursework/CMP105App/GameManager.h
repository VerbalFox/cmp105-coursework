#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Character.h"
#include "TestChar.h"

//#include "NetworkManager.h"

static class GameManager
{
private:
	Character* characters[2] = {nullptr, nullptr};
	sf::View gameCamera;
	bool roundEnded;
	sf::Clock cl;
	sf::Uint32 frameTimestamp = 0;

	//NetworkManager* networkManager = new NetworkManager();

public:
	GameManager();
	~GameManager();
	void positionCamera();
	void update();

	sf::View* getCamera();
	sf::Uint32 getFrameTimestamp();

	void initialiseCharacters();
	void adjustCharacterFlip();

	//Returns the first character if charNum = 0, and the second if charNum = 1
	Character* getCharacter(int charNum);

	void startRound();
	void roundEnd();
};