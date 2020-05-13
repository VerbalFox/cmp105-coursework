#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameManager* game, GameState* gs, AudioManager* am)
{
	//Pointer allocation.
	window = hwnd;
	input = in;
	gm = game;
	gameState = gs;
	audioManager = am;

	//Floor setup, probably a more elegant way of doing this.
	floor.setCollisionBox(0, 0, INT_MAX, INT_MAX);
	floor.setFillColor(sf::Color::Magenta);
	floor.setSize(sf::Vector2f(INT_MAX, INT_MAX));
	floor.setPosition(-100000, 0);
	floor.setType(ObjectType::floor);

	//GameManager camera setup.
	gm->getCamera()->setViewport(sf::FloatRect(0, 0, 1, 1));
	gm->getCamera()->setSize(window->getSize().x, window->getSize().y);
	gm->getCamera()->setCenter(0.f, 0.f);

	//Character positioning.
	gm->initialiseCharacters();

	window->setView(*gm->getCamera());

	gm->getCharacter(0)->resetCharacter();
	gm->getCharacter(1)->resetCharacter();

	//UIManager setup.
	uiManager.setWindow(window);
	uiManager.setInput(input);

	//Sliders that display health/max health as a bar.
	uiManager.addSlider(ElementID::none, 5, 5, 40, 5, sf::Color::Blue, sf::Color::Cyan, gm->getCharacter(0)->getMaxHealth(), gm->getCharacter(0)->getHealth());
	uiManager.addSlider(ElementID::none, 55, 5, 40, 5, sf::Color::Blue, sf::Color::Cyan, gm->getCharacter(1)->getMaxHealth(), gm->getCharacter(1)->getHealth());

	uiManager.addText(ElementID::player1RoundCounter, 5, 15, 40, 5);
	uiManager.addText(ElementID::player2RoundCounter, 55, 15, 40, 5);

	uiManager.addText(ElementID::pausedText, 5, 40, 90, 20);
	uiManager.addText(ElementID::gameTimer, 45, 5, 10, 5);

	//Game tends to crash or otherwise act irratically when the strings aren't assigned values. Absolutely no idea why, they're assigned values in their constructor.
	uiManager.setTextStringById(ElementID::player1RoundCounter, "");
	uiManager.setTextStringById(ElementID::player2RoundCounter, "");

	uiManager.setTextStringById(ElementID::pausedText, "");

	uiManager.setTextStringById(ElementID::gameTimer, "60");

	audioManager->stopAllMusic();
	audioManager->playMusicbyName("game");

	gm->startRound();
}

Level::~Level()
{
	//About the safest place to run this. I don't know nearly enough about threads.
	gm->cleanGameManager();
}

// handle user input
void Level::handleInput()
{
	//If paused and requested, back to the main menu. Seemed like the best way to minimise misinput. Had an issue like that in testing.
	if (input->isKeyDown(sf::Keyboard::Escape) && isPaused) {
		isPaused = true;
		gameState->setCurrentState(State::MENU);
	}
	
	//Preventing pausing when the game is networked for testing. Don't think I'll make multiplayer fully functional. Isn't a bad attempt though.
	if (gm->getNetworkManager() == nullptr) {
		if (input->isKeyDown(sf::Keyboard::P)) {
			input->setKeyUp(sf::Keyboard::P);
			if (isPaused) {
				isPaused = false;
				uiManager.setTextStringById(ElementID::pausedText, "");
			}
			else {
				isPaused = true;
				uiManager.setTextStringById(ElementID::pausedText, "Paused\nPress ESC to return to the main menu");
			}
		}
	}
}

// Update game objects
void Level::update()
{
	if (isPaused && gm->getNetworkManager() == nullptr) {
		//Do absolutely nothing. This wasn't the best way to write this logic, I just found it more readable.
	}
	else {
		gm->update();

		uiManager.setTextStringById(ElementID::gameTimer, std::to_string(gm->getRoundTimer()));

		uiManager.setTextStringById(ElementID::player1RoundCounter, std::to_string(gm->getCharacter(0)->getRoundsWon()) + "/" + std::to_string(gm->getRoundGoal()));
		uiManager.setTextStringById(ElementID::player2RoundCounter, std::to_string(gm->getCharacter(1)->getRoundsWon()) + "/" + std::to_string(gm->getRoundGoal()));

		if (gm->getNetworkManager() != nullptr) {
			//If game is networked, handle local input, send and recieve packets and update input delay queues accordingly, then update the network client input.
			if (gm->getNetworkManager()->getIsServer()) {
				gm->getCharacter(0)->handleInput();
				gm->getNetworkManager()->sendAndRecieveInputQueues(gm->getFrameTimestamp(), gm->getController(0)->getInputQueue());
				gm->getCharacter(1)->handleInput();
			}
			else {
				gm->getCharacter(1)->handleInput();
				gm->getNetworkManager()->sendAndRecieveInputQueues(gm->getFrameTimestamp(), gm->getController(1)->getInputQueue());
				gm->getCharacter(0)->handleInput();
			}
		}
		else {
			//The local, friendlier way of doing things.
			gm->getCharacter(0)->handleInput();
			gm->getCharacter(1)->handleInput();
		}

		gm->getCharacter(0)->update();
		gm->getCharacter(1)->update();

		gm->positionCamera();

		for (int i = 0; i < 2; i++) {
			//A messy solution for several collision boxes that I am ashamed to have written and couldn't think of a better solution for. It's not totally horrific, but still.
			if (Collision::checkBoundingBox(gm->getCharacter(i)->getHighHitbox(), gm->getCharacter((i - 1) * -1)->getHighHitbox())) {
				gm->getCharacter((i - 1) * -1)->collisionResponse(gm->getCharacter(i));
			}

			if (Collision::checkBoundingBox(gm->getCharacter(i)->getLowHitbox(), gm->getCharacter((i - 1) * -1)->getLowHitbox())) {
				gm->getCharacter((i - 1) * -1)->collisionResponse(gm->getCharacter(i));
			}

			if (Collision::checkBoundingBox(gm->getCharacter(i)->getLowHitbox(), gm->getCharacter((i - 1) * -1)->getHighHitbox())) {
				gm->getCharacter((i - 1) * -1)->collisionResponse(gm->getCharacter(i));
			}

			if (Collision::checkBoundingBox(gm->getCharacter(i)->getLowHitbox(), floor.getCollisionBox())) {
				gm->getCharacter(i)->collisionResponse(&floor);
			}

			if (Collision::checkBoundingBox(gm->getCharacter((i - 1) * -1)->getMoveRect(), gm->getCharacter(i)->getHighHitbox()) ||
				Collision::checkBoundingBox(gm->getCharacter((i - 1) * -1)->getMoveRect(), gm->getCharacter(i)->getLowHitbox())
				) {
				if (gm->getCharacter((i - 1) * -1)->getCurrentMove() != nullptr &&
					gm->getCharacter((i - 1) * -1)->getCurrentMove()->getMoveState() == MoveState::active) {
					if (!gm->getCharacter((i - 1) * -1)->getCurrentMove()->getMoveDamaged()) {
						audioManager->playSoundbyName("punch");
					}
					gm->getCharacter(i)->hitResponse(gm->getCharacter((i - 1) * -1)->getCurrentMove());
				}
			}

		}
	}

	window->setView(*gm->getCamera());
	uiManager.update();
}

// Render level
void Level::render()
{
	beginDraw();

	//Only draw the UI if paused. There wasn't much of a reason for me to do this, but I wanted to make certain that the text would be readable.
	if (!isPaused) {
		window->draw(floor);

		window->draw(*gm->getCharacter(0));
		window->draw(*gm->getCharacter(1));
	}

	uiManager.draw();

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to black.
void Level::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}