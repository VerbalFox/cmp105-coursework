#pragma once
#include "InputFrame.h"
#include "Character.h"
class Controller
{
	Character* connectedChar;
	virtual void frameDecision();
};