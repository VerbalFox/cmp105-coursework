#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	//Set to true by default, I don't want that.
	socket.setBlocking(false);
}

NetworkManager::~NetworkManager()
{
	socket.unbind();
}

bool NetworkManager::getIsServer()
{
	return isServer;
}

void NetworkManager::setup()
{
	//Unintuitive setup for a multiplayer game, but this works fairly well and I didn't have time to finish the experiment.
	while (true) {
		std::cout << "Type (0) for client, (1) for server." << std::endl;
		if (std::cin >> isServer) {
			std::cout << ((isServer) ? "Server" : "Client") << std::endl;
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	while (true) {
		std::cout << "Type in the IP address you want to connect to." << std::endl;
		if (std::cin >> opponentIpAddress) {
			std::cout << opponentIpAddress.toString() << std::endl;
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	//Uncommon port to use, should be fine.
	socket.bind(55001);
}

void NetworkManager::setNetworkController(NetworkController* netCon)
{
	opponentController = netCon;
}

//I didn't write most of *<this code>. Needed a way to package a deque for sending in a packet.
//This was originally for sending a vector since this wasn't a popular enough issue for me to find a solution for.
//The code was easily adaptable. (Referenced in my report)
sf::Packet& operator <<(sf::Packet& Packet, const std::deque<InputFrame>& Q)
{
	Packet << Q.size();
	for (int i = 0; i < Q.size(); i++)
	{
		Packet << static_cast<sf::Int8>(Q[i].attack) << static_cast<sf::Int8>(Q[i].direction);
	}
	return Packet;
}

sf::Packet& operator >>(sf::Packet& Packet, std::deque<InputFrame>& Q)
{
	size_t size = 0;
	Packet >> size;

	//My understanding of this is rough. Looks to be getting the size and then each element from the packet, but I don't know how it does this.
	for (int i = 0; i < size; i++)
	{
		InputFrame tempFrame;
		sf::Int8 attackVal;
		sf::Int8 directionVal;
		Packet >> attackVal >> directionVal;
		tempFrame.attack = static_cast<AttackButton>(attackVal);
		tempFrame.direction = static_cast<Direction>(directionVal);
		Q.push_back(tempFrame);
	}
	return Packet;
}
//</this code>

void NetworkManager::sendAndRecieveInputQueues(sf::Uint32 currentTimestamp, std::deque<InputFrame> frameDelayBuffer)
{
	//Create and send a packet with the timestamp and input queue.
	sf::Packet sentPacket;
	sentPacket << currentTimestamp << frameDelayBuffer;
	socket.send(sentPacket, opponentIpAddress, 55001);

	//Prepare to recieve the packet.
	sf::Packet recievedPacket;
	sf::IpAddress address;
	unsigned short port;

	//If a packet hasn't been recieved in 6 frames, stall until one does arrive.
	if (framesSincePacketRecieved >= 6) {
		socket.setBlocking(true);
	}

	//If a packet arrived, check the contents and adjust them accordingly.
	if (socket.receive(recievedPacket, address, port) == sf::Socket::Status::Done) {
		sf::Uint32 packetTimeStamp = {};
		std::deque<InputFrame> opponentInputDelayBuffer;
		recievedPacket >> packetTimeStamp >> opponentInputDelayBuffer;

		//Check if packet recieved is latest packet.
		if (lastPacketTimestampRecieved < packetTimeStamp) {
			lastPacketTimestampRecieved = packetTimeStamp;

			//Slice the input queue based on the timestamp difference. I think my failure to sync the timestamps on both clients is why so much desync is present in testing.
			for (int i = 0; i < (currentTimestamp - packetTimeStamp); i++) {
				opponentInputDelayBuffer.pop_front();
			}
		}

		opponentController->setInputQueue(opponentInputDelayBuffer);

		framesSincePacketRecieved = 0;
	}
	else {
		framesSincePacketRecieved++;
	}

	//Just in case it was set to true earlier.
	socket.setBlocking(false);
}