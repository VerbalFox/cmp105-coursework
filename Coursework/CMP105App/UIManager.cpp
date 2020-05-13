#include "UIManager.h"

UIManager::UIManager()
{
	font.loadFromFile("font/Mohave-Regular.otf");
}

void UIManager::setWindow(sf::RenderWindow* wi)
{
	window = wi;
}

void UIManager::setInput(Input* in)
{
	input = in;
}

void UIManager::addSlider(ElementID newID, float posX, float posY, float sizeX, float sizeY, sf::Color outlineColour, sf::Color filledColour, float* maxValue, float* displayValue)
{
	//Creates a pointer, creates a slider at that pointer, sets it up, then pushes that pointer before it falls out of scope so it's not lost.
	//All other add functions in this class work the same way.

	UISlider* tempSlider = new UISlider(posX, posY, sizeX, sizeY, window);
	tempSlider->setSliderColours(outlineColour, filledColour);
	tempSlider->setSliderValues(maxValue, displayValue);
	tempSlider->setID(newID);

	sliders.push_back(tempSlider);
}

void UIManager::addButton(ElementID newID, float posX, float posY, float sizeX, float sizeY, std::function<void()> func)
{
	UIButton* tempButton = new UIButton(posX, posY, sizeX, sizeY, window, input);
	//std::bind lets the member function that would've otherwise needed a parameter to be stored in an object that treats it like it doesn't need one. Perfect here.
	tempButton->setButtonFunction(func);
	tempButton->setID(newID);

	buttons.push_back(tempButton);
}

void UIManager::addText(ElementID newID, float posX, float posY, float sizeX, float sizeY)
{
	UIText* tempText = new UIText(posX, posY, sizeX, sizeY, window);
	tempText->setFont(&font);
	tempText->setID(newID);

	texts.push_back(tempText);
}

void UIManager::setTextStringById(ElementID id, std::string newString)
{
	//Search until an element that matches the argument ID is found, then change that element string. Do nothing if no matching elementID is found.
	for (size_t i = 0; i < texts.size(); i++)
	{
		if (texts[i]->getID() == id) {
			texts[i]->setTextString(newString);
			break;
		}
	}
}

void UIManager::clearElements()
{
	//Deletes the contents of the pointers before clearing the pointers from the vectors.
	for (size_t i = 0; i < sliders.size(); i++)
	{
		delete sliders[i];
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}

	for (size_t i = 0; i < texts.size(); i++)
	{
		delete texts[i];
	}

	sliders.clear();
	buttons.clear();
	texts.clear();
}

void UIManager::update()
{
	//Update every element in the vectors.
	for (size_t i = 0; i < sliders.size(); i++)
	{
		sliders[i]->update();
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->update();
	}

	for (size_t i = 0; i < texts.size(); i++)
	{
		texts[i]->update();
	}
}

void UIManager::draw()
{
	//Draw every element in the vectors.
	for (size_t i = 0; i < sliders.size(); i++)
	{
		sliders[i]->draw();
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->draw();
	}

	for (size_t i = 0; i < texts.size(); i++)
	{
		texts[i]->draw();
	}
}