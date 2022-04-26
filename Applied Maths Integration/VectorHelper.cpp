#include "VectorHelper.h"
#include <math.h>


float VectorMagnitude(sf::Vector2f a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

float VectorMagnitude(sf::Vector3f a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

sf::Vector2f VectorNormalize(sf::Vector2f a)
{
	return a / VectorMagnitude(a);
}

sf::Vector3f VectorNormalize(sf::Vector3f a)
{
	return a / VectorMagnitude(a);
}


float VectorDot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x*b.x + a.y*b.y;
}

float VectorDot(sf::Vector3f a, sf::Vector3f b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
