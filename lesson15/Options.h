#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
using namespace sf;
using namespace std;
extern Font _Font;
class Options
{
public:
	Options();
	bool PosSlider(float x, float y);
	bool PosBox(float x, float  y);
	bool PosKey(Text text, float x, float  y);
	bool PosButtonClose(float x, float y);
	bool PosButtonSave(float x, float y);
	void Saved();
	static void OpenSaved(const char* file);
	
	//static void OpenSaved(const char *file);
    
	//void MoveRegulator(RectangleShape& reg);
	void CreateMus();
	Text  CreateTitle(const wstring text, int size);
	RectangleShape  CreateLineMus();
	RectangleShape  CreateRegulator();
	void moveSlider(int mouseX);
	RectangleShape CreateCheckBox();
	RectangleShape CreateCheckMarkLine1();
	RectangleShape CreateCheckMarkLine2();
	Text handleKeyPressed(int code);
	
	//static Text SpliteKeyCode;
	//static bool _isKeySpliteChanged;
	static int SplitedKeyCode;
	static int FeededKeyCode;
	static float volume;
	static bool _isBoxPressed;
	static bool _isSaveActive;
	static Music music;
	static bool _isKeySpliteChanged;
	static bool _isKeyFeedingChanged;
	static bool _IsButtonClosePressed;
protected:

	bool _isSliderPressed = false;

	RectangleShape BackGround;
	RectangleShape	_LineMus;
	RectangleShape _Regulator;
	RectangleShape _Box;
	RectangleShape _CheckMark1;
	RectangleShape _CheckMark2;
	//float volume;
	
	Text Setting;
	Text Setting_1;
	Text Setting_2;
	Text Setting_3;
	Text Setting_4;
	Text Save;
	float tempvol;
    bool tempbool;
	
	//Text Splite;
	Text FeedingKeyCode;
	Text SpliteKeyCode;
	//int FeededKeyCode;
	Sprite Close;
	Sprite SP;
	//bool _isBoxPressed = false;
	Texture SettingPicture;
	Texture ButtonClose;
	
};

