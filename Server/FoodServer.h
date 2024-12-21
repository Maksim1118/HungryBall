#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectsServer.h"
using namespace sf;
using namespace std;

namespace Server
{
	constexpr float _FoodMass = 25.0f;
	const float _FoodRadius = sqrt(_FoodMass);

	class Food : public Objects
	{
	public:
		Food();
		void TimeElapsed(int diff);
		int colorNum;
	private:

	
		

	};
}

