#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameManager* game, GameState* gs)
{
	window = hwnd;
	input = in;
	gm = game;
	gameState = gs;

	floor.setCollisionBox(0, 0, INT_MAX, INT_MAX);
	floor.setFillColor(sf::Color::Red);
	floor.setSize(sf::Vector2f(INT_MAX, INT_MAX));
	floor.setPosition(-100000, 0);
	floor.setType(ObjectType::floor);

	gm->getCamera()->setViewport(sf::FloatRect(0, 0, 1, 1));
	gm->getCamera()->setSize(window->getSize().x, window->getSize().y);
	gm->getCamera()->setCenter(0.f, 0.f);

	gm->initialiseCharacters();

	window->setView(*gm->getCamera());

	control.setInput(in);
	control1.setInput(in);

	gm->getCharacter(0)->setController(&control);
	gm->getCharacter(1)->setController(&control1);

	uiManager.setWindow(window);
	uiManager.setInput(input);

	uiManager.addSlider(5, 5, 40, 5, sf::Color::Blue, sf::Color::Cyan, gm->getCharacter(0)->getMaxHealth(), gm->getCharacter(0)->getHealth());
	uiManager.addSlider(55, 5, 40, 5, sf::Color::Blue, sf::Color::Cyan, gm->getCharacter(1)->getMaxHealth(), gm->getCharacter(1)->getHealth());
}

Level::~Level()
{

}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Q)) {
		gameState->setCurrentState(State::MENU);
	}
}

// Update game objects
void Level::update()
{
	gm->getCharacter(0)->update();
	gm->getCharacter(1)->update();
	gm->positionCamera();

	for (int i = 0; i < 2; i++) {

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

		if (Collision::checkBoundingBox(gm->getCharacter((i - 1) * -1)->getMoveRect(), gm->getCharacter(i)->getHighHitbox())) {
			if (gm->getCharacter((i - 1) * -1)->getCurrentMove() != nullptr && gm->getCharacter((i - 1) * -1)->getCurrentMove()->getMoveState() == MoveState::active) {
				gm->getCharacter(i)->hitResponse(gm->getCharacter((i - 1) * -1)->getCurrentMove());
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
	window->draw(floor);

	std::vector<sf::RectangleShape> debugRectangles = gm->getCharacter(0)->getDebugMoveRects();
	for (std::vector<sf::RectangleShape>::iterator it = debugRectangles.begin(); it != debugRectangles.end(); ++it) {
		window->draw(*it);
	}

	std::vector<sf::RectangleShape> debugRectangles1 = gm->getCharacter(1)->getDebugMoveRects();
	for (std::vector<sf::RectangleShape>::iterator it = debugRectangles1.begin(); it != debugRectangles1.end(); ++it) {
		window->draw(*it);
	}

	uiManager.draw();

	window->draw(*gm->getCharacter(0));
	window->draw(*gm->getCharacter(1));
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