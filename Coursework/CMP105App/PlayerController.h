#pragma once
#include "Controller.h"
#include <SFML\Window\Keyboard.hpp>
#include <bitset>

class PlayerController :
	public Controller
{
	Input* input;
public:
	void setInput(Input*);
	InputFrame frameDecision() override;
};