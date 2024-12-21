#include "FoodServer.h"
namespace Server
{

	Food::Food() : Objects(Vector2f(0, 0), _FoodMass)
	{
		colorNum = rand() % 6;
	}
	void Food::TimeElapsed(int diff) 
	{

	}
	
}