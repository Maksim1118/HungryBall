#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class Objects
{
public:
	Objects(Vector2f center, float radius);
	float getRadius() const;
	virtual void draw(RenderWindow& window) = 0;
	virtual ~Objects()=0;
protected:
	float _radius;
	
};

