#pragma once
#include "Framework/GameObject.h"
#include "UIElementID.h"

class UIComponent :
	public GameObject
{
protected:
	//Id for later changing of UIText elements.
	ElementID id;

	//Component percentage value changes.
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

	//ID is only used by text elements. Not sure why the other ones need it.
	ElementID getID();
	void setID(ElementID newID);

	virtual void update();
	virtual void draw();
};