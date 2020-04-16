#include "PlayerController.h"

void PlayerController::setInput(Input* in)
{
	input = in;
}

InputFrame PlayerController::frameDecision()
{
	InputFrame temp = InputFrame();

	sf::Keyboard::Key tempDirectionKeys[4] = {
		sf::Keyboard::W,
		sf::Keyboard::A,
		sf::Keyboard::S,
		sf::Keyboard::D,
	};

	sf::Keyboard::Key tempAttackKeys[4] = {
		sf::Keyboard::Left,
		sf::Keyboard::Up,
		sf::Keyboard::Down,
		sf::Keyboard::Right,
	};

	std::bitset<4> dirKeys;
	std::bitset<4> attackKeys;

	for (int i = 0; i < 4; i++) {
		if (input->isKeyDown(tempDirectionKeys[i])) {
			dirKeys[i] = 1;
		}
		if (input->isKeyDown(tempAttackKeys[i])) {
			input->setKeyUp(tempAttackKeys[i]);
			attackKeys[i] = 1;
		}
	}

	unsigned int directionNum = static_cast<unsigned int>(dirKeys.to_ulong());
	unsigned int attackNum = static_cast<unsigned int>(attackKeys.to_ulong());

	switch (directionNum) {
	case 1:
		temp.direction = Direction::up;
		break;
	case 2:
		temp.direction = Direction::left;
		break;
	case 4:
		temp.direction = Direction::down;
		break;
	case 8:
		temp.direction = Direction::right;
		break;
	case 3:
		temp.direction = Direction::upLeft;
		break;
	case 9:
		temp.direction = Direction::upRight;
		break;
	case 6:
		temp.direction = Direction::downLeft;
		break;
	case 12:
		temp.direction = Direction::downRight;
		break;
	default:
		temp.direction = Direction::none;
		break;
	}

	switch (attackNum) {
	case 1:
		temp.attack = AttackButton::b1;
		break;
	case 2:
		temp.attack = AttackButton::b2;
		break;
	case 4:
		temp.attack = AttackButton::b3;
		break;
	case 8:
		temp.attack = AttackButton::b4;
		break;
	default:
		temp.attack = AttackButton::none;
		break;
	}

	if (!inputBuffer[0].Equals(temp)) {
		pushFrameToBuffer(temp);
	}
	return temp;
}