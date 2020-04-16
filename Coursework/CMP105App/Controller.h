#pragma once
#include "InputFrame.h"
#include "Framework/Input.h"
#include <deque>

class Controller
{
protected:
	std::deque<InputFrame> inputBuffer = {InputFrame()};
public:
	Controller();
	virtual InputFrame frameDecision();
	void pushFrameToBuffer(InputFrame frame);

	std::deque<InputFrame> getInputBuffer();
};