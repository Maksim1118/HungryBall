#include "GameEngine.h"
#include <ctime>
#include "BaseOld.h"
//#include "SettingScene.h"
#include "MessageServer.h"
#include<iostream>

constexpr int fieldWidth = 1200;
constexpr int fieldHeight = 1200;

namespace Server
{
	void runServer()
	{
		Server::GameEngine _Engine;
		Clock clock;
		Time time = clock.getElapsedTime();
		while (1)
		{
			Time time2 = clock.getElapsedTime();
			int  diff = time2.asMilliseconds() - time.asMilliseconds();
			time = time2;
			_Engine.TimeElapsed(diff);
			lock_guard<mutex> lock(m);
			if (!messageServer.isResponse)
			{
				messageServer.response = _Engine.process(messageServer.request);
				messageServer.isResponse = true;
			}
		}
	}

	GameEngine::GameEngine() : hero(_Food,"myHero")
	{

		_GameOver = false;
		

		srand(time(NULL));

		float xHero = (float)(rand() % 1100);
		float yHero = (float)(rand() % 1100);
		hero.setCenter(xHero, yHero);

		for (int i = 0; i < 10; i++)
		{

			bots.push_back(shared_ptr<Objects>(new Hero(_Food, "Bot" + to_string(i+1))));
		}

		for (auto i = bots.begin(); i != bots.end();i++)
		{
			
			float xBot = (float)(rand() % 1100);
			float yBot = (float)(rand() % 1100);
			(*i)->setCenter(xBot, yBot);
			if ((*i)->isCollision(hero, 2))
			{
				i--;
				break;
			}
			for (auto j = next(i); j != bots.end(); j++)
			{
				
				if ((*i)->isCollision(**j, 2))
				{
					i--;
					break;
				}
			}

		}

		for (int i = 0; i < ThornSpriteSize; ++i)
			_ThornSprite.emplace_back(new Thorn);

		for (auto &i = _ThornSprite.begin(); i != _ThornSprite.end(); ++i)
		{
			float xThorn = (float)(rand() % (int)(fieldWidth - _ThornSpriteR));
			float yThorn = (float)(rand() % (int)(fieldHeight - _ThornSpriteR));
			(*i)->setCenter(xThorn,yThorn);

			for (auto& j = _ThornSprite.begin(); j != i; ++j)
			{

				if ((*i)->isCollision(**j, 2))
				{
					i--;
					break;
				}


			}
		}


		
		for (int i = 0; i < ArrFoodSize; ++i)
			_Food.emplace_back(new Food());
		for (auto& i = _Food.begin(); i != _Food.end(); ++i)
		{
			

			float xFood = (float)(rand() % SetPosFood);
			float yFood = (float)(rand() % SetPosFood);
			(*i)->setCenter(xFood,yFood);
			
			for (auto& j = _Food.begin(); j != i; ++j)
			{
				

				if ((*i)->isCollision(**j, 2))
				{
					i--;
					break;
				}
				
			}

		}

	}

	nlohmann::json GameEngine::process(nlohmann::json request)
	{
		nlohmann::json response;
		
		if (request.contains("action") && request["action"] == "split")
		{
			hero.setSplite();
			response["status"] = "OK";
		}
		else if (request.contains("action") && request["action"] == "feed")
		{
			hero.setFeeded();
			response["status"] = "OK";
		}
		else if (request.contains("action") && request["action"] == "ask pos mouse")
		{
			float x = request["mousePosition"]["x"];
			float y = request["mousePosition"]["y"];
			hero.setPosMouse(x, y);
			response["status"] = "OK";
		}
		else if (request.contains("action") && request["action"] == "get object")
		{
			nlohmann::json FoodArray = nlohmann::json::array();
			for (auto& f : _Food)
			{
				nlohmann::json Food;
				Food["Center"] = { {"x", f->getCenter().x},{ "y", f->getCenter().y} };
				Food["Radius"] = f->getRadius();
				Food["Color"] = dynamic_cast<Server::Food*>(f.get())->colorNum;
				FoodArray.push_back(Food);
			}
			response["listFood"] = FoodArray;

			nlohmann::json ThornArray = nlohmann::json::array();
			for (auto& t : _ThornSprite)
			{
				nlohmann::json Thorn;
				Thorn["Center"] = { {"x", t->getCenter().x},{ "y", t->getCenter().y} };
				Thorn["Radius"] = t->getRadius();
				ThornArray.push_back(Thorn);
			}			
			response["listThorn"] = ThornArray;

			nlohmann::json BotsArray = nlohmann::json::array();

			for (auto& b : bots)
			{
				auto bot = dynamic_cast<Server::Hero*>(b.get());
				auto botCol = static_cast<int>(bot->colB);
				nlohmann::json Bot;
				Bot["Center"] = { {"x", b->getCenter().x},{ "y", b->getCenter().y} };
				Bot["Radius"] = b->getRadius();
				Bot["Color"] = botCol;
				Bot["Name"] = bot->name;
				Bot["Splitted"] = bot->Splitted;
				if (Bot["Splitted"] == true)
				{
					nlohmann::json BotPieceArray = nlohmann::json::array();
					for (auto& p : bot->pieces)
					{
						nlohmann::json Piece;
						Piece["Center"] = { {"x", p->getCenter().x},{ "y", p->getCenter().y} };
						Piece["Radius"] = p->getRadius();
						Piece["Color"] = botCol;

						BotPieceArray.push_back(Piece);
					}
					Bot["Pieces"] = BotPieceArray;
				}
				BotsArray.push_back(Bot);
			}
			response["listBot"] = BotsArray;

			nlohmann::json Hero;
			auto heroCol = static_cast<int>(hero.colB);
			Hero["Center"] = { {"x", hero.getCenter().x},{ "y", hero.getCenter().y} };
			Hero["Radius"] = hero.getRadius();
			Hero["Color"] = heroCol;
			Hero["Name"] = hero.name;
			Hero["Splitted"] = hero.Splitted;
			Hero["Feeded"] = hero.Feeded;
			Hero["Mass"] = hero.getMass();
			Hero["GameOver"] = _GameOver;

			if (Hero["Splitted"] == true)
			{
				nlohmann::json HeroPieceArray = nlohmann::json::array();
				for (auto& p : hero.pieces)
				{
					nlohmann::json Piece;
					Piece["Center"] = { {"x", p->getCenter().x},{ "y", p->getCenter().y} };
					Piece["Radius"] = p->getRadius();
					Piece["Color"] = heroCol;

					HeroPieceArray.push_back(Piece);
				}
				Hero["Pieces"] = HeroPieceArray;
			}

			if (Hero["Feeded"] == true)
			{
				nlohmann::json FeedArray = nlohmann::json::array();
				for (const auto& f : hero.feeds)
				{
					nlohmann::json Feed;
					Feed["Center"] = { {"x", f->getCenter().x},{ "y", f->getCenter().y} };
					Feed["Radius"] = f->getRadius();

					FeedArray.push_back(Feed);
				}
				Hero["Feeds"] = FeedArray;
			}

			response["Hero"] = Hero;
			response["status"] = "OK";
		}
		else
		{
			response["status"] = "ERROR";
		}

		return response;
	}

	bool GameEngine::isCollWithMap(const  Vector2f& pos)
	{
		return (pos.x < 0) || (pos.x > fieldWidth) || (pos.y < 0) || (pos.y > fieldHeight) ? true : false;
	}
	Vector2f GameEngine::getCoorCollWithMap(const Vector2f& pos)
	{
		if (pos.x < 0)
			return Vector2f(0, pos.y);
		else if (pos.x > fieldWidth)
			return Vector2f(fieldWidth, pos.y);
		else if (pos.y < 0)
			return  Vector2f(pos.x, 0);
		else if (pos.y > fieldHeight)
			return Vector2f(pos.x, fieldHeight);
	}
	void GameEngine::TimeElapsed(int& diff)
	{
	/*	cout << (*bots.begin())->getCenter().x << "  " << (*bots.begin())->getCenter().y << endl;*/
		if (!_GameOver)
			hero.TimeElapsed(diff);
		if (isCollWithMap(hero.getCenter()))
			hero.setCenter(getCoorCollWithMap(hero.getCenter()));

		for (auto& f : hero.feeds)
		{
			if (isCollWithMap(f->getCenter()))
				f->setCenter(getCoorCollWithMap(f->getCenter()));
		}
		for (auto& b : bots)
		{
			if (isCollWithMap(b->getCenter()))
				b->setCenter(getCoorCollWithMap(b->getCenter()));
		}
		for (auto& Piece : hero.pieces)
		{
			if (isCollWithMap(Piece->getCenter()))
				Piece->setCenter(getCoorCollWithMap(Piece->getCenter()));

		}

		/*cout << "begin: " << endl;*/
		for (auto i = bots.begin(); i != bots.end(); i++)
		{
			/*cout << "bot: " << (*i)->getCenter().x << "  " << (*i)->getCenter().y << endl;*/
			Vector2f to(0.0,0.0);
			for (auto& j = _Food.begin(); j != _Food.end(); ++j)
			{
				Vector2f distance = (*j)->getCenter() - (*i)->getCenter();
				float lenD = GetLen(distance);
				if (lenD < (*i)->getRadius()*0.99f)
				{
					continue;

				}
				distance /= lenD;
				distance /= lenD;
				distance /= lenD;
				to += distance;
			}
			/*cout << "to1: " << to.x << "  " << to.y << endl;*/
			{
				for (auto& j = _ThornSprite.begin(); j != _ThornSprite.end(); ++j)
				{

					Vector2f distance = (*j)->getCenter() - (*i)->getCenter();
					float lenD = GetLen(distance);
					if (lenD < (*i)->getRadius() + _ThornSpriteR - 10)
					{
						if(lenD < min((*i)->getRadius(),(*j)->getRadius())*0.99f)
							continue;
						distance /= lenD;
						distance /= lenD;
						distance /= lenD;
						to -= distance * 4.f;
					}
				}
			}
			/*cout << "to2: " << to.x << "  " << to.y << endl;*/
			to = getIdentityVector(to) * 100.f + (*i)->getCenter();
		
			dynamic_cast<Server::Hero*>((*i).get())->setPosMouse(to.x, to.y);
			(*i)->TimeElapsed(diff);

		}
		for (auto& i = _Food.begin(); i != _Food.end();)
		{
			(*i)->TimeElapsed(diff);
			if (!(*i)->eatable)
			{
				++i;
				continue;
			}
			bool foodEaten = false;
			if (hero.Splitted)
			{
				for (auto& Piece : hero.pieces)
				{
					if (Piece->isCollision(**i))
					{
						hero._mass += _FoodMass;
						Piece->_mass += _FoodMass;
						i = _Food.erase(i);
						foodEaten = true;
						break;
					}

				}

			}
			else
			{
				if (hero.isCollision(**i, -(*i)->getRadius()))
				{
					hero._mass += 3*_FoodMass;
					i = _Food.erase(i);
					foodEaten = true;
				}

			}
			if (!foodEaten)
			{
				for (auto j = bots.begin(); j != bots.end(); j++)
				{

					
					if (dynamic_cast<Server::Hero*>((*j).get())->isCollision(**i, -(*i)->getRadius()))
					{
						(*j)->_mass +=3 * _FoodMass;
						i = _Food.erase(i);
						foodEaten = true;
						break;
					}

				}
				if (!foodEaten)
					(*i)->TimeElapsed(diff);
			}
			if (!foodEaten) ++i;


		}
		for (auto& i = _ThornSprite.begin(); i != _ThornSprite.end();)
		{

		
			thornEaten = false;
			if (hero.Splitted)
			{
				for (auto& Piece : hero.pieces)
				{
					if (Piece->isCollision(**i, -(*i)->getRadius()) && Piece->_mass > _ThornSpriteMass * 1.2f)
					{
						hero._mass += _ThornSpriteMass;
						Piece->_mass += _ThornSpriteMass;
						i = _ThornSprite.erase(i);

						thornEaten = true;
						break;

					}

				}
			}
			else
			{

				if (hero.isCollision(**i, -(*i)->getRadius()) && hero._mass > _ThornSpriteMass * 1.2f)
				{
					hero._mass += _ThornSpriteMass;
					i = _ThornSprite.erase(i);
					hero.setWeakened();
					thornEaten = true;
				}

			}
			if (!thornEaten)
			{
				for (auto& b : bots)
				{
					if (b->isCollision(**i, -(*i)->getRadius()) && b->_mass > _ThornSpriteMass * 1.2f)
					{
						b->_mass += _ThornSpriteMass;
				
						i = _ThornSprite.erase(i);
						dynamic_cast<Server::Hero*>(b.get())->setWeakened();
						thornEaten = true;
						break;
					}

				}
			}
			if (!thornEaten) ++i;


		}
		for (auto i = bots.begin(); i != bots.end();)
		{
			bool botsEaten = false;
			for (auto j = bots.begin(); j != bots.end();)
			{
				if ((*j)->isCollision(**i, -min((*i)->getRadius(), (*j)->getRadius())))
				{
					if ((*j)->_mass > (*i)->_mass * 1.2f)
					{
						(*j)->_mass += (*i)->_mass;

						/*std::cout << "1 Bot " << i->getDescription() << " was eaten by Bot " << j->getDescription() << " бот №i " << i << " " << " бот №j " << j <<  endl;*/
						
						i=bots.erase(i);
						/*std::cout << " new I = " << i->getDescription() << endl;*/
						botsEaten = true;
						break;
					}

					if ((*i)->_mass > (*j)->_mass * 1.2f)
					{
						(*i)->_mass += (*j)->_mass;
						/*std::cout << "2 Bot " << j->getDescription() << " was eaten by Bot " << i->getDescription() << " бот №j " << j << " " << " бот №i " << i << endl;*/
						j=bots.erase(j);
						/*std::cout << " new J = " << j->getDescription() << endl;*/
						continue;

					}

				}
				++j;
			}
			if (botsEaten)
				continue;

			if (botsEaten)
				continue;
			if (!_GameOver)
			{
				if (hero.Splitted)
				{
					if (dynamic_cast<Server::Hero*>((*i).get())->Splitted)
					{

						for (auto& j = hero.pieces.begin(); j != hero.pieces.end();)
						{
							bool heroPieceEaten = false;
							for (auto& k = dynamic_cast<Server::Hero*>((*i).get())->pieces.begin(); k != dynamic_cast<Server::Hero*>((*i).get())->pieces.end();)
							{
								if ((*k)->isCollision(**j, -min((*k)->getRadius(), (*j)->getRadius())))
								{
									if ((*j)->_mass > (*k)->_mass * 1.2f)
									{
										(*j)->_mass += (*k)->_mass;
										(*i)->_mass -= (*k)->_mass;
										k = dynamic_cast<Server::Hero*>((*i).get())->pieces.erase(k);

										if (dynamic_cast<Server::Hero*>((*i).get())->pieces.empty())
										{
											botsEaten = true;
											/*cout << "BotLastPiece " << i->getDescription() << " was eaten by HeroPiece " << j->getDescription() << endl;*/
											i = bots.erase(i);
											break;
										}
										
										continue;
									}

									if ((*k)->_mass > (*j)->_mass * 1.2f)
									{
										(*k)->_mass += (*j)->_mass;
										hero._mass -= (*j)->_mass;
										j = hero.pieces.erase(j);
										if (hero.pieces.empty())
										{
											_GameOver = true;
											break;
										}
										heroPieceEaten = true;
										break;

									}
								}
								++k;

							}
							if (!heroPieceEaten)
								++j;
							if (botsEaten)
								break;
							if (_GameOver)break;
						}
						if (_GameOver)break;
						if (botsEaten)
							continue;

					}
					else
					{
						bool botsEaten = false;
						for (auto& j = hero.pieces.begin(); j != hero.pieces.end();)
						{
							if ((*j)->isCollision(**i, -min((*i)->getRadius(), (*j)->getRadius())))
							{
								if ((*j)->_mass > (*i)->_mass * 1.2f)
								{
									(*j)->_mass += (*i)->_mass;
								/*	cout << "Bot " << i->getDescription() << " was eaten by HeroPiece " << j->getDescription() << endl;*/
									i = bots.erase(i);
									botsEaten = true;
									break;
								}

								if ((*i)->_mass > (*j)->_mass * 1.2f)
								{
									(*i)->_mass += (*j)->_mass;
									hero._mass -= (*j)->_mass;
									j = hero.pieces.erase(j);
									if (hero.pieces.empty())
									{
										_GameOver = true;
										break;
									}
										
									continue;
								}
								
							}
							++j;
						}
						if (_GameOver)break;
						if (botsEaten)
							continue;

					}
				}
				else
				{
					if (dynamic_cast<Server::Hero*>((*i).get())->Splitted)
					{
						for (auto& j = dynamic_cast<Server::Hero*>((*i).get())->pieces.begin(); j != dynamic_cast<Server::Hero*>((*i).get())->pieces.end();)
						{
							if (hero.isCollision(**j, -min((*j)->getRadius(), hero.getRadius())))
							{
								if (hero._mass > (*j)->_mass * 1.2f)
								{
									hero._mass += (*j)->_mass;
									(*i)->_mass -= (*j)->_mass;
									j = dynamic_cast<Server::Hero*>((*i).get())->pieces.erase(j);
									continue;
								}

								if ((*j)->_mass > hero._mass * 1.2f)
								{
									(*j)->_mass += hero._mass;
									_GameOver = true;
								}


							}
							++j;
						}
					}
					else
					{
						if (hero.isCollision(**i, -min((*i)->getRadius(), hero.getRadius())))
						{
							if (hero._mass > (*i)->_mass * 1.2f)
							{
								hero._mass += (*i)->_mass;
								/*cout << "Bot " << i->getDescription() << " was eaten by Hero " << hero.getDescription() << endl;*/
								i = bots.erase(i);
								continue;
							}

							if ((*i)->_mass > hero._mass * 1.2f)
							{
								(*i)->_mass += hero._mass;
								_GameOver = true;
							}


						}
					}
				}

			}
			++i;
			///*if (botsEaten)
			//	i = bots.erase(i);*/
			//else ++i;
		}
		
		//if (hero.Splitted)
		//{
		///*	for (const auto& piece : hero.pieces)
		//	{
		//		auto p = dynamic_pointer_cast<Server::Hero> (bot);
		//		piece->name.setPosition(b->getCenter().x - b->name.getLocalBounds().width / 2, b->getCenter().y - b->name.getLocalBounds().height / 2);
		//	}*/
		//}

			
			
		
		/*for (const auto& bot : bots)
		{
			auto b = dynamic_pointer_cast<Server::Hero> (bot);
			b->name.setPosition(b->getCenter().x - b->name.getLocalBounds().width / 2, b->getCenter().y - b->name.getLocalBounds().height / 2);
		}*/
		
	}


}
