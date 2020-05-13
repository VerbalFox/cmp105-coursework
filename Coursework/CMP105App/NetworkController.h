#pragma once
#include "Controller.h"
#include <SFML/Main.hpp>

class NetworkController :
	public Controller
{
	sf::Uint32 frameTimestampRecieved = 0;
	InputFrame inputRecieved = InputFrame();

public:
	void setFrameInput(sf::Uint32 timestamp, InputFrame input);
	InputFrame frameDecision() override;
};