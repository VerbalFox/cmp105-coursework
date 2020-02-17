#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

// Sets the velocity of the sprite
void GameObject::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}
void GameObject::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

// get sprite velocity
sf::Vector2f GameObject::getVelocity()
{
	return velocity;
}

// Returns collision box + position, giving the collision box in the correct position
sf::FloatRect GameObject::getCollisionBox() {
	
	return sf::FloatRect(collisionBox.left + getPosition().x, collisionBox.top + getPosition().y, collisionBox.width, collisionBox.height); 
}

// Reponse function, what the sprite does based on collision
// Colliding object is passed in for information
// e.g. compare sprite positions to determine new velocity direction.
// e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
void GameObject::collisionResponse(GameObject * collider)
{
}

void GameObject::setType(ObjectType ty)
{
	type = ty;
}

ObjectType GameObject::getType()
{
	return type;
}
