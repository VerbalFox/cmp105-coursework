// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "GameManager.h"
#include <thread>

void gameThread(Level &panda) {
	int i = 0;
	while (i < 300) {
		i++;
		panda.handleInput();
		panda.update();
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 60));
	}
}

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "CMP105");

	// Initialise input and level objects.
	Input input;
	GameManager gm;
	Level level(&window, &input, &gm);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;


	std::thread t1(gameThread, std::ref(level));
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
				t1.join();
				window.close();
				break;
			case sf::Event::Resized:
				gm.getCamera()->setViewport(sf::FloatRect(0, 0, 1, 1));
				gm.getCamera()->setSize((float)event.size.width, (float)event.size.height);
				gm.getCamera()->setCenter(0.f, 0.f);
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

		deltaTime = clock.restart().asSeconds();
		
		level.render();
	}
}