#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameManager* game)
{
	window = hwnd;
	input = in;
	gm = game;

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

	gm->getCharacter(0)->setController(&control);
	gm->getCharacter(1)->setController(&control1);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput()
{

}

// Update game objects
void Level::update()
{
	gm->getCharacter(0)->update();
	gm->getCharacter(1)->update();
	gm->positionCamera();

	for (int i = 0; i < 2; i++) {
		if (Collision::checkBoundingBox(&GameObject(*gm->getCharacter(i)), &floor)) {
			gm->getCharacter(i)->collisionResponse(&floor);
		}
	}

	window->setView(*gm->getCamera());
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(floor);
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