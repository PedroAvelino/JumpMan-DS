#pragma once

#include <cmath>
#include <iostream>


struct Vector2
{
    Vector2()
    :x(0.0f), y(0.0f)
    {}

    Vector2( float p_x, float p_y )
    :x(p_x), y(p_y)
    {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
};

inline void VectorAdd(Vector2& out, const Vector2& a, const Vector2& b)
{
	out.x = a.x + b.x;
	out.y = a.y + b.y;
}

inline void VectorScale(Vector2& out, Vector2& in, float s)
{
	out.x = in.x * s;
	out.y = in.y * s;
}

inline void VectorSubtract(Vector2& out, const Vector2& a, const Vector2& b)
{
	out.x = a.x - b.x;
	out.y = a.y - b.y;
}

inline float Square(float fValue)
{
	return (fValue * fValue);
}

inline float VectorLenght(const Vector2& v2)
{
	return sqrt(Square(v2.x) + Square(v2.y));
}

inline void Normalize(Vector2& out)
{
	Vector2 v2TempRef = out;
	out.x = out.x / VectorLenght(v2TempRef);
	out.y = out.y / VectorLenght(v2TempRef);
}


inline float VectorDot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}


inline float VectorDistance(const Vector2& a, const Vector2& b)
{
	return sqrt( (Square(a.x - b.x)) + ( Square(a.y - b.y) ) );
}

//COLLISIONS
inline Vector2 Reflect(const Vector2& dir, const Vector2& normal, const Vector2& vel) 
{
	float dot = VectorDot(dir, normal);

	float x = normal.x * dot;
	float y = normal.y * dot;

	Vector2 out;
	out.x = x * -2;
	out.y = y * -2;

	out.x += dir.x;
	out.y += dir.y;

	//TODO: fix this
	//If the velocity is zero the Y axis of the projectile will be "dead" so we hard code a number to prevent that
	if ( vel.y == 0 )
		out.y *= -1;
	else
		out.y *= vel.y;

	return out;
}

inline bool SphereToSphereIntersect(const Vector2& v2PositionA, float fRadiusA, const Vector2& v2PositionB,  float fRadiusB)
{
	Vector2 v2SphereAB;
	VectorSubtract(v2SphereAB, v2PositionA, v2PositionB);

	float fDistanceAB = VectorLenght( v2SphereAB );

	return (fDistanceAB <= (fRadiusA + fRadiusB));
}


