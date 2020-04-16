#include "GaiaBody.h"

struct World //Se encarga de hacer las iteraciones necesarias para la simulación. 
{
	//Constructores
	World() {} //Constructor default
	World(Vec2 gravity) : gravity(gravity) {}

	//Establecer gravedad
	void setGravity(const Vec2& v);

	//Body creation
	void addBody(Body* b);

	//Simulation
	void Step(float dt);

	Vec2 gravity;
	std::vector<Body*> bodies;
};
