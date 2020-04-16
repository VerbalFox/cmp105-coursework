#include "NetworkController.h"

NetworkController::NetworkController()
{
}

void NetworkController::setup()
{
	std::cout << "Type (0) for client, (1) for server and anything else to break me." << std::endl;
	std::cin >> isServer;

	std::cout << ((isServer) ? "Server" : "Client") << std::endl;

	if (isServer) {
		socket.bind(55001);
	}
	else {
		socket.bind(55002);
	}
}

InputFrame NetworkController::playFrame(sf::Uint32 timestamp)
{
	sf::Packet sentPacket;
	sentPacket << timestamp;
	if (isServer) {
		socket.send(sentPacket, sf::IpAddress::getLocalAddress(), 55002);
	}
	else {
		socket.send(sentPacket, sf::IpAddress::getLocalAddress(), 55001);
	}

	sf::Packet recievedPacket;
	sf::IpAddress address;
	unsigned short port;
	socket.receive(recievedPacket, address, port);

	sf::Uint32 timeStamp = {};
	recievedPacket >> timeStamp;
	std::cout << timeStamp << std::endl;

	return InputFrame();
}