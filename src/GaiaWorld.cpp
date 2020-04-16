#include "GaiaWorld.h"

void World::setGravity(const Vec2& v)
{
	gravity = v;
}

void World::addBody(Body* b)
{
	bodies.push_back(b); //Va agregando elementos al vector bodies. 
}

void World::Step(float dt) //LA PARTE MÁS IMPORTANTE DE TODO.
{
	if ((int)bodies.size() == 0) { std::cout << "NO BODIES FOUND IN THIS WORLD." << std::endl; system("pause"); }

	//Integrador de fuerzas
	for (int i = 0; i < (int)bodies.size(); i++)
	{
		bodies[i]->velocity += dt * (gravity + bodies[i]->invMass * bodies[i]->force);
	}

	//Integrador de velocidad
	for (int i = 0; i < (int)bodies.size(); i++) //Iterando sobre el vector "bodies". 
	{
		bodies[i]->position += dt * bodies[i]->velocity;
		bodies[i]->force = Vec2(0.0f, 0.0f);
	}
}