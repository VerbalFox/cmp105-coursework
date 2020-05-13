#include "GameManager.h"

GameManager::GameManager(Input* in, GameState* gs)
{
<<<<<<< HEAD
	input = in;
	gameState = gs;
=======
	for (int i = 0; i < 2; i++) {
		characters[i] = new TestChar();
		characters[i]->setPlayerNumber(i + 1);

		if (i == 1) {
			characters[i]->flip();
		}
	}

	//networkManager->setup();

	roundEnded = false;
>>>>>>> parent of 8812eb3... Code compiles, network module now working
}

GameManager::~GameManager()
{
	//Just in case. This should go unused given the GameManager is declared directly in the scope of main.
	for (int i = 0; i < 2; i++) {
		delete characters[i];
	}

	for (int i = 0; i < 2; i++) {
		delete controllers[i];
	}
}

void GameManager::positionCamera()
{
	//Camera lerping.
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

<<<<<<< HEAD
=======
	//networkManager->playFrame(frameTimestamp);

>>>>>>> parent of 8812eb3... Code compiles, network module now working
	adjustCharacterFlip();

	//If time is up, check for a winner.
	if (roundLength - roundTimer.getElapsedTime().asSeconds() <= 0 && !roundEnded) {
		if (*characters[0]->getHealth() == *characters[1]->getHealth()) {
			characters[0]->incrementRoundsWon();
			characters[1]->incrementRoundsWon();
		}
		else if (*characters[0]->getHealth() > *characters[1]->getHealth()) {
			characters[0]->incrementRoundsWon();
		}
		else if (*characters[0]->getHealth() < * characters[1]->getHealth()) {
			characters[1]->incrementRoundsWon();
		}

		checkForWinner();
		roundEnded = true;
		roundEndTimer.restart();
	}

	//If health of both players hits 0 in the same frame, give both players the win.
	if (*characters[0]->getHealth() <= 0 && *characters[1]->getHealth() <= 0 && !roundEnded) {
		characters[0]->incrementRoundsWon();
		characters[1]->incrementRoundsWon();

		checkForWinner();
		roundEnded = true;
		roundEndTimer.restart();
	}
	//Else, if one of the players health hits 0, give the other player the win.
	else if (*characters[0]->getHealth() <= 0 && !roundEnded) {
		characters[1]->incrementRoundsWon();

		checkForWinner();
		roundEnded = true;
		roundEndTimer.restart();
	}
	else if (*characters[1]->getHealth() <= 0 && !roundEnded) {
		characters[0]->incrementRoundsWon();

		checkForWinner();
		roundEnded = true;
		roundEndTimer.restart();
	}

	//If end of round timer hits 5 seconds, move onto the next round.
	if (roundEnded && roundEndTimer.getElapsedTime().asSeconds() > 8) {
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
	//Inform the characters of which way they should be facing.
	if (characters[0]->getPosition().x < characters[1]->getPosition().x) {
		characters[0]->setFacingLeft(true);
		characters[1]->setFacingLeft(false);
	}
	else {
		characters[0]->setFacingLeft(false);
		characters[1]->setFacingLeft(true);
	}
}

void GameManager::setupPVPGame()
{
	for (int i = 0; i < 2; i++) {
		//This could be any derived character class. Only had time to make one.
		characters[i] = new TestChar();
		characters[i]->setPlayerNumber(i + 1);

		if (i == 1) {
			characters[i]->flip();
		}
	}

	controllers[0] = new PlayerController(true);
	controllers[1] = new PlayerController(false);
	controllers[0]->setInput(input);
	controllers[1]->setInput(input);
	characters[0]->setController(controllers[0]);
	characters[1]->setController(controllers[1]);

	roundEnded = false;
}

void GameManager::setupNetworkGame()
{
	networkManager = new NetworkManager();

	for (int i = 0; i < 2; i++) {
		characters[i] = new TestChar();
		characters[i]->setPlayerNumber(i + 1);

		if (i == 1) {
			characters[i]->flip();
		}
	}

	networkManager->setup();

	//Server and clients are mainly used to determine which player each client is controlling.
	if (networkManager->getIsServer()) {
		controllers[0] = new PlayerController(true);
		characters[0]->setFillColor(sf::Color::Red);
		controllers[1] = new NetworkController();
		networkManager->setNetworkController(dynamic_cast<NetworkController*>(controllers[1]));
		controllers[0]->setInput(input);
	}
	else {
		controllers[0] = new NetworkController();
		characters[1]->setFillColor(sf::Color::Red);
		controllers[1] = new PlayerController(true);
		networkManager->setNetworkController(dynamic_cast<NetworkController*>(controllers[0]));
		controllers[1]->setInput(input);
	}

	for (int i = 0; i < 2; i++)
	{
		controllers[i]->setNetworkedGame(true);
	}

	characters[0]->setController(controllers[0]);
	characters[1]->setController(controllers[1]);

	roundEnded = false;
}

void GameManager::cleanGameManager()
{
	//Delete the characters and controllers, and set all the important variables back to their defaults.
	for (size_t i = 0; i < characters.size(); i++)
	{
		delete characters[i];
		characters[i] = nullptr;
	}

	for (size_t i = 0; i < controllers.size(); i++)
	{
		delete controllers[i];
		controllers[i] = nullptr;
	}

	gameOver = false;
	frameTimestamp = 0;
	delete networkManager;
	networkManager = nullptr;
}

int GameManager::getRoundTimer()
{
	return roundLength - roundTimer.getElapsedTime().asSeconds();
}

int GameManager::getRoundGoal()
{
	return roundGoal;
}

NetworkManager* GameManager::getNetworkManager()
{
	return networkManager;
}

Character* GameManager::getCharacter(int charNum)
{
	return characters[charNum];
}

Controller* GameManager::getController(int controllerNum)
{
	return controllers[controllerNum];
}

void GameManager::startRound()
{
	//Set up character positions and restart round timer.
	initialiseCharacters();
	roundTimer.restart();
}

void GameManager::roundEnd()
{
	//If game isn't over, new round. Else, back to the main menu.
	if (!gameOver) {
		roundEnded = false;
		startRound();
	}
	else {
		gameState->setCurrentState(State::MENU);
	}
}

void GameManager::checkForWinner()
{
	//Check if the number of rounds won is greater than or equal to the round goal. If so, blend a gold colour into the characters as an indictation of victory.
	if (characters[0]->getRoundsWon() >= roundGoal && characters[1]->getRoundsWon() >= roundGoal) {
		characters[0]->setFillColor(sf::Color(218, 165, 32));
		characters[1]->setFillColor(sf::Color(218, 165, 32));
		gameOver = true;
	}
	else if (characters[0]->getRoundsWon() >= roundGoal) {
		characters[0]->setFillColor(sf::Color(218, 165, 32));
		gameOver = true;
	}
	else if (characters[1]->getRoundsWon() >= roundGoal) {
		characters[1]->setFillColor(sf::Color(218, 165, 32));
		gameOver = true;
	}
}
