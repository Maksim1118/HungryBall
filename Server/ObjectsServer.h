#pragma once
#include <SFML/Graphics.hpp>
#include "BaseOld.h"

using namespace sf;
using namespace std;
namespace Server {
	class Objects
	{
	public:
		float _mass{0};
		Objects(Vector2f center, float mass);
		virtual ~Objects();
		void setCenter(float& x, float& y);
		void setCenter(Vector2f& center);
		Vector2f getCenter() const;
		
		float getRadius()const;
		float getMass()const;
		void addMass(float& diff);
		void Move(Vector2f& diff);
		bool isCollision(const Objects& obj, const float shift = 0);
		virtual void TimeElapsed(int diff) = 0;
		string  getDescription();
		bool eatable = true;

	protected:
		Vector2f _center{ 0,0 };

	};


}
