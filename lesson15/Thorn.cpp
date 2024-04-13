#include "Thorn.h"
#include <iostream>

Thorn::Thorn(): Objects(Vector2f(0, 0), 20.000f)
{



	if (!thorn.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\thorn2.png"))
	{

	}
	thornSprite->setTexture(thorn);
	
	ActiveThorn = true;
	
}
void Thorn::setPosition(int x, int y)
{
	thornSprite->setPosition(x, y);
}
void Thorn::draw(RenderWindow& window)
{
	window.draw(*thornSprite);
		
}
const Vector2f& Thorn::getPosition()
{
	return thornSprite->getPosition();
		
}