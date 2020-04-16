#include "GaiaMath.h"

struct Body
{
public:
	//Constructores
	Body() {}

	//Mostrar información del cuerpo
	void DisplayInfo();

	//Aplicación de fuerzas
	void addForce(const Vec2& f);

	float mass;
	float invMass = 1 / mass;
	Vec2 position;
	Vec2 velocity;
	Vec2 force = Vec2(0.0f, 0.0f); //La mejoraremos eventualmente. 
};
