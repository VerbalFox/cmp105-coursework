#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>

#include "Framework/GameState.h"

#include "Character.h"
#include "TestChar.h"

<<<<<<< HEAD
#include "NetworkManager.h"

#include "PlayerController.h"
#include "NetworkController.h"
#include "Framework/Input.h"
=======
//#include "NetworkManager.h"
>>>>>>> parent of 8812eb3... Code compiles, network module now working

class GameManager
{
private:
	std::array<Character*, 2> characters = {nullptr, nullptr};
	std::array<Controller*, 2> controllers = {nullptr, nullptr};
	sf::View gameCamera;
	bool roundEnded = true;
	bool gameOver = false;

	//These timers should really be their own timers based on the constant frame rate for the sake of online play. Didn't have time. Works just fine for local play.
	sf::Clock roundEndTimer;
	sf::Clock roundTimer;

	int roundLength = 60;
	int roundGoal = 3;

	//This timestamp will overflow after about 2.2 years of constant play. Round timers and limits make that impossible though.
	sf::Uint32 frameTimestamp = 0;
<<<<<<< HEAD
	
	Input* input;
	GameState* gameState;

	//Since the NM is done as a pointer, I can simply use whether it exists as an indictation of whether the match is online or not, and run the appropriate code.
	NetworkManager* networkManager = nullptr;
=======

	//NetworkManager* networkManager = new NetworkManager();
>>>>>>> parent of 8812eb3... Code compiles, network module now working

public:
	GameManager(Input* in, GameState* gs);
	~GameManager();
	//Position camera using lerping and their centre point.
	void positionCamera();
	void update();

	sf::View* getCamera();
	sf::Uint32 getFrameTimestamp();

	void initialiseCharacters();
	void adjustCharacterFlip();

	void setupPVPGame();
	void setupNetworkGame();

	void cleanGameManager();

	int getRoundTimer();
	int getRoundGoal();

	NetworkManager* getNetworkManager();

	//Returns the first character if charNum = 0, and the second if charNum = 1
	Character* getCharacter(int charNum);

	//Returns the first controller if controllerNum = 0, and the second if controllerNum = 1
	Controller* getController(int controllerNum);

	void startRound();
	void roundEnd();

	void checkForWinner();
};