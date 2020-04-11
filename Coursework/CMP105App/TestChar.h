#pragma once
#include "Character.h"
class TestChar :
	public Character
{
public:
	TestChar();
	~TestChar();

	Move lArmJab;
	sf::IntRect getFrame(int frameNum);
	Animation formAnimation(int firstFrame, int lastFrame);
};