#pragma once
#include "Character.h"
class TestChar :
	public Character
{
public:
	TestChar();
	~TestChar();

	Move lArmJab;
	Move dash;
	Move jumpKick;
	Move crouchArmJab;

	//Helper functions for navigating the excessively large sprite sheet.
	sf::IntRect getFrame(int frameNum);
	Animation formAnimation(int firstFrame, int lastFrame);
};