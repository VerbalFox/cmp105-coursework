// Game Object Class
// A class representing a single renderable game object.
// Game Object extend sf::RectangleShape, and added functionailty for collision, sprite states (alive/dead), velocity for movement, input component
// Most elements of your game will extend game object to create larger more complex elements such as player, enemies, bullets etc.
// @author paul Robertson

#pragma once
#include "SFML\Graphics.hpp"

enum class ObjectType { none, floor, wall, character };

class GameObject : public sf::RectangleShape
{
public:
	GameObject();
	~GameObject();

	// Control sprite speed and direction
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	// Sprite state
	bool isAlive() { return alive; };
	void setAlive(bool b) { alive = b; };

	// For sprite collision, set collider box, get collider box, and dedicated virtual function for collision response
	bool isCollider() { return collider; };
	void setCollider(bool b) { collider = b; };
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect fr) { collisionBox = fr; };
	virtual void collisionResponse(GameObject* collider);


	void setType(ObjectType);
	ObjectType getType();

protected:
	// Sprite properties
	sf::Vector2f velocity;
	bool alive;

	// Collision vars
	sf::FloatRect collisionBox;
	bool collider;

	ObjectType type = ObjectType::none;
};