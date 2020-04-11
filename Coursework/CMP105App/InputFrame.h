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
	bool Equals(InputFrame inputFr) {
		return (this->direction == inputFr.direction && this->attack == inputFr.attack) ? true : false;
	}
};