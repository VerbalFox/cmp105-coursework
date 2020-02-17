#pragma once
enum class Direction {
	forward,
	backward,
	up,
	down,
	downForward,
	downBackward,
	upForward,
	upBackward
};

enum class AttackButton {
	Button1,
	Button2,
	Button3,
	Button4
};

struct InputFrame {
	Direction direction;
	AttackButton attack;
};