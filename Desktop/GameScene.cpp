#include "GameScene.h"
#include "SceneManager.h"
//#include "BaseOld.h"
#include "SettingScene.h"
#include "Message.h"

#include <ctime>
#include<iostream>
#include <chrono>
//bool SettingScene::_isKeySpliteChanged = false;
int Options::SplitedKeyCode;
extern bool thornEeaten;
//Text SettingScene::SpliteKeyCode;
GameScene::GameScene(SceneManager* manager): _manager(manager) /*hero(_Food)*/
{
	/*if (!_Font.loadFromFile("D:\\изучение c++\\ofont.ru_Europe.ttf"))
	{
		cerr << "not found font GameScene";
		exit(1);
	}*/
	
	text.setString(L"Вы Проиграли");
	text.setFont(*rec.font);
	text.setCharacterSize(80);
	text.setFillColor(Color::Red);

	HeroMass.setFont(*rec.font);
	HeroMass.setCharacterSize(28);
	HeroMass.setPosition(20, 50);
	HeroMass.setFillColor(Color::Black);
	

	_GameOver = false;
	/*if (!fieldBG.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\fieldBG.png"))
	{
		cerr << "not found field GameScene";
	}*/

	
	
 	fieldBGSprite.setTexture(*rec.textures[ResourceManager::Textures::FIELD]);
	/*BotsColor colB = (BotsColor)(rand() % 6);*/
	/*_manager = manager;*/

	/*srand(time(NULL));

	float xHero = (float)(rand() % 1100);
	float yHero = (float)(rand() % 1100);
	hero.setCenter(xHero, yHero);*/

	/*for (int i = 0; i < 10; i++)
	{

		bots.emplace_back(_Food);
	}*/

	/*for (int i = 0; i < bots.size(); i++)
	{
		BotsColor colB = (BotsColor)(rand() % 6);
		bots[i].setColor(colB);
		float xBot = (float)(rand() % 1100);
		float yBot = (float)(rand() % 1100);
		bots[i].setCenter(xBot, yBot);
		if (bots[i].isCollision(hero, 2))
		{
			i--;
			break;
		}
		for (int j = 0; j < i; j++)
		{
			if (bots[i].isCollision(bots[j], 2))
			{
				i--;
				break;
			}
		}

	}*/

	//for ( int i = 0; i < ThornSpriteSize; ++i)
	//	_ThornSprite.emplace_back();

	//for (auto& i = _ThornSprite.begin(); i != _ThornSprite.end(); ++i)
	//{
	//	float xThorn = (float)(rand() % (int)(Options::_WindowWidth - _ThornSpriteR));
	//	float yThorn = (float)(rand() % (int)(Options::_WindowHeight - _ThornSpriteR));
	//	i->setCenter(xThorn, yThorn);

	//	for (auto& j = _ThornSprite.begin(); j != i; ++j)
	//	{
	//		/*const Vector2f Pos1 = thornSprite[i].getCenter();
	//		const Vector2f Pos2 = thornSprite[j].getCenter();*/

	//		if (i->isCollision(*j, 2))
	//		{
	//			i--;
	//			break;
	//		}


	//	}
	//}
		
		
	
	/*for (int i = 0; i < ArrFoodSize; ++i)
		_Food.emplace_back(new Food());*/
	//for (auto& i = _Food.begin(); i != _Food.end(); ++i)
	//{
	//	//Food newFood;
	//	foodcolor colF = (foodcolor)(rand() % 6);
	//    (*i)->setColor(colF);
	//	float xFood = (float)(rand() % SetPosFood);
	//	float yFood = (float)(rand() % SetPosFood);
	//	(*i)->setCenter(xFood,yFood);
	//	/*if (_Food.size() == 0)
	//	{
	//		_Food.push_back(newFood);
	//		continue;
	//	}*/
	//	for (auto& j = _Food.begin(); j != i; ++j)
	//	{
	//		//const Vector2f& Pos1 = arrFood[i].getCenter();
	//		//const Vector2f& Pos2 = arrFood[j].getCenter();

	//		if ((*i)->isCollision(**j, 2))
	//		{
	//			i--;
	//			break;
	//		}
	//		//_Food.push_back(newFood);
	//	}

	//	//for (int j = 0; j < ThornSpriteSize; j++)
	//	//{
	//	//	//const Vector2f& Pos1 = arrFood[i].getCenter();
	//	//	//const Vector2f& Pos2 = thornSprite[j].getCenter();
	//	//	
	//	//	/*if (food.isCollision(thornSprite[j], 2))
	//	//	{
	//	//		i--;
	//	//		break;
	//	//	}*/

	//	//	
	//	//}
	//	

	//}

	/*_manager = manager;*/


}

void GameScene::HandleEvent(Event& event, Vector2f& mousePos)
{

	nlohmann::json request;
	if (event.type == sf::Event::KeyPressed)
	{
		
		if (event.key.scancode == sf::Keyboard::Scan::Escape)
		{
			_manager->SetMainScene();
		}
		if (event.key.code == Options::SplitedKeyCode)	/*_Engine.hero.setSplite();*/
		{
			/*request["id"] = _Engine.hero.getID();*/
			
			request["action"] = "split";
			nlohmann::json response = message.process(request);
			
		}
		if (event.key.code == Options::FeededKeyCode)
		{		
			/*request["id"] = _Engine.hero.getID();*/
			request["action"] = "feed";
			nlohmann::json response = message.process(request);
			/*_Engine.hero.setFeeded();*/
		}
		/*if (SettingScene::_isKeySpliteChanged == false)
		{

			string text = SettingScene::SpliteKeyCode.getString();
			int keycode = stoi(text);
		
		}
		else if (event.key.scancode == sf::Keyboard::Scan::Space)
		{
			_Engine.hero.setSplite();
		}*/
	}
	if (event.type == sf::Event::MouseMoved)
	{
		request["action"] = "ask pos mouse";
		request["mousePosition"] = { {"x",mousePos.x}, {"y", mousePos.y} };
		nlohmann::json response = message.process(request);
		/*_Engine.hero.setPosMouse(mousePos.x, mousePos.y);*/
	}
	
}

//bool GameScene::isCollWithMap(Vector2f& pos)
//{
//	return (pos.x < 0) || (pos.x > Options::_WindowWidth) || (pos.y < 0) || (pos.y > Options::_WindowHeight) ? true : false;
//}
//Vector2f GameScene::getCoorCollWithMap(Vector2f& pos)
//{
//	if (pos.x < 0)
//		return Vector2f(0, pos.y);
//	else if (pos.x > Options::_WindowWidth)
//		return Vector2f(Options::_WindowWidth, pos.y);
//	else if (pos.y < 0)
//		return  Vector2f(pos.x, 0);
//	else if (pos.y > Options::_WindowHeight)
//		return Vector2f(pos.x, Options::_WindowHeight);
//}
void GameScene::TimeElapsed(int& diff)
{
	/*_Engine.TimeElapsed(diff);*/
	//if(!_GameOver)
	//	hero.TimeElapsed(diff);
	//if(isCollWithMap(hero.getCenter()))
	//	hero.setCenter(getCoorCollWithMap(hero.getCenter()));
	//
	//for (auto& f : hero.feeds)
	//{
	//	if (isCollWithMap(f->getCenter()))
	//		f->setCenter(getCoorCollWithMap(f->getCenter()));f
	//}
	//for (auto& b : bots)
	//{
	//	if (isCollWithMap(b.getCenter()))
	//		b.setCenter(getCoorCollWithMap(b.getCenter()));		
	//}
	//for (auto& Piece : hero.pieces)
	//{
	//	if (isCollWithMap(Piece.getCenter()))
	//		Piece.setCenter(getCoorCollWithMap(Piece.getCenter()));

	//}
	//
	//
	//for (int i = 0; i < bots.size(); i++)
	//{	

	//	Vector2f to;
	//	for (auto& j = _Food.begin(); j != _Food.end(); ++j)
	//	{
	//		/*if (arrFood[j].active != true)
	//		{
	//			continue;
	//		}*/
	//		Vector2f distance = (*j)->getCenter() - bots[i].getCenter();
	//		float lenD = GetLen(distance);
	//		distance /= lenD;
	//		distance /= lenD;
	//		distance /= lenD;
	//		to += distance;
	//	}
	///*	if (bots[i]._mass < _ThornSpriteMass * 1.2f) 
	//	{
	//		
	//	}
	//	else*/
	//	{
	//		for (auto& j = _ThornSprite.begin(); j != _ThornSprite.end(); ++j)
	//		{
	//			/*if (arrFood[j].active != true)
	//			{
	//				continue;
	//			}*/
	//			Vector2f distance = j->getCenter() - bots[i].getCenter();
	//			float lenD = GetLen(distance);
	//			if (lenD < bots[i].getRadius() + _ThornSpriteR - 10)
	//			{
	//				distance /= lenD;
	//				distance /= lenD;
	//				distance /= lenD;
	//				to -= distance * 4.f;
	//			}			
	//		}
	//	}
	//	
	//	to = getIdentityVector(to)  * 100.f +  bots[i].getCenter();
	//	bots[i].setPosMouse(to.x, to.y);
	//	bots[i].TimeElapsed(diff);
	//	
	//}
	//for (auto &i = _Food.begin(); i != _Food.end();)
	//{
	///*	if (arrFood[i].active != true)
	//	{
	//		continue;
	//	}*/
	//	bool foodEaten = false;
	//	if (hero.Splitted)
	//	{
	//		for (auto& Piece : hero.pieces)
	//		{
	//			if (Piece.isCollision(**i))
	//			{
	//				hero._mass += _FoodMass;
	//				Piece._mass += _FoodMass;
	//				//arrFood[i].active = false;
	//				delete* i;
	//				i = _Food.erase(i);
	//				foodEaten = true;
	//				break;
	//			}
	//			
	//			/*if (Piece.getCenter().x < 0)
	//				Piece.setCenter(0, Piece.getCenter().y);
	//			else if (Piece.getCenter().x > Options::_WindowWidth)
	//				Piece.setCenter(Options::_WindowWidth, Piece.getCenter().y);
	//			else if (Piece.getCenter().y < 0)
	//				Piece.setCenter(Piece.getCenter().x, 0);
	//			else if (Piece.getCenter().y > Options::_WindowHeight)
	//				Piece.setCenter(Piece.getCenter().x, Options::_WindowHeight);*/
	//			
	//		}

	//	}
	//	else
	//	{
	//		if (hero.isCollision(**i, -(*i)->getRadius()))
	//		{
	//			hero._mass += 20*_FoodMass;
	//			//arrFood[i].active = false;
	//			delete* i;
	//			i = _Food.erase(i);
	//			foodEaten = true;
	//		}
	//		
	//	}
	//	if (!foodEaten)
	//	{
	//		for (int j = 0; j < bots.size(); j++)
	//		{

	//			//if (arrFood[i].active != true)
	//			//{
	//			//	continue;
	//			//}
	//			if (bots[j].isCollision(**i, -(*i)->getRadius()))
	//			{
	//				bots[j]._mass += 5 * _FoodMass;
	//				//arrFood[i].active = false;
	//				delete* i;
	//				i = _Food.erase(i);
	//			    foodEaten = true;
	//				break;
	//			}
	//			
	//		}
	//		if(!foodEaten)
	//			(*i)->TimeElapsed(diff);
	//	}
	//	if (!foodEaten) ++i;
	//	
	//	
	//}
	//for (auto& i = _ThornSprite.begin(); i != _ThornSprite.end();)
	//{

	//	/*if (thornSprite[i].ActiveThorn != true)
	//	{
	//		continue;
	//	}*/
	//	bool thornEaten = false;
	//	if (hero.Splitted)
	//	{
	//		for (auto& Piece : hero.pieces)
	//		{
	//			if (Piece.isCollision(*i, -i->getRadius()) && Piece._mass > _ThornSpriteMass * 1.2f)
	//			{
	//				hero._mass += _ThornSpriteMass;
	//				Piece._mass += _ThornSpriteMass;
	//				i = _ThornSprite.erase(i);
	//				
	//				thornEaten = true;
	//				break;

	//			}
	//			
	//		}
	//	}
	//	else 
	//	{
	//		
	//		if (hero.isCollision(*i, -i->getRadius()) && hero._mass > _ThornSpriteMass * 1.2f)
	//		{
	//			hero._mass += _ThornSpriteMass;
	//			i = _ThornSprite.erase(i);
	//			hero.setWeakened();
	//			thornEaten = true;
	//		}
	//		
	//	}
	//	if (!thornEaten)
	//	{
	//		for (auto& b : bots)
	//		{
	//			if (b.isCollision(*i, -i->getRadius()) && b._mass > _ThornSpriteMass * 1.2f)
	//			{
	//				b._mass += _ThornSpriteMass;
	//				//thornSprite[i].ActiveThorn = false;
	//				i = _ThornSprite.erase(i);
	//				b.setWeakened();
	//				thornEaten = true;
	//				break;
	//			}
	//			
	//		}
	//	}
	//	if (!thornEaten) ++i;

	//	
	//}
	//for (auto& i = bots.begin(); i != bots.end();)
	//{
	//	bool botsEaten = false;
	//	for (auto& j = bots.begin(); j != bots.end();)
	//	{
	//		if (j->isCollision(*i, -min(i->getRadius(), j->getRadius())))
	//		{
	//			if(j->_mass > i->_mass * 1.2f)
	//			{
	//			    j->_mass += i->_mass;
	//				i = bots.erase(i);
	//				botsEaten = true;
	//				break;
	//			}

	//			if (i->_mass > j->_mass * 1.2f)
	//			{
	//				i->_mass += j->_mass;
	//				j = bots.erase(j);
	//				continue;
	//			}
	//		}
	//		++j;
	//	}
	//	
	//	if(botsEaten)
	//		continue;
	//	if (!_GameOver)
	//	{
	//		if (hero.Splitted)
	//		{
	//			if (i->Splitted)
	//			{

	//				for (auto& j = hero.pieces.begin(); j != hero.pieces.end();)
	//				{
	//					bool heroPieceEaten = false;
	//					for (auto& k = i->pieces.begin(); k != i->pieces.end();)
	//					{
	//						if (k->isCollision(*j, -min(k->getRadius(), j->getRadius())))
	//						{
	//							if (j->_mass > k->_mass * 1.2f)
	//							{
	//								j->_mass += k->_mass;
	//								i->_mass -= k->_mass;
	//								k = i->pieces.erase(k);
	//								if (i->pieces.empty())
	//								{
	//									botsEaten = true;
	//								}
	//								continue;
	//							}

	//							if (k->_mass > j->_mass * 1.2f)
	//							{
	//								k->_mass += j->_mass;
	//								hero._mass -= j->_mass;
	//								j = hero.pieces.erase(j);
	//								if (hero.pieces.empty())
	//								{
	//									_GameOver = true;
	//								}
	//								heroPieceEaten = true;
	//								break;
	//								
	//							}
	//						}
	//						++k;
	//						
	//					}
	//					if(!heroPieceEaten)
	//						++j;
	//				}
	//				
	//			}
	//			else
	//			{
	//				bool botsEaten = false;
	//				for (auto& j = hero.pieces.begin(); j != hero.pieces.end();)
	//				{
	//					if (j->isCollision(*i, -min(i->getRadius(), j->getRadius())))
	//					{
	//						if (j->_mass > i->_mass * 1.2f)
	//						{
	//							j->_mass += i->_mass;
	//							i = bots.erase(i);
	//							botsEaten = true;
	//							break;
	//						}

	//						if (i->_mass > j->_mass * 1.2f)
	//						{
	//							i->_mass += j->_mass;
	//							hero._mass -= j->_mass;
	//							j = hero.pieces.erase(j);
	//							if(hero.pieces.empty())
	//								_GameOver = true;
	//							continue;
	//						}
	//					}
	//					++j;
	//				}
	//			if(botsEaten)
	//				continue;
	//				
	//			}
	//		}
	//		else
	//		{
	//			if (i->Splitted)
	//			{
	//				for (auto& j = i->pieces.begin(); j != i->pieces.end();)
	//				{
	//					if (hero.isCollision(*j, -min(j->getRadius(), hero.getRadius())))
	//					{
	//						if (hero._mass > j->_mass * 1.2f)
	//						{
	//							hero._mass += j->_mass;
	//							i->_mass -= j->_mass;
	//							j = i->pieces.erase(j);
	//							continue;
	//						}

	//						if (j->_mass > hero._mass * 1.2f)
	//						{
	//							j->_mass += hero._mass;
	//							_GameOver = true;
	//						}


	//					}
	//					++j;
	//				}
	//			}
	//			else
	//			{
	//				if (hero.isCollision(*i, -min(i->getRadius(), hero.getRadius())))
	//				{
	//					if (hero._mass > i->_mass * 1.2f)
	//					{
	//						hero._mass += i->_mass;
	//						i = bots.erase(i);
	//						continue;
	//					}

	//					if (i->_mass > hero._mass * 1.2f)
	//					{
	//						i->_mass += hero._mass;
	//						_GameOver = true;
	//					}


	//				}
	//			}
	//		}
	//		
	//	}
	//	if (botsEaten)
	//		i = bots.erase(i);
	//	else ++i;9
	//}

}
void GameScene::draw(RenderWindow& window)
{	
	vector<Objects*> objects{};
	nlohmann::json listObjects;
	listObjects["action"] = "get object";
	nlohmann::json response = message.process(listObjects);
	
	

	/*nlohmann::json response = _Engine.process(listObjects);*/
	/*cout << response.dump(3);*/

	if (response.contains("listFood"))
	{
		for (const auto& obj : response["listFood"])
		{
			Food* _food = new Food(Vector2f(obj["Center"]["x"], obj["Center"]["y"]), obj["Radius"]);
			_food->setColor(obj["Color"]);
			objects.push_back(_food);
		}
	}

	/*for (auto& f : _Engine._Food)
	{
		Food* _food = new Food(f->getCenter(), f->getRadius());
		objects.push_back(_food);
		_food->setColor(dynamic_cast<Server::Food*>(f.get())->colorNum);
		
	}*/
	

	if (response.contains("listThorn"))
	{
		for (const auto& obj : response["listThorn"])
		{
			Thorn* _thorn = new Thorn(Vector2f(obj["Center"]["x"], obj["Center"]["y"]), obj["Radius"]);
			objects.push_back(_thorn);
		}
	}
	//for (auto& t : _Engine._ThornSprite)
	//	objects.push_back(new Thorn(t->getCenter(), t->getRadius()));
	if (response.contains("listBot"))
	{
		for (const auto& obj : response["listBot"])
		{
			if (obj["Splitted"] == true)
			{
				for (auto& p : obj["Pieces"])
					objects.push_back(new Hero::Piece(Vector2f(p["Center"]["x"], p["Center"]["y"]),p["Radius"], p["Color"]));
			}
			else
			{
				objects.push_back(new Hero(Vector2f(obj["Center"]["x"], obj["Center"]["y"]), obj["Radius"], obj["Color"], obj["Name"]));
			}
			
		}
	}

	if (response.contains("Hero"))
	{
		auto obj = response["Hero"];
		HeroMass.setString("mass Hero: " + to_string(static_cast<int>(obj["Mass"])));
		if (obj["Splitted"] == true)
		{
			for (auto& p : obj["Pieces"])
				objects.push_back(new Hero::Piece(Vector2f(p["Center"]["x"], p["Center"]["y"]), p["Radius"], p["Color"]));
		}
		else
		{
			objects.push_back(new Hero(Vector2f(obj["Center"]["x"], obj["Center"]["y"]), obj["Radius"], obj["Color"], obj["Name"]));
		}

		if (obj["Feeded"] == true)
		{
			for (const auto& f : obj["Feeds"])
				objects.push_back(new Hero::Feed(Vector2f(f["Center"]["x"], f["Center"]["y"]), f["Radius"]));
		}
	}
	//for (auto& b : _Engine.bots)
	//{
	//	Server::Hero* bot = dynamic_cast<Server::Hero*>(b.get());
	//	if (bot->Splitted)
	//	{
	//		for(auto& p: bot->pieces)
	//			objects.push_back(new Hero::Piece(p->getCenter(), p->getRadius(), static_cast<int>(bot->colB)));
	//	}
	//	else 
	//	{
	//		objects.push_back(new Hero(bot->getCenter(), bot->getRadius(), static_cast<int>(bot->colB),bot->name));
	//	}
	//	
	//	
	//}
	//if (_Engine.hero.Splitted)
	//{
	//	for (auto& p : _Engine.hero.pieces)
	//		objects.push_back(new Hero::Piece(p->getCenter(), p->getRadius(), static_cast<int>(_Engine.hero.colB)));
	//}
	//else
	//{
	//	objects.push_back(new Hero(_Engine.hero.getCenter(), _Engine.hero.getRadius(), static_cast<int>(_Engine.hero.colB), _Engine.hero.name));
	//}
	//
	//if (_Engine.hero.Feeded)
	//	for (const auto& f : _Engine.hero.feeds)
	//		objects.push_back(new Hero::Feed(f->getCenter(), f->getRadius()));
	//

	window.draw(fieldBGSprite);	
	
	sort(objects.begin(), objects.end(), [](const Objects* obj1, const Objects* obj2)
		{
			return obj1->getRadius() < obj2->getRadius();
		}); 

	for (auto& obj : objects)
		obj->draw(window);
	for (auto& obj : objects)
		delete obj;
	objects.clear();
	window.draw(HeroMass);
	


	if (response.contains("Hero") && response["Hero"]["GameOver"])
	{
		text.setPosition(Options::_WindowWidth / 2 - text.getGlobalBounds().width / 2, Options::_WindowHeight/2 - text.getGlobalBounds().height / 2);
		window.draw(text);
	}

	
	

}
