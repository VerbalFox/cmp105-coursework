#pragma once
#include "InputFrame.h"
#include "Framework/Input.h"
#include <deque>
#include <queue>

class Controller
{
protected:
	Input* input;

	//Double sided queue, used for moves with multple input frames.
	std::deque<InputFrame> inputBuffer;
	//Queue for an input delay, used for multiplayer. This could be a queue, but I couldn't figure out a way to send a queue over a packet.
	std::deque<InputFrame> inputDelayQueue;

	bool isNetworkedGame = false;
public:
	Controller();
	void setInput(Input* in);
	virtual InputFrame frameDecision();
	void pushFrameToBuffer(InputFrame frame);

	void setNetworkedGame(bool newIsNetworkedGame);

	std::deque<InputFrame> getInputBuffer();
	std::deque<InputFrame> getInputQueue();
	void setInputQueue(std::deque<InputFrame> newInputDelayQueue);
};