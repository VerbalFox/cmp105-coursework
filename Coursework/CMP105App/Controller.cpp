#include "Controller.h"

void Controller::setInput(Input* in)
{
	input = in;
}

InputFrame Controller::frameDecision()
{
	return InputFrame();
}
