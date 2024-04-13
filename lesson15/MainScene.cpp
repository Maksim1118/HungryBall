#include "MainScene.h"
#include "Button.h"
#include "SceneManager.h"
bool Options::_IsButtonClosePressed = false;
MainScene::MainScene(SceneManager* manager)
{
    ButtonBG = new Texture();
    if (!ButtonBG->loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\BGButton.png"))
    {
        // error...
    }
    _manager = manager;   
     current = nullptr;
     _SettingScene = nullptr;
    
    if (!BackgroundTexture.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\bgmenu.png"))
    {
        // error...
    }
    
    BackgroundSprite.setTexture(BackgroundTexture);


    if (!ButtonFont.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\ofont.ru_Europe.ttf"))
    {
        
        // error...
    }


}

void MainScene::HandleEvent(Event event, Vector2f mousePos)
{
  
    if (_SettingScene != nullptr)
    {
        _SettingScene->HandleEvent(event, mousePos);
        if (Options::_IsButtonClosePressed)
        {
            delete _SettingScene;
            _SettingScene = nullptr;
            current = nullptr;
            Options::_IsButtonClosePressed = false;
        }
    }
    else
    {
        if (event.type == sf::Event::MouseMoved)
        {

            if (button1.isPoz(mousePos.x, mousePos.y))
            {
                current = &button1;
            }
            else if (button2.isPoz(mousePos.x, mousePos.y))
            {

                current = &button2;
            }
            else if (button3.isPoz(mousePos.x, mousePos.y))
            {


                current = &button3;

            }
            else
            {
                current = nullptr;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (current == &button1)
            {
                _manager->SetGameScene();


            }
            else if (current == &button2)
            {
                _SettingScene = new SettingScene();
                //_manager->SetSettingScene();
            }
            else if (current == &button3)

            {
                exit(0);
            }


        }
    }
   
}
void MainScene::TimeElapsed(int diff)
{
    if (_SettingScene != nullptr)
    {
        _SettingScene->TimeElapsed(diff);

    }
}
void MainScene::draw(RenderWindow& window)
{
    window.draw(BackgroundSprite);
    if (_SettingScene == nullptr)
    {
        if (current != nullptr)
        {
            //window.draw(*current);
            current->drawBG(window);

        }
    }
   
    button1.draw(window);
    button2.draw(window);
    button3.draw(window);
    if (_SettingScene != nullptr)
    {
        _SettingScene->draw(window);
    }

}