#pragma once
#include "Controller.h"
#include <SFML\Window\Keyboard.hpp>
#include <bitset>
#include <array>

class PlayerController :
	public Controller
{
	std::array<sf::Keyboard::Key, 4> tempDirectionKeys = {};
	std::array<sf::Keyboard::Key, 4> tempAttackKeys = {};

public:
	PlayerController(bool isPlayerOne);
	InputFrame frameDecision() override;
};