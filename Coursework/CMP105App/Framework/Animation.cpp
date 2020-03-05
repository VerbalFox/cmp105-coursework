#include "Animation.h"

// Constructor. Sets initial values.
Animation::Animation()
{
	currentFrame = 0;
	elapsedTime = 0;
	isPlaying = true;
	isLooping = true;
	animationSpeed = 0;
	flipped = false;
}

// Adds animation frame. Rect object represent a single sprite frame
void Animation::addFrame(sf::IntRect rect)
{
	frames.push_back(rect);
}

// Returns the size of the animation. The number of frames.
int Animation::getSize()
{
	return (int)frames.size();
}

// Get current frame from the animation. Flip the returning frame if required.
sf::IntRect Animation::getCurrentFrame()
{
	frame = frames[currentFrame];
	if (flipped)
	{

		frame = sf::IntRect(frame.left + frame.width, frame.top, -frame.width, frame.height);
	}
	return frame;
}

// Check if the animation should progress, if so move to next frame, or loop back to the start
void Animation::animate()
{
	if (isPlaying)
	{
		elapsedTime += 1;
		if (elapsedTime >= (animationSpeed / frames.size()))
		{
			currentFrame++;
			if (currentFrame >= frames.size())
			{
				if (isLooping)
				{
					currentFrame = 0;
				}
				else
				{
					currentFrame--;
					setPlaying(false);
				}
			}
			elapsedTime = 0;
		}
	}
}

// Reset animation.
void Animation::reset()
{
	currentFrame = 0;
	elapsedTime = 0;
}

void Animation::stop()
{
	setPlaying(false);
	currentFrame = 0;
	elapsedTime = 0;
}

// Set animation speed, in Frames per Second.
void Animation::setFrameSpeed(int speed)
{
	animationSpeed = speed;
}