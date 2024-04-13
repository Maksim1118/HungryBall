#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class Objects
{
public:
	Objects(Vector2f center, float mass);
	Vector2f getCenter();
	Vector2f getTopLeft();
	float getRadius();
	float getMass();
    void addMass(float diff);
	void Move(Vector2f diff);
protected:
	float _mass;
	Vector2f _center;
};

