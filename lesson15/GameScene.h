#pragma once
#include "Scene.h"
#include "Food.h"
#include "Hero.h"
#include "Thorn.h"
#include "SettingScene.h"
const int ArrFoodSize = 500;
const int SetPosFood = 1190;
const int SetPosThorn = 1100;
class SceneManager;
class GameScene : public Scene
{
public:
	GameScene(SceneManager* manager);
	
	

	virtual void HandleEvent(Event event, Vector2f mousePos);
	virtual void draw(RenderWindow& window);
	virtual void TimeElapsed(int diff);
	
private:
	SceneManager *_manager;

	Texture fieldBG;

	Sprite fieldBGSprite;

	Thorn thornSprite[ThornSpriteSize];
		
	Food arrFood[ArrFoodSize];
	
	Hero hero;


	
	
};

