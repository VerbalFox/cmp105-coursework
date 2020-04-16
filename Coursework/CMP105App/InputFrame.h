#pragma once
enum class Direction {
	none,
	right,
	left,
	up,
	down,
	downRight,
	downLeft,
	upRight,
	upLeft
};

enum class AttackButton {
	none,
	b1,
	b2,
	b3,
	b4
};

struct InputFrame {
	Direction direction;
	AttackButton attack;
	InputFrame() {
		this->attack = AttackButton::none;
		this->direction = Direction::none;
	}
	bool Equals(InputFrame inputFr) {
		return (this->direction == inputFr.direction && this->attack == inputFr.attack) ? true : false;
	}
	InputFrame Flipped(InputFrame frame) {
		InputFrame tempFr = frame;
		switch (tempFr.direction)
		{
		case Direction::upLeft:
			tempFr.direction = Direction::upRight;
			break;
		case Direction::downLeft:
			tempFr.direction = Direction::downRight;
			break;
		case Direction::left:
			tempFr.direction = Direction::right;
			break;
		case Direction::upRight:
			tempFr.direction = Direction::upLeft;
			break;
		case Direction::downRight:
			tempFr.direction = Direction::downLeft;
			break;
		case Direction::right:
			tempFr.direction = Direction::left;
			break;
		default:
			break;
		}
		return tempFr;
	}
};