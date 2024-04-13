#include "SettingScene.h"
#include "SceneManager.h"
#include <SFML/Audio.hpp>


//Font _Font;
 int Options::FeededKeyCode;

 //float Options::volume;
SettingScene::SettingScene()
{
	/*BackGround.setSize(Vector2f(800.f, 800.f));
	BackGround.setPosition(200.f, 200.f);
	BackGround.setFillColor(Color(204, 204, 204));*/

	//_manager = manager;
	/*if (!_Font.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\ofont.ru_Europe.ttf"))
	{

		// error...
	}
	if (!ButtonClose.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\ButtonClose.png"))
	{

	}
	if (!SettingPicture.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\setting_picture.png"))
	{

	}

	Close.setTexture(ButtonClose);
	Close.setPosition(200.f + (BackGround.getGlobalBounds().width - Close.getGlobalBounds().width), 200.f);

	SP.setTexture(SettingPicture);
	SP.setPosition(BackGround.getGlobalBounds().width, 950.f -  SP.getGlobalBounds().height);

	Setting = CreateTitle(L"НАСТРОЙКИ", 40);
	Setting.setPosition((1200.f - Setting.getGlobalBounds().width) / 2, 250.f);

	Setting_1 = CreateTitle(L"На Весь Экран:", 25);
	Setting_1.setPosition(300.f, 400.f);

	Setting_2 = CreateTitle(L"Громкость Музыки:", 25);
	Setting_2.setPosition(300.f, 500.f);

	Setting_3 = CreateTitle(L"Деление:", 25);
	Setting_3.setPosition(300.f, 600.f);


	Setting_4 = CreateTitle(L"Прикормка:", 25);
	Setting_4.setPosition(300.f, 700.f);

	SpliteKeyCode = CreateTitle(L"Space", 25);
	SpliteKeyCode.setPosition(330.f + Setting_3.getGlobalBounds().width, 600.f);
	SplitedKeyCode = Keyboard::Key::Space;

	FeedingKeyCode = CreateTitle(L"E", 25);
	FeedingKeyCode.setPosition(330.f + Setting_4.getGlobalBounds().width, 700.f);
	FeededKeyCode = Keyboard::Key::E;

	_LineMus = CreateLineMus();
	_Regulator = CreateRegulator();
	_Box = CreateCheckBox();*/
	
	
}


void SettingScene::HandleEvent(Event event, Vector2f mousePos)
{
	

	if (event.type == Event::MouseMoved)
	{
		
		if (!_isKeySpliteChanged && PosKey(SpliteKeyCode, mousePos.x, mousePos.y))
		{
			SpliteKeyCode.setFillColor(Color::Red);
		}
		else
		{
			SpliteKeyCode.setFillColor(Color::Black);
		}
		if (!_isKeyFeedingChanged && PosKey(FeedingKeyCode, mousePos.x, mousePos.y))
		{
			FeedingKeyCode.setFillColor(Color::Red);
		}
		else
		{
			FeedingKeyCode.setFillColor(Color::Black);
		}
		if (_isSaveActive && PosButtonSave(mousePos.x, mousePos.y))
		{
			Save.setFillColor(Color::Red);
		}
		else if (!_isSaveActive)
		{
			Save.setFillColor(Color(150, 150, 150));
		}
		else  if (_isSaveActive)
		{
			Save.setFillColor(Color::Black);
		}
		
		/*if (_isKeySpliteChanged && PosKey(SpliteKeyCode, event.mouseMove.x, event.mouseMove.y))
		{
			SpliteKeyCode.setFillColor(Color::Red);
		}
		else
		{
			SpliteKeyCode.setFillColor(Color::Black);
		}*/
	


	
	}
	if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
	{
		if (PosSlider(mousePos.x , mousePos.y))
		{
			_isSliderPressed = true;
		}
		if (_isBoxPressed && PosBox(mousePos.x, mousePos.y))
		{
			_isBoxPressed = false;
			if (tempbool == _isBoxPressed)
				_isSaveActive = false;
		}
		else if (PosBox(mousePos.x, mousePos.y))
		{
			_isBoxPressed = true;
			if (tempbool == _isBoxPressed)
				_isSaveActive = false;
			//_CheckMark1 = CreateCheckMarkLine1();
			//_CheckMark2 = CreateCheckMarkLine2();
		}
		if (PosButtonClose(mousePos.x, mousePos.y))
		{
			_IsButtonClosePressed = true;
			//_manager->SetMainScene();
		}
		/*if (!_isKeySpliteChanged && PosKey(Splite, event.mouseButton.x, event.mouseButton.y))
		{	
			_isKeySelected = true;
		    SettingScene::_isKeySpliteChanged = true;
			Splite.setString("");
		}*/
		if (!_isKeyFeedingChanged && PosKey(SpliteKeyCode, mousePos.x, mousePos.y))
		{
			//_isKeySelected = true;
			_isSaveActive = false;
			_isKeySpliteChanged = true;
			SpliteKeyCode.setString("");
		}
		if (!_isKeySpliteChanged && PosKey(FeedingKeyCode, mousePos.x, mousePos.y))
		{
			//_isKeySelected = true;
			_isSaveActive = false;
			_isKeyFeedingChanged = true;
			FeedingKeyCode.setString("");
		}
		if (_isSaveActive && PosButtonSave(mousePos.x, mousePos.y))
		{
			Saved();
			tempvol = volume;
			tempbool = _isBoxPressed;
			_isSaveActive = false;
			//_isSavePressed = true;
		}
	}
	
	if (event.type == Event::MouseButtonReleased && !Mouse::isButtonPressed(Mouse::Left))
	{
		_isSliderPressed = false;
	}
	if (_isSliderPressed && event.type == Event::MouseMoved)
	{
		moveSlider(event.mouseMove.x);
	}
	
	if (event.type == Event::KeyPressed)
	{	
		if (event.key.scancode == sf::Keyboard::Scan::Escape)
		{
		
		
				//_manager->SetMainScene();
			
		}
		if (_isKeySpliteChanged)
		{
			SplitedKeyCode = event.key.code;
			if (SplitedKeyCode != FeededKeyCode)
			{
				SpliteKeyCode = handleKeyPressed(event.key.code);
				SpliteKeyCode.setPosition(330.f + Setting_3.getGlobalBounds().width, 600.f);
				_isSaveActive = true;
				_isKeySpliteChanged = false;
			}
		
			
		}
		
		if (_isKeyFeedingChanged)
		{			
			FeededKeyCode = event.key.code;
			if (SplitedKeyCode != FeededKeyCode)
			{
				FeedingKeyCode = handleKeyPressed(event.key.code);
				FeedingKeyCode.setPosition(330.f + Setting_4.getGlobalBounds().width, 700.f);
				_isSaveActive = true;
				_isKeyFeedingChanged = false;
			}
			
		}
		
		/*if (_isKeySelected)
		{
		
			
		}*/
	}
}
void SettingScene::TimeElapsed(int diff)
{
	if ((tempvol != volume || tempbool != _isBoxPressed) && !_isKeySpliteChanged && !_isKeyFeedingChanged)
	{
		_isSaveActive = true;
	}
	if (_isBoxPressed)
	{
		_CheckMark1 = CreateCheckMarkLine1();
		_CheckMark2 = CreateCheckMarkLine2();
	}
	
	
}
void SettingScene::draw(RenderWindow& window)
{

	window.draw(BackGround);
	window.draw(Setting);
	window.draw(Setting_1);
	window.draw(Setting_2);
	window.draw(Setting_3);
	window.draw(Setting_4);
	window.draw(Save);
	if (!_isKeySpliteChanged)
	{
		window.draw(SpliteKeyCode);
	}
	if (!_isKeyFeedingChanged)
	{
		window.draw(FeedingKeyCode);
	}
	/*else
	{
		window.draw(SpliteKeyCode);
	}*/
	
	window.draw(_LineMus);
	window.draw(_Regulator);
	window.draw(_Box);
	if (_isBoxPressed)
	{
		window.draw(_CheckMark1);
		window.draw(_CheckMark2);
	}
	window.draw(Close);
	window.draw(SP);
	
	
	
}
/*RectangleShape SettingScene::CreateLineMus()
{
	RectangleShape line_mus;
	line_mus.setSize(Vector2f(2.f, 200.f));
	line_mus.setPosition((350.f + Setting_2.getGlobalBounds().width), 505.f + Setting_2.getGlobalBounds().height / 2);
	line_mus.setRotation(270.f);
	return  line_mus;
}
RectangleShape SettingScene::CreateRegulator()
{
	music.setVolume(30.f);
	RectangleShape regulator;
	regulator.setSize(Vector2f(6.f, 30.f));
	regulator.setFillColor(Color(90, 90, 90));
	regulator.setOutlineThickness(2.f);
	regulator.setOutlineColor(Color::Red);
	regulator.setPosition( _LineMus.getPosition().x + _LineMus.getGlobalBounds().width / 100.f * music.getVolume(), _LineMus.getPosition().y - 30.f / 2);
	//printf("%f", music.getVolume());
	return regulator;

}
void SettingScene::moveSlider(int mouseX)
{
	if (mouseX > _LineMus.getPosition().x && mouseX <= _LineMus.getPosition().x + _LineMus.getGlobalBounds().width)
	{
		_Regulator.setPosition(mouseX - _Regulator.getGlobalBounds().width / 2, _Regulator.getPosition().y);
	}
	else if (mouseX <= _LineMus.getPosition().x)
	{
		_Regulator.setPosition(_LineMus.getPosition().x, _Regulator.getPosition().y);
	}
	else if (mouseX > _LineMus.getPosition().x + _LineMus.getGlobalBounds().width)
	{
		_Regulator.setPosition(_LineMus.getPosition().x + _LineMus.getGlobalBounds().width - _Regulator.getGlobalBounds().width / 2, _Regulator.getPosition().y);
	}
}
bool SettingScene::PosSlider(float x, float y)
{
	if (x < _Regulator.getPosition().x - 2.f)
		return false;
	if (x > _Regulator.getPosition().x + _Regulator.getGlobalBounds().width + 2.f)
		return false;
	if (y < _Regulator.getPosition().y - 2.f)
		return false;
	if (y > _Regulator.getPosition().y + _Regulator.getGlobalBounds().height + 2.f)
		return false;
	return true;
}
bool SettingScene::PosBox(float x, float  y)
{

	if (x <= _Box.getPosition().x)
		return false;
	if (x >= _Box.getPosition().x + _Box.getGlobalBounds().width)
		return false;
	if (y <= _Box.getPosition().y)
		return false;
	if (y >= _Box.getPosition().y + _Box.getGlobalBounds().height)
		return false;
	return true;
}
bool SettingScene::PosKey(Text text, float x, float  y)
{
	if (x <= text.getGlobalBounds().left)
		return false;
	if (x >= text.getGlobalBounds().left + text.getGlobalBounds().width)
		return false;
	if (y <= text.getGlobalBounds().top)
		return false;
	if (y >= text.getGlobalBounds().top + text.getGlobalBounds().height)
		return false;
	return true;
}
bool SettingScene::PosButtonClose(float x, float y)
{
	if (x <= Close.getPosition().x)
		return false;
	if (x >= Close.getPosition().x + Close.getGlobalBounds().width)
		return false;
	if (y <= Close.getPosition().y)
		return false;
	if (y >= Close.getPosition().y + Close.getGlobalBounds().height)
		return false;
	return true;
}

RectangleShape SettingScene::CreateCheckBox()
{
	RectangleShape Square;

	Square.setSize(Vector2f(20.f, 20.f));
	Square.setPosition(330.f + Setting_1.getGlobalBounds().width, 406.f);
	Square.setFillColor(Color::Transparent);
	Square.setOutlineThickness(2.f);
	Square.setOutlineColor(Color::Black);
	return Square;
	
}
RectangleShape SettingScene::CreateCheckMarkLine1()
{

	RectangleShape CheckMark(Vector2f(3.f, 25.f));
	CheckMark.setPosition(_Box.getPosition().x + 20.f / 2, _Box.getPosition().y + 20.f / 2);
	CheckMark.setFillColor(Color::Black);
	CheckMark.rotate(150.f);
	return CheckMark;
}
RectangleShape SettingScene::CreateCheckMarkLine2()
{

	RectangleShape CheckMark(Vector2f(3.f, 40.f));
	CheckMark.setPosition(_Box.getPosition().x + 20.f / 2, _Box.getPosition().y + 20.f / 2);
	CheckMark.setFillColor(Color::Black);
	CheckMark.rotate(210.f);
	return CheckMark;
}
Text SettingScene::handleKeyPressed(Keyboard::Key code)
{
	Text key;
	switch (code)
	{
	case Keyboard::A:
		return  key = CreateTitle(L"A", 25);
	case Keyboard::B:
		return  key = CreateTitle(L"B", 25);
	case Keyboard::C:
		return  key = CreateTitle(L"C", 25);
	case Keyboard::D:
		return  key = CreateTitle(L"D", 25);
	case Keyboard::E:
		return  key = CreateTitle(L"E", 25);
	case Keyboard::F:
		return  key = CreateTitle(L"F", 25);
	case Keyboard::G:
		return  key = CreateTitle(L"G", 25);
	case Keyboard::H:
		return  key = CreateTitle(L"H", 25);
	case Keyboard::I:
		return  key = CreateTitle(L"I", 25);
	case Keyboard::J:
		return  key = CreateTitle(L"J", 25);
	case Keyboard::K:
		return  key = CreateTitle(L"K", 25);
	case Keyboard::L:
		return  key = CreateTitle(L"L", 25);
	case Keyboard::M:
		return  key = CreateTitle(L"M", 25);
	case Keyboard::N:
		return  key = CreateTitle(L"N", 25);
	case Keyboard::O:
		return  key = CreateTitle(L"O", 25);
	case Keyboard::P:
		return  key = CreateTitle(L"P", 25);
	case Keyboard::Q:
		return  key = CreateTitle(L"Q", 25);
	case Keyboard::R:
		return  key = CreateTitle(L"R", 25);
	case Keyboard::S:
		return  key = CreateTitle(L"S", 25);
	case Keyboard::T:
		return  key = CreateTitle(L"T", 25);
	case Keyboard::U:
		return  key = CreateTitle(L"U", 25);
	case Keyboard::V:
		return  key = CreateTitle(L"V", 25);
	case Keyboard::W:
		return  key = CreateTitle(L"W", 25);
	case Keyboard::X:
		return  key = CreateTitle(L"X", 25);
	case Keyboard::Y:
		return  key = CreateTitle(L"Y", 25);
	case Keyboard::Z:
		return  key = CreateTitle(L"Z", 25);
	case Keyboard::Num1:
		return  key = CreateTitle(L"Num1", 25);
	case Keyboard::Num2:
		return  key = CreateTitle(L"Num2", 25);
	case Keyboard::Num3:
		return  key = CreateTitle(L"Num3", 25);
	case Keyboard::Num4:
		return  key = CreateTitle(L"Num4", 25);
	case Keyboard::Num5:
		return  key = CreateTitle(L"Num5", 25);
	case Keyboard::Num6:
		return  key = CreateTitle(L"Num6", 25);
	case Keyboard::Num7:
		return  key = CreateTitle(L"Num7", 25);
	case Keyboard::Num8:
		return  key = CreateTitle(L"Num8", 25);
	case Keyboard::Num9:
		return  key = CreateTitle(L"Num9", 25);
	case Keyboard::Num0:
		return  key = CreateTitle(L"Num0", 25);
	case Keyboard::Enter:
		return  key = CreateTitle(L"Enter", 25);
	case Keyboard::BackSpace:
		return  key = CreateTitle(L"BackSpace", 25);
	case Keyboard::Tab:
		return  key = CreateTitle(L"Tab", 25);
	case Keyboard::Space:
		return  key = CreateTitle(L"Space", 25);
	case Keyboard::Hyphen:
		return  key = CreateTitle(L"Hyphen", 25);
	case Keyboard::Equal:
		return  key = CreateTitle(L"Equal", 25);
	case Keyboard::LBracket:
		return  key = CreateTitle(L"LBracket", 25);
	case Keyboard::RBracket:
		return  key = CreateTitle(L"RBracket", 25);
	case Keyboard::Backslash:
		return  key = CreateTitle(L"Backslash", 25);
	case Keyboard::Semicolon:
		return  key = CreateTitle(L"Semicolon", 25);
	case Keyboard::Apostrophe:
		return  key = CreateTitle(L"Apostrophe", 25);
	case Keyboard::Grave:
		return  key = CreateTitle(L"Grave", 25);
	case Keyboard::Comma:
		return  key = CreateTitle(L"Comma", 25);
	case Keyboard::Period:
		return  key = CreateTitle(L"Period", 25);
	case Keyboard::Slash:
		return  key = CreateTitle(L"Slash", 25);
	case Keyboard::LShift:
		return  key = CreateTitle(L"LShift", 25);
	case Keyboard::LControl:
		return  key = CreateTitle(L"LControl", 25);
	case Keyboard::LAlt:
		return  key = CreateTitle(L"LAlt", 25);
	case Keyboard::LSystem:
		return  key = CreateTitle(L"LSystem", 25);
	case Keyboard::RControl:
		return  key = CreateTitle(L"RControl", 25);
	case Keyboard::RShift:
		return  key = CreateTitle(L"RShift", 25);
	case Keyboard::RAlt:
		return  key = CreateTitle(L"RAlt", 25);
	case Keyboard::RSystem:
		return  key = CreateTitle(L"RSystem", 25);
	case Keyboard::Menu:
		return  key = CreateTitle(L"Menu", 25);
	case Keyboard::PageUp:
		return  key = CreateTitle(L"PageUp", 25);
	case Keyboard::PageDown:
		return  key = CreateTitle(L"PageDown", 25);
	case Keyboard::End:
		return  key = CreateTitle(L"End", 25);
	case Keyboard::Home:
		return  key = CreateTitle(L"Home", 25);
	case Keyboard::Insert:
		return  key = CreateTitle(L"Insert", 25);
	case Keyboard::Delete:
		return  key = CreateTitle(L"Delete", 25);
	case Keyboard::Add:
		return  key = CreateTitle(L"Add", 25);
	case Keyboard::Subtract:
		return  key = CreateTitle(L"Subtract", 25);
	case Keyboard::Multiply:
		return  key = CreateTitle(L"Multiply", 25);
	case Keyboard::Divide:
		return  key = CreateTitle(L"Divide", 25);
	case Keyboard::Left:
		return  key = CreateTitle(L"Left", 25);
	case Keyboard::Right:
		return  key = CreateTitle(L"Right", 25);
	case Keyboard::Up:
		return  key = CreateTitle(L"Up", 25);
	case Keyboard::Down:
		return  key = CreateTitle(L"Down", 25);
	case Keyboard::Numpad0:
		return  key = CreateTitle(L"Numpad0", 25);
	case Keyboard::Numpad1:
		return  key = CreateTitle(L"Numpad1", 25);
	case Keyboard::Numpad2:
		return  key = CreateTitle(L"Numpad2", 25);
	case Keyboard::Numpad3:
		return  key = CreateTitle(L"Numpad3", 25);
	case Keyboard::Numpad4:
		return  key = CreateTitle(L"Numpad4", 25);
	case Keyboard::Numpad5:
		return  key = CreateTitle(L"Numpad5", 25);
	case Keyboard::Numpad6:
		return  key = CreateTitle(L"Numpad6", 25);
	case Keyboard::Numpad7:
		return  key = CreateTitle(L"Numpad7", 25);
	case Keyboard::Numpad8:
		return  key = CreateTitle(L"Numpad8", 25);
	case Keyboard::Numpad9:
		return  key = CreateTitle(L"Numpad9", 25);
	case Keyboard::F1:
		return  key = CreateTitle(L"F1", 25);
	case Keyboard::F2:
		return  key = CreateTitle(L"F2", 25);
	case Keyboard::F3:
		return  key = CreateTitle(L"F3", 25);
	case Keyboard::F4:
		return  key = CreateTitle(L"F4", 25);
	case Keyboard::F5:
		return  key = CreateTitle(L"F5", 25);
	case Keyboard::F6:
		return  key = CreateTitle(L"F6", 25);
	case Keyboard::F7:
		return  key = CreateTitle(L"F7", 25);
	case Keyboard::F8:
		return  key = CreateTitle(L"F8", 25);
	case Keyboard::F9:
		return  key = CreateTitle(L"F9", 25);
	case Keyboard::F10:
		return  key = CreateTitle(L"F10", 25);
	case Keyboard::F11:
		return  key = CreateTitle(L"F11", 25);
	case Keyboard::F12:
		return  key = CreateTitle(L"F12", 25);
	case Keyboard::F13:
		return  key = CreateTitle(L"F13", 25);
	case Keyboard::F14:
		return  key = CreateTitle(L"F14", 25);
	case Keyboard::F15:
		return  key = CreateTitle(L"F15", 25);
	case Keyboard::Pause:
		return  key = CreateTitle(L"Pause", 25);
	case Keyboard::KeyCount:
		return  key = CreateTitle(L"KeyCount", 25);
	default:
		return key = CreateTitle(L"Unknown", 25);
	}

}
Text SettingScene::CreateTitle(const wstring text, int size)
{
	Text _Text;
	_Text.setFont(_Font);
	_Text.setString(text);
	_Text.setCharacterSize(size);
	_Text.setFillColor(Color::Black);
	

	return _Text;
}*/
