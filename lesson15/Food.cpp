#include "Food.h"

Color arrcolor[] =
{ Color(250, 255, 0),
	Color(255, 0, 0),
	Color(0, 199, 255),
	Color(100, 250, 50),
	Color(165, 72, 38),
	Color(168, 17, 255) };

Food::Food(): Objects(Vector2f(0,0), FoodRadius)
{
	_shape.setRadius(FoodRadius);
	active = true;
	
}
void Food::setColor(foodcolor Col)
{
	_shape.setFillColor(arrcolor[Col]);
}
void Food::setPosition(float x, float y)
{
	_shape.setPosition(x, y);
}
void Food::draw(RenderWindow& window)
{
	window.draw(_shape);
}
const Vector2f& Food::getPosition()
{
	return _shape.getPosition();
}