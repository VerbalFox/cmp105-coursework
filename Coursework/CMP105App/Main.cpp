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
#include "Framework/Input.h"

#include <Windows.h>
#include <chrono>

#include <ctime>

#include <iostream>

//Thread to make sure that the game runs at 60 times per second, while letting the game loop run as many times as it can for other scenes, namely the menu. 
//Also, this lets render be called as many times as it can also.

void gameThread(Level* lev, sf::RenderWindow &wi, GameState &gs, bool &canRen) {
	while (wi.isOpen() && gs.getCurrentState() == State::LEVEL) {
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		//Making sure that render is not called while the level is potentially updating anything.
		canRen = false;
		lev->handleInput();
		lev->update();
		canRen = true;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		//Timing how long handleInput and Update take to run, and taking that away from 1/60 of a second, before sleeping for that amount of time. 
		//This should mean this thread runs as close to 60 times per sec as it can.
		auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::microseconds((1000000 / 60) - time));
	}
}

int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Untitled Fighting Game");

	// Initialise input and level objects.
	Input input;

	GameState gs;

	//Really shouldn't have created this here. Probably would've been better to have made this under level, but menu uses it for setup.
	GameManager gm(&input, &gs);

	//To keep track of transitions.
	State lastLoopState = State::MENU;

	//Setup and add audio files to AudioManager.
	AudioManager am;
	am.addMusic("sfx/menu.ogg", "menu");
	am.addMusic("sfx/game.ogg", "game");
	am.addMusic("sfx/gameFinal.ogg", "gameFinal");
	am.addSound("sfx/punch3.ogg", "punch");

	gs.setCurrentState(State::MENU);
	
	Menu* menu = new Menu(&window, &input, &gm, &gs, &am);
	Level* level = nullptr;
	std::thread* t1 = nullptr;

	//To make sure that render is not called while update or handleInput are being run.
	bool canRender = false;

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
		
		if (gs.getCurrentState() != lastLoopState) {
			switch (gs.getCurrentState())
			{
			case State::MENU:
				menu = new Menu(&window, &input, &gm, &gs, &am);
				break;
			case State::LEVEL:
				delete menu;
				menu = nullptr;
				break;
			default:
				break;
			}
		}

		lastLoopState = gs.getCurrentState();

		if (gs.getCurrentState() == State::LEVEL) {
			//If thread pointer has nothing at it, and the gameState is level, create a new thread and level and begin running.
			if (t1 == nullptr) {
				//Set canRender to false until handleInput and Update have had a chance to run at least once.
				canRender = false;
				level = new Level(&window, &input, &gm, &gs, &am);
				t1 = new std::thread(gameThread, std::ref(level), std::ref(window), std::ref(gs), std::ref(canRender));
			}
			if (canRender) {
				level->render();
			}
		}
		else {
			//Join the thread back to the main thread and clean the pointers, as well as reallocate them back to null pointers.
			if (t1 != nullptr) {
				t1->join();
				delete t1;
				t1 = nullptr;
				delete level;
				level = nullptr;
			}

			if (gs.getCurrentState() == State::MENU) {
				//A nice simple loop.
				menu->handleInput();
				menu->update();
				menu->render();
			}
		}

		//Don't think I ever made use of deltatime, which I hope doesn't set me back grade wise.
		deltaTime = clock.restart().asSeconds();
	}
}