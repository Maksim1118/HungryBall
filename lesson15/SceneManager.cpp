#include "SceneManager.h"
#include "MainScene.h"
#include "GameScene.h"
#include "SettingScene.h"



SceneManager::SceneManager()
{
	_GameScene = new GameScene(this);
	//_SettingScene = new SettingScene(this);
	_MainScene = new MainScene(this);

	_current = _MainScene;
}
SceneManager::~SceneManager()
{
	delete _MainScene;
	delete _GameScene;
	//delete _SettingScene;

}
Scene* SceneManager::GetCurrent()
{

	return _current;
}
void SceneManager::SetMainScene()
{
	_current = _MainScene;
	
}
void SceneManager::SetGameScene()
{
	_current = _GameScene;
	
}
/*void SceneManager::SetSettingScene()
{
	_current = _SettingScene;
	
}*/