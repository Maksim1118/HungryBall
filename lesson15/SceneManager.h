#pragma once
#include "Scene.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	Scene* GetCurrent();
	void SetMainScene();
	void SetGameScene();
	void SetSettingScene();

private:
	Scene* _MainScene;
	Scene* _GameScene;
	//Scene* _SettingScene;
	
	Scene* _current;
	bool _isSettingSceneVisible;
};

