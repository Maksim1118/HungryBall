#include "HeroServer.h"
#include <iostream>
#include "BaseOld.h"

namespace Server
{
	int Hero::nextId = 1;

	Hero::Hero(list<shared_ptr<Objects>>& f, string text) : Objects(Vector2f(0, 0), 400.000f), feeds(f),id(nextId++)
	{
		name=text;
		prevMass = _mass;
		Splitted = false;
		colB = (BotsColor)(rand() % 6);
	}

	Hero& Hero::operator =(const Hero& other)
	{
		Splitted = other.Splitted;
		Feeded = other.Feeded;
		pieces = other.pieces;
		feeds = other.feeds;
		_Mouse = other._Mouse;
		V = other.V;
	
		Timer = other.Timer;
		count = other.count;
		return *this;
	}

	int Hero::getID()
	{
		return id;
	}
	void Hero::TimeElapsed(int diff)
	{


		if (Splitted == true)
		{

			for (auto& piece : pieces)
			{
				Vector2f center = piece->getCenter();

				for (auto& piece2 : pieces)
				{
					if (&piece == &piece2)
					{
						continue;
					}

					float lenPiece2 = GetLen(piece->getCenter(), piece2->getCenter());
					float sumRadius = piece->getRadius() + piece2->getRadius();
					if (lenPiece2 < sumRadius)
					{
						Vector2f toPiece21 = getIdentityVector(piece2->getCenter() - center);
						piece2->Move(toPiece21 * (sumRadius - lenPiece2) / (float)2);
						piece->Move(-toPiece21 * (sumRadius - lenPiece2) / (float)2);
					}

				}
			}
			for (auto& piece : pieces) {
				Vector2f F(0, 0);
				Vector2f center = piece->getCenter();

			
				F += getIdentityVector(_Mouse - center);

				for (auto& piece2 : pieces) {
					if (piece == piece2) {
						continue;
					}
					float lenPiece2 = GetLen(piece->getCenter(), piece2->getCenter());
					float sumRadius = piece->getRadius() + piece2->getRadius();
					if (lenPiece2 > sumRadius)
					{
						Vector2f toPiece21 = getIdentityVector(piece2->getCenter() - center);
						F += toPiece21 * (float)0.01;
					}
					
				}

				Vector2f a = F / piece->_mass;
				float lenA = GetLen(a);
				float maxA = 2.0 / piece->_mass;
				if (lenA > maxA) {
					a = a / lenA * (float)maxA;
				}

				dynamic_cast<Piece*>(piece.get())->V += a * (float)diff * (float)1.0;
				float lenV = GetLen(dynamic_cast<Piece*>(piece.get())->V);
				float maxV = dynamic_cast<Piece*>(piece.get())->maxV;
				float lenMouse = GetLen(_Mouse - getCenter());
				if (lenMouse < 40)
				{
					maxV *= (lenMouse / 40);
				}
				if (lenV > maxV) {
					dynamic_cast<Piece*>(piece.get())->V *= (float)maxV / lenV;
				}


				dynamic_cast<Piece*>(piece.get())->Move(dynamic_cast<Piece*>(piece.get())->V * (float)diff);
			}

		}
		else
		{
			Vector2f vector = getCenter();

			Vector2f d = getIdentityVector(_Mouse - vector);
		
			V += d * (float)diff * 0.0007f;
			float lenV = GetLen(V, Vector2f(0, 0));
			float maxV = 0.2f;
			float len = GetLen(_Mouse - vector);
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


			setCenter(vector + V1 * K * (float)diff);
		}

		if (Splitted == true)
		{
			Timer -= diff;
			if (Timer < 0)
			{
				int count = 0;
				Vector2f co(0, 0);
				_mass = 0;
				for (auto& piece : pieces)
				{
					_mass += piece->getMass();
					co += piece->getCenter();
					count++;
				}
				co /= (float)count;
				setCenter(co);
				
				Splitted = false;

			}

		}

	}
	void Hero::setPosMouse(float& x, float& y)
	{
		_Mouse = Vector2f(x, y);
	}
	void Hero::setWeakened()
	{
		Splitted = true;
		Timer = 5000;
		count = _mass / 400;
		if (count > 8)
			count = 8;
		
		float remainMass = _mass;
		pieces.clear();
		for (int i = 0; i < count; i++)
		{
			Piece* p = new Piece;
			pieces.emplace_back(p);
			
			if (i == count - 1)
			{
				p->_mass = remainMass;
			}
			else
			{
				p->_mass = remainMass / (count - i) * (float)(rand() % 40 + 80) / 100.0f;
			}
			remainMass -= p->_mass;
			p->maxV = 1.0 / p->getRadius();
			
			p->setCenter(getCenter());
			

		}
	}
	void Hero::createPiece(float& mass, Vector2f& center)
	{
		Timer = 5000;
		for (int i = 0; i < 2; i++)
		{
			Piece* p = new  Piece;
			pieces.emplace_back(p);
		
			p->_mass = mass / 2;
			p->maxV = 0.7 / p->getRadius() * (i + 1);

			Vector2f toMouse1 = getIdentityVector(_Mouse - center);
			p->V = toMouse1 * p->maxV;
		
			p->setCenter(center + toMouse1 * (float)i);
		

		}
	}
	void Hero::setSplite()
	{
		if (_mass < 800.f)
			return;
		if (Splitted == true)
		{
			if (pieces.size() >= 8)
			{
				return;
			}
			list<shared_ptr<Objects>> oldPieces = pieces;
			pieces.clear();

			for (auto& p : oldPieces)
			{

				createPiece(p->_mass, p->getCenter());
			}
			return;
		}
		Splitted = true;
		pieces.clear();
		createPiece(_mass, getCenter());
	}

	void Hero::createFeed(Objects& obj)
	{

		Feed* f = new Feed();
		obj._mass -= f->getMass();
	
		f->setCenter(obj.getCenter());
		Vector2f Dir = getIdentityVector(_Mouse - obj.getCenter());

		f->V = Dir * 0.5f;
		f->parentCenter = getCenter();
		f->parentRadius = getRadius();
		feeds.push_back(shared_ptr<Objects>(f));

	}
	void Hero::setFeeded()
	{
		if (Splitted)
		{
			for (auto& p : pieces)
			{
				if (p->getMass() < 400.f)
					continue;
				createFeed(*p);
			}
		}
		else
		{
			if (_mass < 400.f)
				return;
			createFeed(*this);
		}

	}
	
}