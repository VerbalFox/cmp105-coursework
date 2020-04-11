#pragma once
#include "Framework/GameObject.h"

class UIComponent :
	public GameObject
{
protected:
	float widthPercentage;
	float heightPercentage;
	float xPercentage;
	float yPercentage;

	sf::RenderWindow* window;
public:
	UIComponent();
	void setPositionPercent(float x, float y);
	void setSizePercent(float x, float y);
	void setWindow(sf::RenderWindow* wi);
	
	virtual void update();
	virtual void draw();
};