#pragma once
#include <SFML/Graphics.hpp>
#include "Objects.h"
#include <list>
using namespace sf;
using namespace std;
class Hero : public Objects
{
public:
	Hero();

	//void setPosition(float x, float y);
	//Vector2f getCenter();
	void TimeElapsed(int diff);
	void setPosMouse(int x, int y);
	void setWeakened();
	void setSplite();
	void setFeeded();

	void draw(RenderWindow& window);
	//const Vector2f& getPosition();
	//float _mass;
	bool Splitted;
	bool Feeded;
	class Piece : public Objects
	{
	public:
		Piece() : Objects(Vector2f(0, 0), 20.000f)
		{

		}

		Vector2f getCenter()
		{
			return _shape.getPosition() + Vector2f(_mass, _mass);
		}
		void move(Vector2f delta) {
			_shape.setPosition(_shape.getPosition() + delta);
		}
		Vector2f V;
		CircleShape _shape;
		float _mass;
		float maxV;
		//Vector2f diff;
	};
	list<Piece> pieces;
	class Feed : public Objects
	{
	public:
		Feed() : Objects(Vector2f(0.f, 0.f), 5.f)
		{
			
		}
		Vector2f Center()
		{
			return _shape.getPosition() + Vector2f(_mass, _mass);
		}
		CircleShape _shape;
		float _mass;
		Vector2f V;
		
	};
	list<Feed> feeds;
private:
	int mouseX;
	int mouseY;
	Vector2f V;
	CircleShape _shape;
	int Timer;
	int count;
	


};

