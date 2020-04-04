#include <iostream>
#include <math.h>
#include <vector>

struct Vec2
{
public:
	//Definir los constructores.
	Vec2() : x(0.0f), y(0.0f) {} //Constructor default
	Vec2(float x, float y) : x(x), y(y) {}

	//Asignar valores a las componentes del vector. 
	void Set(float x_, float y_);

	//Propiedades del vector. 
	float Length();
	float LengthSquared();
	void Display();

	//Obtener componentes del vector. 
	float getX();
	float getY();

	//Operaciones con vectores. 
	void operator += (Vec2 v);
	void operator -= (Vec2 v);
	float Dot(Vec2 a, Vec2 b);
	float Cross(Vec2 a, Vec2 b);

private:
	float x, y;
};
