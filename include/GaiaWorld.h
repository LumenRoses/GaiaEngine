#include "GaiaBody.h"

struct World //Se encarga de hacer las iteraciones necesarias para la simulación. 
{
	//Constructores
	World() : gravity(Vec2(0.0f, 9.81f)) {} //Constructor default
	World(Vec2 gravity) : gravity(gravity) {}

	//Establecer gravedad
	void setGravity(Vec2 v);

	//Body creation
	void addBody(Body* b);

	//Simulation
	void Step(float dt);

private:
	Vec2 gravity;
	std::vector<Body*> bodies;
};
