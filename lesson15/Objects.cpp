
#include "Objects.h"
#include <math.h>

Objects::Objects(Vector2f center, float mass): _center(center), _mass(mass)
{

}

void Objects::setCenter(float x, float y)
{
	_center.x = x;
	_center.y = y;
}
Vector2f Objects::getCenter()
{
	return _center;
}
Vector2f Objects::getTopLeft()
{
	float radius = getRadius();

	return _center - Vector2f(radius, radius);
}
float Objects::getRadius()
{
	return sqrt(_mass);
}
float Objects::getMass()
{
	return  _mass;
}
void Objects::addMass(float diff)
{
	_mass += diff;

}
void Objects::Move(Vector2f diff)
{
	_center += diff;
}