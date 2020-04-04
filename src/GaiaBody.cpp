#include "GaiaBody.h"

void Body::setMass(float m)
{
	mass = m;
}

void Body::setVel(Vec2 v)
{
	velocity = v;
}

void Body::setPos(Vec2 v)
{
	position = v;
}

float Body::getMass()
{
	return mass;
}

float Body::getInvMass()
{
	return invMass;
}

Vec2 Body::getVel()
{
	return velocity;
}

Vec2 Body::getPos()
{
	return position;
}

void Body::DisplayInfo()
{
	std::cout << "m: " << mass << std::endl;
	std::cout << "s: ", position.Display();
	std::cout << "v: ", velocity.Display();
}

void Body::addForce(Vec2 v)
{



}