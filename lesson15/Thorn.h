#pragma once
#include <SFML/Graphics.hpp>
#include "Objects.h"
using namespace sf;
using namespace std;

const int ThornSpriteSize = 10;
const float ThornSpriteR = 50.0f;

class Thorn : public Objects
{
public:
	Thorn();
	void setPosition(int x, int y);
	void TimeElapsed(int diff);
	void draw(RenderWindow& window);
	const Vector2f& getPosition();
	bool ActiveThorn;
	
private:
	
	Texture thorn;

	Sprite thornSprite[ThornSpriteSize];
	
};

