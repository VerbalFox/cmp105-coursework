#include "NetworkController.h"

void NetworkController::setFrameInput(sf::Uint32 timestamp, InputFrame input)
{
	frameTimestampRecieved = timestamp;
	inputRecieved = input;
}

InputFrame NetworkController::frameDecision()
{
	//Take latest input from delay queue.
	if (inputDelayQueue.size() > 0) {
		InputFrame temp = inputDelayQueue.front();
		inputDelayQueue.pop_front();
		pushFrameToBuffer(temp);

		return temp;
	}
	else {
		return InputFrame();
	}
}