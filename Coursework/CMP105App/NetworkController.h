#pragma once
#include "SFML/Network.hpp"
#include "InputFrame.h"
#include <iostream>

class NetworkController
{
	sf::UdpSocket socket;
	bool isServer;

public:
	NetworkController();
	void setup();
	InputFrame playFrame(sf::Uint32 timestamp);
};