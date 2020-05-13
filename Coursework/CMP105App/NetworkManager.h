#pragma once
#include "SFML/Network.hpp"
#include "InputFrame.h"
#include "NetworkController.h"
#include <iostream>

class NetworkManager
{
	sf::UdpSocket socket;
	bool isServer = false;
	NetworkController* opponentController = nullptr;

	sf::IpAddress opponentIpAddress;
	sf::Uint32 lastPacketTimestampRecieved = 0;
	short int framesSincePacketRecieved = 0;

public:
	NetworkManager();
	~NetworkManager();
	bool getIsServer();

	void setup();

	void setNetworkController(NetworkController* netCon);
	void sendAndRecieveInputQueues(sf::Uint32 timestamp, std::deque<InputFrame> frameDelayBuffer);
};