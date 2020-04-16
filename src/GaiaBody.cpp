#include "GaiaBody.h"

void Body::DisplayInfo()
{
	std::cout << "m: " << mass << std::endl;
	std::cout << "s: ", position.Display();
	std::cout << "v: ", velocity.Display();
}

void Body::addForce(const Vec2& f)
{
	force += f;
}