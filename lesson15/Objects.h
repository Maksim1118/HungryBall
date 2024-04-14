#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class Objects
{
public:
	float _mass;
	Objects(Vector2f center, float mass);
	void setCenter(float x, float y);
	Vector2f getCenter();
	Vector2f getTopLeft();
	float getRadius();
	float getMass();
    void addMass(float diff);
	void Move(Vector2f diff);
protected:
	Vector2f _center;
};

