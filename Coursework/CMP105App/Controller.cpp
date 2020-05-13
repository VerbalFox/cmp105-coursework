#include "Controller.h"

Controller::Controller()
{
	inputBuffer.resize(10, InputFrame());
	inputDelayQueue.resize(6, InputFrame());
}

void Controller::setInput(Input* in)
{
	input = in;
}

InputFrame Controller::frameDecision()
{
	return InputFrame();
}

void Controller::pushFrameToBuffer(InputFrame frame)
{
	inputBuffer.push_front(frame);
	inputBuffer.resize(10);
}

void Controller::setNetworkedGame(bool newIsNetworkedGame)
{
	isNetworkedGame = newIsNetworkedGame;
}

std::deque<InputFrame> Controller::getInputBuffer()
{
	return inputBuffer;
}

std::deque<InputFrame> Controller::getInputQueue() {
	return inputDelayQueue;
}

void Controller::setInputQueue(std::deque<InputFrame> newInputDelayQueue)
{
	inputDelayQueue = newInputDelayQueue;
}
