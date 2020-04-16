#include "Controller.h"

Controller::Controller()
{
	inputBuffer.resize(10, InputFrame());
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

std::deque<InputFrame> Controller::getInputBuffer()
{
	return inputBuffer;
}
