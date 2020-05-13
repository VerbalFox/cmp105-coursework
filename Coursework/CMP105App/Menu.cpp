#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameManager* gm, GameState* gs, AudioManager* am)
{
	window = hwnd;
	input = in;
	gameState = gs;
	gameManager = gm;
	audioManager = am;

	uiManager.setWindow(window);
	uiManager.setInput(input);

	displayMainMenu();

	audioManager->stopAllMusic();
	audioManager->playMusicbyName("menu");
}

Menu::~Menu()
{

}

// handle user input
void Menu::handleInput()
{

}

// Update game objects
void Menu::update()
{
	uiManager.update();
}

// Render level
void Menu::render()
{
	beginDraw();
	uiManager.draw();
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to black.
void Menu::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Menu::endDraw()
{
	window->display();
}

void Menu::toLocalGame()
{
	gameManager->setupPVPGame();
	gameState->setCurrentState(State::LEVEL);
}

void Menu::toNetworkedGame()
{
	gameManager->setupNetworkGame();
	gameState->setCurrentState(State::LEVEL);
}

void Menu::displayMainMenu()
{
	uiManager.clearElements();

	//Took me several days to figure out how easy function pointers are to use.
	//It was the fact that member functions secretly take in a parameter they don't mention which is a pointer to an instance they can run off of.
	//Binding them lets me treat them like voids with no parameters when handed off to the buttons. Really pretty code.
	uiManager.addButton(ElementID::none, 10, 10, 35, 20, std::bind(&Menu::toLocalGame, this));
	uiManager.addButton(ElementID::none, 10, 40, 80, 20, std::bind(&Menu::toNetworkedGame, this));
	uiManager.addButton(ElementID::none, 55, 10, 35, 20, std::bind(&Menu::displayOptions, this));

	//Text is given ElementIDs so I can change their content dynamically with the setTextStringById function.
	uiManager.addText(ElementID::menuLocal, 10, 10, 35, 20);
	uiManager.addText(ElementID::menuNetworked, 10, 40, 80, 20);
	uiManager.addText(ElementID::menuOptions, 55, 10, 35, 20);

	uiManager.setTextStringById(ElementID::menuLocal, "Local");
	uiManager.setTextStringById(ElementID::menuNetworked, "Multiplayer (Experimental)");
	uiManager.setTextStringById(ElementID::menuOptions, "Options");

	uiManager.addText(ElementID::ipText, 10, 70, 80, 20);
	uiManager.setTextStringById(ElementID::ipText, sf::IpAddress::getPublicAddress(sf::seconds(10)).toString());
}

void Menu::displayOptions()
{
	uiManager.clearElements();

	//Volume adjusting buttons. Made so much easier with function pointers. Lot more readable too.
	uiManager.addButton(ElementID::none, 5, 20, 16, 9, std::bind(&Menu::decreaseVolume, this));
	uiManager.addText(ElementID::volume, 20, 20, 16, 9);
	uiManager.setTextStringById(ElementID::volume, std::to_string(static_cast<int>(std::round(audioManager->getMusic()->getVolume()))));
	uiManager.addButton(ElementID::none, 35, 20, 16, 9, std::bind(&Menu::increaseVolume, this));

	uiManager.addText(ElementID::volumeText, 5, 10, 16, 10);
	uiManager.setTextStringById(ElementID::volumeText, "Volume - ");

	uiManager.addButton(ElementID::none, 5, 85, 90, 10, std::bind(&Menu::displayMainMenu, this));
	uiManager.addText(ElementID::menuMain, 5, 85, 90, 10);
	uiManager.setTextStringById(ElementID::menuMain, "Back");

	uiManager.addButton(ElementID::none, 5, 50, 30, 20, std::bind(&Menu::displayControls, this));
	uiManager.addText(ElementID::menuShowControls, 5, 50, 30, 20);
	uiManager.setTextStringById(ElementID::menuShowControls, "Controls");
}

void Menu::displayControls()
{
	uiManager.clearElements();

	uiManager.addText(ElementID::menuControlsGeneric, 5, 10, 40, 90);
	uiManager.setTextStringById(ElementID::menuControlsGeneric, "Controls - \n\nDirectional \n- \nP1 = WASD\nP2 = Arrows \nAttack Buttons (1, 2, 3, 4) \n- \nP1 = FTGH\nP2 = Numpad(1, 5, 2, 3)\n\nPress P to pause\n(Doesn't work in multiplayer)");

	uiManager.addText(ElementID::menuControlsMoves, 50, 5, 40, 90);
	uiManager.setTextStringById(ElementID::menuControlsMoves, "Moves (Facing Right) - \n\n Jab (Idle) - (1) \n Dash (Running) - (Right - 1) \n Jump Kick (Jumping) - (3) \n Crouch Jab (Crouching) - (Down - 1)");

	uiManager.addButton(ElementID::none, 5, 85, 90, 10, std::bind(&Menu::displayMainMenu, this));
	uiManager.addText(ElementID::menuMain, 5, 85, 90, 10);
	uiManager.setTextStringById(ElementID::menuMain, "Back");
}

void Menu::decreaseVolume()
{
	audioManager->getMusic()->setVolume(audioManager->getMusic()->getVolume() - 5);
	audioManager->getSound("punch")->setVolume(audioManager->getSound("punch")->getVolume() - 5);
	uiManager.setTextStringById(ElementID::volume, std::to_string(static_cast<int>(std::round(audioManager->getMusic()->getVolume()))));
}

void Menu::increaseVolume()
{
	audioManager->getMusic()->setVolume(audioManager->getMusic()->getVolume() + 5);
	audioManager->getSound("punch")->setVolume(audioManager->getSound("punch")->getVolume() + 5);
	uiManager.setTextStringById(ElementID::volume, std::to_string(static_cast<int>(std::round(audioManager->getMusic()->getVolume()))));
}
