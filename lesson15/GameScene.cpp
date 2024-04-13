#include "GameScene.h"
#include "SceneManager.h"
#include <ctime>
#include "Base.h"
#include "SettingScene.h"
//bool SettingScene::_isKeySpliteChanged = false;
int Options::SplitedKeyCode;

//Text SettingScene::SpliteKeyCode;
GameScene::GameScene(SceneManager* manager)
{
	if (!fieldBG.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\fieldBG.png"))
	{

	}
	
	fieldBGSprite.setTexture(fieldBG);

	_manager = manager;

	srand(time(NULL));

	hero.setPosition(rand() % 1100, rand() % 1100);

	

	for ( int i = 0; i < ThornSpriteSize; i++)
	{
		

		
		thornSprite[i].setPosition(rand() % SetPosThorn,rand() % SetPosThorn);

		for (int j = 0; j < i; j++)
		{
			const Vector2f Pos1 = thornSprite[i].getPosition();
			const Vector2f Pos2 = thornSprite[j].getPosition();

			if (sqrt((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y)) < ThornSpriteR  * 2)
			{
				i--;
				break;
			}


		}




		

		
		
	}
	for (int i = 0; i < ArrFoodSize; i++)
	{
		arrFood[i].setColor((foodcolor)(rand() % 6));
		arrFood[i].setPosition(rand() % SetPosFood, rand() % SetPosFood);

		for (int j = 0; j < i; j++)
		{
			const Vector2f& Pos1 = arrFood[i].getPosition();
			const Vector2f& Pos2 = arrFood[j].getPosition();

			if (sqrt((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y)) < FoodRadius *2)
			{
				i--;
				break;
			}


		}

		for (int j = 0; j < ThornSpriteSize; j++)
		{
			const Vector2f& Pos1 = arrFood[i].getPosition();
			const Vector2f& Pos2 = thornSprite[j].getPosition();
			
			if (sqrt((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y)) < ThornSpriteR * 2 + FoodRadius * 2 + 2)
			{
				i--;
				break;
			}

			
		}


	}

	
	

	
	
	
	
	_manager = manager;


}

void GameScene::HandleEvent(Event event, Vector2f mousePos)
{
	
	if (event.type == sf::Event::KeyPressed)

	{
		
		if (event.key.scancode == sf::Keyboard::Scan::Escape)

		{
			_manager->SetMainScene();

		}
		if (event.key.code == Options::SplitedKeyCode)
			hero.setSplite();
		if (event.key.code == Options::FeededKeyCode)
		{
		
			hero.setFeeded();			
		}
		/*if (SettingScene::_isKeySpliteChanged == false)
		{

			//string text = SettingScene::SpliteKeyCode.getString();
			//int keycode = stoi(text);
		
		}*/
		/*else if (event.key.scancode == sf::Keyboard::Scan::Space)
		{
			hero.setSplite();
		}*/
	}
	if (event.type == sf::Event::MouseMoved)
	{
		hero.setPosMouse(mousePos.x, mousePos.y);
	}
}
void GameScene::TimeElapsed(int diff)
{
	hero.TimeElapsed(diff);
	for (int i = 0; i < ArrFoodSize; i++)
	{
		if (arrFood[i].active != true)
		{
			continue;
		}
		if (hero.Splitted)
		{
			for (auto& Piece : hero.pieces)
			{
				if (Piece._mass > GetLen(Piece.getCenter(), arrFood[i].getPosition() + Vector2f(FoodRadius, FoodRadius)))
				{
					hero._mass += 1.000f;
					Piece._mass += 1.000f;
					arrFood[i].active = false;
				}
			}
		}
		else
		{
			if (hero._mass > GetLen(hero.getCenter(), arrFood[i].getPosition() + Vector2f(FoodRadius, FoodRadius)))
			{
				hero._mass += 1.000f;
				arrFood[i].active = false;
			}
		}
	}
	for (int i = 0; i < ThornSpriteSize; i++)
	{

		if (thornSprite[i].ActiveThorn != true)
		{
			continue;
		}
		if (hero._mass > GetLen(hero.getCenter(), thornSprite[i].getPosition() + Vector2f(ThornSpriteR, ThornSpriteR)) && hero._mass > ThornSpriteR * 1.18f)
		{
			hero._mass += 7.000f;
			thornSprite[i].ActiveThorn = false;
			hero.setWeakened();

		}
	}

}
void GameScene::draw(RenderWindow& window)
{	

	window.draw(fieldBGSprite);
	
	for (int i = 0; i < ArrFoodSize; i++)
	{
		if (arrFood[i].active != true)
		{
			continue;
		}
		arrFood[i].draw(window);
		
	}
	if (hero._mass <= ThornSpriteR)
	{
		hero.draw(window);
		

			
		
	}
	for (int i = 0; i < ThornSpriteSize; i++)
	{
		if (thornSprite[i].ActiveThorn != true)
		{
			continue;
		}
		thornSprite[i].draw(window);

		
	}
	/*if (hero._mass > ThornSpriteR)
	{
		for (int i = 0; i < ThornSpriteSize; i++)
		{
			float temp = hero._mass;
			if (thornSprite[i].ActiveThorn != true)
			
			{
				
				int j = hero._mass / 20;
				if (j < 6)
				{
					int new_mass = hero._mass / j;

					for (int k = 0; k < j; k++)
					{
						
						
						int rand_mass = 20 + rand() % (new_mass - 20);
						if (k > 0)
						{
							hero._mass = 20 + rand() % (new_mass - rand_mass);
						}
						else
						{
							hero._mass = rand_mass;
						}
						
						hero.draw(window);
					}

				}
				else
				{
					
					
					int new_mass = hero._mass / (j - 6);
					for (int k = 0; k < 6; k++)
					{
						

						int rand_mass = 20 + rand() % (new_mass - 20);

						if (k > 0)
						{
							hero._mass = 20 + rand() % (new_mass - rand_mass);
						}
						else
						{
							hero._mass = rand_mass;
						}
						hero.draw(window);
					}
				}
			}
			else
			{
				hero._mass = temp;

				
			}
		}
		
	}*/
	if (hero._mass > ThornSpriteR)
	{
		hero.draw(window);




	}
	/*if (hero._mass <= ThornSpriteD / 2)
	{
		hero.draw(window);
	}
	for (int i = 0; i < ThornSpriteSize; i++) 
	{
		thornSprite[i].draw(window);
	}
	if (hero._mass > ThornSpriteD / 2) 
	{
		hero.draw(window);
	}*/
		
	
	
	
	
	
	

}
