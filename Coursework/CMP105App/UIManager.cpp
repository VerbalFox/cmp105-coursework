#include "UIManager.h"

UIManager::UIManager()
{

}

void UIManager::setWindow(sf::RenderWindow* wi)
{
	window = wi;
}

void UIManager::setInput(Input* in)
{
	input = in;
}

void UIManager::addSlider(float posX, float posY, float sizeX, float sizeY, sf::Color outlineColour, sf::Color filledColour, float* maxValue, float* displayValue)
{
	UISlider tempSlider(posX, posY, sizeX, sizeY, window);
	tempSlider.setSliderColours(outlineColour, filledColour);
	tempSlider.setSliderValues(maxValue, displayValue);

	sliders.push_back(tempSlider);
}

void UIManager::addButton(float posX, float posY, float sizeX, float sizeY, GameState* gs, State s)
{
	UIButton tempButton(posX, posY, sizeX, sizeY, window, input);
	tempButton.setGameState(gs);
	tempButton.setTargetState(s);
	buttons.push_back(tempButton);
}

void UIManager::update()
{
	for (std::vector<UISlider>::iterator it = sliders.begin(); it != sliders.end(); ++it) {
		(*it).update();
	}

	for (std::vector<UIButton>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		(*it).update();
	}
}

void UIManager::draw()
{
	for (std::vector<UISlider>::iterator it = sliders.begin(); it != sliders.end(); ++it) {
		(*it).draw();
	}

	for (std::vector<UIButton>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
		(*it).draw();
	}
}