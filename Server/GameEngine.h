#pragma once
#include "FoodServer.h"
#include "HeroServer.h"
#include "ThornServer.h"
//#include "SettingScene.h"
#include "nlohmann\json.hpp"

namespace  Server
{
	void runServer();
	constexpr auto ArrFoodSize = 500;
	constexpr int SetPosFood = 1190;
	constexpr int SetPosThorn = 1100;
	class SceneManager;
	class GameEngine
	{
	public:
		GameEngine();

		nlohmann::json process(nlohmann::json request);
		bool isCollWithMap(const Vector2f& pos);
		Vector2f getCoorCollWithMap(const  Vector2f& pos);
		virtual void TimeElapsed(int& diff);


		bool _GameOver = false;
		bool thornEaten = false;

		list<shared_ptr<Objects>> _ThornSprite{};

		list<shared_ptr<Objects>> _Food{};

		Hero hero;

		list<shared_ptr<Objects>> bots{};
	private:

	
	

	};

}

