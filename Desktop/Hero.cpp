#include "Hero.h"
#include <iostream>
//#include "BaseOld.h"
#include "ResourñeManager.h"
Color botsArrColor[] =
{ Color(250, 255, 0),
	Color(255, 0, 0),
	Color(0, 199, 255),
	Color(100, 250, 50),
	Color(165, 72, 38),
	Color(168, 17, 255)
};


Hero::Hero(Vector2f center, float radius, int Col, string text): Objects(Vector2f(0, 0), radius)
{
	name.setString(text);
	name.setColor(Color::White);
	name.setFont(*rec.font);
	name.setCharacterSize(20+radius/5);

	name.setPosition(center.x - name.getLocalBounds().width / 2, center.y - name.getLocalBounds().height / 2);
	//if ((getMass() - prevMass) >= 100)
	//{
	//	name.setCharacterSize(name.getCharacterSize() + 1);
	//	prevMass = getMass();
	//}

	_shape.setRadius(radius);
	_shape.setFillColor(botsArrColor[Col]);
	_shape.setPosition(center.x - radius, center.y - radius);
	
}

void Hero::TimeElapsed(int diff)
{	
	
}
void Hero::setPosMouse(float& x, float& y)
{
	_Mouse = Vector2f(x, y);
}
void Hero::setWeakened()
{
	
}
void Hero::createPiece(float& mass, Vector2f& center)
{

}
void Hero::setSplite()
{

}

void Hero::createFeed(Vector2f& center)
{
	
}
void Hero::setFeeded()
{
	

}
void Hero::draw(RenderWindow& window)
{	
	
	/*cout << _shape.getPosition().x<< "      " << _shape.getPosition().y << "      " << _shape.getRadius() << "      " << _shape.getFillColor().toInteger() << endl << endl;*/
	window.draw(_shape);
	window.draw(name);
	
}
