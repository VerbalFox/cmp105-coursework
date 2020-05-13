#include "PlayerController.h"

PlayerController::PlayerController(bool isPlayerOne)
{
	//Assigning the buttons for different players.
	if (isPlayerOne) {
		tempDirectionKeys = {
			sf::Keyboard::W,
			sf::Keyboard::A,
			sf::Keyboard::S,
			sf::Keyboard::D
		};

		tempAttackKeys = {
			sf::Keyboard::F,
			sf::Keyboard::T,
			sf::Keyboard::G,
			sf::Keyboard::H
		};
	}
	else {
		tempDirectionKeys = {
			sf::Keyboard::Up,
			sf::Keyboard::Left,
			sf::Keyboard::Down,
			sf::Keyboard::Right
		};

		tempAttackKeys = {
			sf::Keyboard::Numpad1,
			sf::Keyboard::Numpad5,
			sf::Keyboard::Numpad2,
			sf::Keyboard::Numpad3
		};
	}
}

InputFrame PlayerController::frameDecision()
{
	InputFrame temp = InputFrame();

	//Doing inputs as bitsets lets me evaulate the results as integers, which gives me full control over the different combinations of inputs since each combination will just be a number.
	std::bitset<4> dirKeys;
	std::bitset<4> attackKeys;

	//Assigning the values to the bitset using the input class.
	for (int i = 0; i < 4; i++) {
		if (input->isKeyDown(tempDirectionKeys[i])) {
			dirKeys[i] = 1;
		}
		if (input->isKeyDown(tempAttackKeys[i])) {
			attackKeys[i] = 1;
		}
	}
	
	//Converting the bitsets to their respective numbers.
	unsigned int directionNum = static_cast<unsigned int>(dirKeys.to_ulong());
	unsigned int attackNum = static_cast<unsigned int>(attackKeys.to_ulong());

	//Turning those numbers into input frames.
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

	//If game isn't networked, push to the buffer and return the current input.
	if (!isNetworkedGame) {
		if (!inputBuffer[0].Equals(temp)) {
			pushFrameToBuffer(temp);
		}
		return temp;
	}
	//If game is networked, push to the queue, then pop from the queue if the right size, push the popped to the buffer and return that.
	else {
		inputDelayQueue.push_back(temp);
		if (inputDelayQueue.size() >= 6) {
			InputFrame tempPopped = inputDelayQueue.front();
			inputDelayQueue.pop_front();
			pushFrameToBuffer(tempPopped);
			return tempPopped;
		}
		else {
			return InputFrame();
		}
	}
	return InputFrame();
}