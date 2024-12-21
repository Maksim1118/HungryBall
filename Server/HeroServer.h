#pragma once
#include "ObjectsServer.h"
#include <list>
#include "FoodServer.h"
#include <iostream>
#include <memory>
using namespace sf;
using namespace std;

namespace Server
{
	enum class BotsColor
	{
		BotsYellow, BotsRed, botsBlue, BotsGreen, BotsBrown, BotsPurple
	};
	class Hero : public Objects
	{
	public:
		
		Hero(list<shared_ptr<Objects>>& f,string  text);
		Hero& operator =(const Hero&);

		void TimeElapsed(int diff);
		void setPosMouse(float& x, float& y);
		void setWeakened();
		void setSplite();
		void setFeeded();
		int getID();


		string name;
		int prevMass;
		BotsColor colB;
		bool Splitted = false;
		bool Feeded= false;
		class Piece : public Objects
		{
		public:
			Piece() : Objects(Vector2f(0, 0), 400.f)
			{
				
			}
			void TimeElapsed(int diff) {

			}

			
			Vector2f V{ 0,0 };
			
			float maxV{ 0 };
		
		};
		list<shared_ptr<Objects>> pieces{};
		class Feed : public Food
		{
		public:
			Feed() : Food()
			{
				eatable = false;
				_mass = 25.f;
				colorNum = 2;
			}
			void TimeElapsed(int diff)
			{
				if (GetLen(parentCenter, getCenter()) > parentRadius)
				{
					eatable = true;
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

			}
	
			Vector2f V{ 0,0 };
			Vector2f parentCenter{ 0,0 };
			float parentRadius{ 0 };
		};
		list<shared_ptr<Objects>>& feeds;
		
	private:
		void createFeed(Objects& obj);
		void createPiece(float& mass, Vector2f& center);
		Vector2f _Mouse{ 0,0 };
		Vector2f V{ 0,0 };
		static int nextId;
		int id;
		int Timer{ 0 };
		int count{ 0};
	



	};
}


