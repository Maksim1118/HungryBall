#pragma once
#include <SFML/Graphics.hpp>
#include "Objects.h"
using namespace sf;
using namespace std;
const float FoodRadius = 5.0;
enum foodcolor
{
	yellow, red, blue, green, brown, purple
};
class Food: public Objects
{
public:
	Food();
	void setColor(foodcolor Col);
	void setPosition(float x, float y);
	void TimeElapsed(int diff);
	void draw(RenderWindow& window);
	const Vector2f& getPosition();
	bool active;
private:

	CircleShape _shape;
};

