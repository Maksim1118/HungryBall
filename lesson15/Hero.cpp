#include "Hero.h"
#include <iostream>
#include "Base.h"


Hero::Hero(): Objects(Vector2f(0, 0), 400.000f)
{
	
	_shape.setFillColor(Color(250, 0, 0));
	//_mass = Objects::_mass;
	_shape.setRadius(getRadius());
	V.x = 0;
	V.y = 0;
	Splitted = false;
}

/*void Hero::setPosition(float x, float y)
{
	_shape.setPosition(x, y);
}*/
/*Vector2f Hero::getCenter()
{
	return _shape.getPosition() + Vector2f(_mass, _mass);
}*/

void Hero::TimeElapsed(int diff)
{	
	
	
	if (Splitted == true)
	{

		for (auto& piece : pieces)
		{
			Vector2f center = piece.getCenter();

			for (auto& piece2 : pieces)
			{
				if (&piece == &piece2)
				{
					continue;
				}
				Vector2f toPiece2 = piece2.getCenter() - center;
				float lenPiece2 = GetLen(toPiece2);
				if (lenPiece2 == 0)
				{

					piece2.move(Vector2f(1, 0));
					toPiece2 = piece2.getCenter() - center;
					lenPiece2 = GetLen(toPiece2);
				}
				Vector2f toPiece21 = toPiece2 / lenPiece2;
				float sumRadius = piece._mass + piece2._mass;
				if (lenPiece2 < sumRadius)
				{
					piece2.move(toPiece21 * (sumRadius - lenPiece2) / (float)2);
					piece.move(-toPiece21 * (sumRadius - lenPiece2) / (float)2);
				}

			}
		}
		for (auto& piece : pieces) {
			Vector2f F(0, 0);
			Vector2f center = piece.getCenter();

			Vector2f toMouse = (Vector2f(mouseX, mouseY) - center);
			float lenMouse = GetLen(toMouse);
			if (lenMouse != 0)
			{
				Vector2f toMouse1 = toMouse / lenMouse;

				F += toMouse1;
			}
			
			for (auto& piece2 : pieces) {
				if (&piece == &piece2) {
					continue;
				}
				Vector2f toPiece2 = piece2.getCenter() - center;
				float lenPiece2 = GetLen(toPiece2);
				if (lenPiece2 == 0)
				{

					piece2.move(Vector2f(1, 0));
					toPiece2 = piece2.getCenter() - center;
					lenPiece2 = GetLen(toPiece2);
				}
				Vector2f toPiece21 = toPiece2 / lenPiece2;
				float sumRadius = piece._mass + piece2._mass;
				if (lenPiece2 > sumRadius) {
					F += toPiece21 * (float)0.01;
				}

			}

			Vector2f a = F / piece._mass;
			float lenA = GetLen(a);
			float maxA = 2.0 / piece._mass;
			if (lenA > maxA) {
				a = a / lenA * (float)maxA;
			}

			piece.V += a * (float)diff * (float)1.0;
			float lenV = GetLen(piece.V);
			float maxV = piece.maxV;
			if (lenMouse < 40)
			{
				maxV *= (lenMouse / 40);
			}
			if (lenV > maxV) {
				piece.V *= (float)maxV / lenV;
			}


			piece.move(piece.V * (float)diff);
		}
	}
	else
	{
		Vector2f vector = getCenter();

		Vector2f d(mouseX - vector.x, mouseY - vector.y);
		float len = GetLen(d, Vector2f(0, 0));

		d /= len;
		V += d * (float)diff * 0.0007f;
		float lenV = GetLen(V, Vector2f(0, 0));
		float maxV = 0.2f;
		if (len < getRadius())
		{
			maxV *= (len / getRadius());
		}
		if (lenV > maxV)
		{
			V = V / lenV * maxV;
		}
		Vector2f V1 = V;

		float K = 0.2f;


		setCenter(vector.x  + V1.x * K * diff, vector.y + V1.y * K * diff);
	}
	
	if (Splitted == true)
	{
		Timer -= diff;
		if (Timer < 0)
		{
			int count = 0;
			Vector2f co(0, 0);
			
			for (auto& piece : pieces)
			{
				co += piece.getCenter();
				count++;
			}
			co /= (float)count;
			_shape.setPosition(_shape.getPosition() + (co - getCenter()));
			Splitted = false;

		}
			
	}
	/*if (Feeded == true)
	{
		Feed& feed = feeds.front();
		//int count = (_mass - 20.0f) / feed._mass;
		if (feeds.size() > count)
		{
			feeds.resize(count);
		}
		Vector2f center = getCenter();
		Vector2f Dir = (Vector2f(mouseX, mouseY) - center);
		float LenMouse = GetLen(Dir);
		float A = 1.0f;
		feed.V = A * 0.03f;
		Dir /= LenMouse;
		if ((feed._shape.getPosition().x - center.x) > _mass && (feed._shape.getPosition().y - center.y) > _mass)
		{
			feed.V -= 0.0005f;
			if (feed.V < 0.0f)
				feed.V = 0.0f;
		}
		if (LenMouse > 0.0f)
			feed._shape.move(feed.V * Dir);

	}*/
	for (auto& f : feeds)
	{
		if (GetLen(getCenter(), f.Center()) > getRadius())
		{
			float lenV = GetLen(f.V);
			float newlenV = lenV - 0.001f * diff;
			if (newlenV < 0)
				f.V = {0,0};
			else
			{
				f.V *= newlenV / lenV;
				
			}
			
		}
		f._shape.move(f.V* (float)diff);
		cout << f._shape.getPosition().x << " " << f._shape.getPosition().y << endl;
		
	}
}
void Hero::setPosMouse(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
void Hero::setWeakened()
{
	Splitted = true;
	Timer = 5000;
	count = _mass / 20;
	if (count > 6)
		count = 6;
	float average = _mass / count;
	pieces.clear();
	for (int i = 0; i < count; i++)
	{
		pieces.emplace_back();
		Piece& p = pieces.back();
		p._mass = average * (float)(rand() % 100 + 50) / 100.0f;
	    p.maxV = 1.0 / p._mass;
		Vector2f center = getCenter();
		//p.diff = Vector2f(rand() % 100 - 50, rand() % 100 - 50);
		p._shape.setPosition(_shape.getPosition());
		p._shape.setRadius(p._mass);
		p._shape.setFillColor(Color(250, 0, 0));

	}
}
void Hero::setSplite()
{
	if (_mass < 40.f)
		return;
	if (Splitted == true)
	{
		return;
	}
	Splitted = true;
	Timer = 5000;
	pieces.clear();
	for (int i = 0; i < 2; i++)
	{
		pieces.emplace_back();
		Piece& p = pieces.back();
		p._mass = _mass / 2;
		p.maxV = 0.5 / p._mass * (i + 1);
		Vector2f center = getCenter();
		//p.diff = Vector2f(_mass * i, _mass * i);
		p._shape.setPosition(_shape.getPosition());
		p._shape.setRadius(p._mass);
		p._shape.setFillColor(Color(250, 0, 0));

	}
}
void Hero::setFeeded()
{
	if (_mass < 25.f)
		return;
	_mass -= 2;
	feeds.emplace_back();
	Feed& f = feeds.back();
	f._mass = 5.f;
	f._shape.setRadius(f._mass);
	f._shape.setFillColor(Color::Red);
	f._shape.setPosition(getCenter() - Vector2f(f._mass, f._mass));
	
	Vector2f center = f.Center();
	Vector2f Dir = (Vector2f(mouseX, mouseY) - center);
	float LenMouse = GetLen(Dir);
	if (LenMouse == 0)
	{
	    float angle = (float)(rand() % 360) / 180.0f * 3.1415926;
		Dir = Vector2f(cos(angle), sin(angle));
	}
	else
	{
		Dir /= LenMouse;
	}	
	f.V = Dir * 0.5f;

}
void Hero::draw(RenderWindow& window)
{	
	
	if (Splitted == true)
	{	
		//cout << endl;
		for (auto &p: pieces)
		{
			p._shape.setRadius(p._mass);
			//p._shape.setPosition(_shape.getPosition() + p.diff);
			window.draw(p._shape);
			//cout << p._shape.getPosition().x << " " << p._shape.getPosition().y << endl;

		}

	}
	else
	{
		_shape.setPosition(getCenter().x - getRadius(), getCenter().y - getRadius());
		_shape.setRadius(getRadius());
		window.draw(_shape);
	}
	for (auto& f : feeds)
	{
		window.draw(f._shape);
	}
	
}
/*const Vector2f& Hero::getPosition()
{
	return _shape.getPosition();
}*/