#pragma once
#include "Scene.h"
#include "Options.h"
#include <list>
#include <SFML/Audio.hpp>
//extern Font _Font;
class SceneManager;
class SettingScene : public Scene, public Options
{
public: 
	SettingScene();
	virtual void HandleEvent(Event event, Vector2f mousePos);
	virtual void TimeElapsed(int diff);
	virtual void draw(RenderWindow& window);
	
	/*bool PosSlider(float x, float y);
	bool PosBox(float x, float  y);
	bool PosKey(Text text, float x, float  y);
	bool PosButtonClose(float x, float y);

	//void MoveRegulator(RectangleShape& reg);
	void CreateMus();
	Text  CreateTitle(const wstring text, int size);
	RectangleShape  CreateLineMus();
	RectangleShape  CreateRegulator();
	void moveSlider(int mouseX);
	RectangleShape CreateCheckBox();
	RectangleShape CreateCheckMarkLine1();
	RectangleShape CreateCheckMarkLine2();
	Text handleKeyPressed(Keyboard::Key code);
	//static Text SpliteKeyCode;
	//static bool _isKeySpliteChanged;
	static int SplitedKeyCode;
	//static int FeededKeyCode;
	static bool _isBoxPressed;
	static Music music;*/
private:
	//SceneManager* _manager;
	
	//Options _option;
	/*RectangleShape BackGround;
	RectangleShape	_LineMus;
	RectangleShape _Regulator;
	RectangleShape _Box;
	RectangleShape _CheckMark1;
	RectangleShape _CheckMark2;
	Text Setting;
	Text Setting_1;
	Text Setting_2;
	Text Setting_3;
	Text Setting_4;
	//Text Splite;
	Text FeedingKeyCode;
	Text SpliteKeyCode;
	int FeededKeyCode;
	bool _isKeySpliteChanged = false;
	bool _isKeyFeedingChanged = false;
	bool _isSliderPressed  = false;
	//bool _isBoxPressed = false;
	Texture SettingPicture;
	Texture ButtonClose;
	Sprite Close;
	Sprite SP;*/
	
};

