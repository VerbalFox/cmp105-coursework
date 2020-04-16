// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include <thread>

#include "Level.h"
#include "Menu.h"

#include "GameManager.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"

#include <Windows.h>

void gameThread(Level* panda, sf::RenderWindow &wi, GameState &gs, bool &canRen) {
	sf::Clock cl;
	while (wi.isOpen() && gs.getCurrentState() == State::LEVEL) {
		canRen = false;
		panda->handleInput();
		panda->update();
		canRen = true;
		std::this_thread::sleep_for(std::chrono::microseconds((1000000 / 60) - cl.restart().asMicroseconds()));
	}
}

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "CMP105");

	// Initialise input and level objects.
	Input input;
	GameManager gm;
	GameState gs;
	AudioManager am;

	gs.setCurrentState(State::MENU);
	
	Menu menu(&window, &input, &gs);
	Level* level = nullptr;
	std::thread* t1 = nullptr;

	bool canRender = true;

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				if (t1 != nullptr) {
					t1->join();
				}
				break;
			case sf::Event::Resized:
				gm.getCamera()->setViewport(sf::FloatRect(0, 0, 1, 1));
				gm.getCamera()->setSize((float)event.size.width, (float)event.size.height);
				window.setView(*gm.getCamera());
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}
		
		if (gs.getCurrentState() == State::LEVEL) {
			if (t1 == nullptr) {
				level = new Level(&window, &input, &gm, &gs);
				t1 = new std::thread(gameThread, std::ref(level), std::ref(window), std::ref(gs), std::ref(canRender));
			}
			if (canRender) {
				level->render();
			}
		}
		else {
			if (t1 != nullptr) {
				t1->join();
				delete t1;
				t1 = nullptr;
				delete level;
				level = nullptr;
			}

			if (gs.getCurrentState() == State::MENU) {
				menu.handleInput();
				menu.update();
				menu.render();
			}
		}

		deltaTime = clock.restart().asSeconds();
	}
}