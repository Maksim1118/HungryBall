#include "Objects.h"
#include <math.h>


Objects::Objects(Vector2f center, float radius) :_radius(radius)/*: _center(center), _mass(mass)*/
{

}

Objects::~Objects() = default;

float Objects::getRadius() const
{
	return _radius;
}
