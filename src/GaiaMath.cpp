#include "GaiaMath.h"

//Dando valor a las componentes del vector.
void Vec2::Set(float x_, float y_)
{
	x = x_;
	y = y_;
}

void Vec2::setX(float x_)
{
	x = x_;
}

void Vec2::setY(float y_)
{
	y = y_;
}

//Calculando algunas propiedades del vector.
float Vec2::Length()
{
	return sqrt(x * x + y * y);
}

float Vec2::LengthSquared()
{
	return x * x + y * y;
}

//Mostrar el valor del vector.
void Vec2::Display()
{
	std::cout << "El vector es: (" << x << ", " << y << ")" << std::endl;
}

//Obteniendo las componentes del vector. 
float Vec2::getX()
{
	return x;
}

float Vec2::getY()
{
	return y;
}


//Definiendo operaciones con vectores. 

void Vec2::operator += (Vec2 v)
{
	x += v.x;
	y += v.y;
}

void Vec2::operator -= (Vec2 v)
{
	x -= v.x;
	y -= v.y;
}

float Vec2::Dot(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float Vec2::Cross(Vec2 a, Vec2 b)
{
	return a.x * b.y - a.y * b.x;
}