#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <math.h>
#include <vector>

struct Vec2
{
public:
	//Definir los constructores.
	Vec2() {} //Constructor default
	Vec2(float x, float y) : x(x), y(y) {}

	//Asignar valores a las componentes del vector. 
	void Set(float x_, float y_);

	//Propiedades del vector. 
	float Length();
	float LengthSquared();
	void Display();

	//Operaciones con vectores. 
	void operator += (const Vec2& v); //Pass by reference. 
	void operator -= (const Vec2& v);
	
	float Dot(const Vec2& a, const Vec2& b);
	float Cross(const Vec2& a, const Vec2& b);

	float x, y;
};

inline Vec2 operator * (float k, const Vec2& v)
{
	return Vec2(k * v.x, k * v.y);
}

inline Vec2 operator + (Vec2 v1, Vec2 v2)
{
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}
#endif
