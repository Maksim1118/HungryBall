#pragma once
#include <SFML/Graphics.hpp>
#include "Objects.h"
#include <list>
#include "Food.h"
//#include "HeroServer.h"
using namespace sf;
using namespace std;

extern  Color botsArrColor[];

class Hero : public Objects
{
public:
	Hero(Vector2f center, float radius,int Col, string text);
	/*Hero& operator =(const Hero&);*/

	//void setPosition(float x, float y);
	//Vector2f getCenter();
	
	void TimeElapsed(int diff);
	void setPosMouse(float& x, float& y);
	void setWeakened();
	void setSplite();
	void setFeeded();

	Text name;
	void draw(RenderWindow& window)override;
	class Piece : public Objects
	{
	public:
		Piece(Vector2f center, float  radius, int Col) : Objects(center,radius)
		{
			_shape.setRadius(radius);
			_shape.setFillColor(botsArrColor[Col]);
			_shape.setPosition(center.x - radius, center.y - radius);
		}

		void draw(RenderWindow& window)override
		{
			window.draw(_shape);
		}
		
		Vector2f V{ 0,0 };
		CircleShape _shape;
		float maxV{ 0 };
		
	};
	list<Piece> pieces{};
	class Feed : public Food
	{
	public:
		Feed(Vector2f center, float radius) : Food(center, radius)
		{
			_shape.setRadius(radius);
			_shape.setPosition(center.x - radius, center.y - radius);
			_shape.setFillColor(Color(255, 255, 255));
		}
		/*void TimeElapsed(int diff) 
		{
			if (GetLen(parentCenter, getCenter()) > parentRadius)
			{
				float lenV = GetLen(V);
				float newlenV = lenV - 0.001f * diff;
				if (newlenV < 0)
					V = { 0,0 };
				else
				{
					V *= newlenV / lenV;

				}

			}
			Move(V * (float)diff);
			
		}*/
		/*Vector2f Center()
		{
			return _shape.getPosition() + Vector2f(getRadius(), getRadius());
		}*/
		void draw(RenderWindow& window)
		{
			/*_shape.setPosition(getTopLeft());
			_shape.setRadius(getRadius());*/
			window.draw(_shape);
		}
		CircleShape _shape;
		//float _mass;
		/*Vector2f V{ 0,0 };
		Vector2f parentCenter{ 0,0 };
		float parentRadius{ 0 };*/
		
	};
	/*list<Food*>& feeds;*/
private:
	void createFeed(Vector2f& center);
	void createPiece(float& mass, Vector2f& center);
	Vector2f _Mouse{ 0,0 };
	Vector2f V{ 0,0 };
	CircleShape _shape;
	int Timer{ 0 };
	int count{ 0 };


};

