#pragma once
#include "InputFrame.h"
#include "Framework/Input.h"

class Controller
{
protected:
	InputFrame inputBuffer[10];
	Input* input;
public:
	virtual void setInput(Input*);
	virtual InputFrame frameDecision();
};