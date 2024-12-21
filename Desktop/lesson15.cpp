// lesson15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SceneManager.h"
#include "Button.h"
#include "SettingScene.h"
#include "ResourсeManager.h"
//#include "GameEngine.h"
#include "Message.h"

#include <iostream>
#include <thread>

using namespace sf;
using namespace std;

//extern float audio;
//extern int SpliteCode;
//extern int FeedCode;
View view;

//Music Options::music;
//float Options::volume;
//
//float Options::_WindowWidth;
//float Options::_WindowHeight;

float propX = VideoMode::getDesktopMode().width / 1200.f;
float propY = VideoMode::getDesktopMode().height / 1200.f;
float prop = min(propX, propY);
//Sprite NewField() 
//{
//
//    Texture FieldBG;
//
//    if (!FieldBG.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\fieldBG.png"))
//    {
//       
//    }
//    Sprite FieldBGSprite;
//    FieldBGSprite.setTexture(FieldBG);
//    return FieldBGSprite;
//    
//}


Vector2f getViewSize()
{
    float widthRect = VideoMode::getDesktopMode().width / prop;
    float heightRect = VideoMode::getDesktopMode().height / prop;
    return Vector2f(widthRect, heightRect);
}
void createFullScreen(RenderWindow & window)
{
    float sizeBG = 0, DesktopCenter = 0, dir = 0;

    window.create(VideoMode::getDesktopMode(), "HUNGRY BALLS", Style::Fullscreen);

    sizeBG = 1200.f * prop;
    DesktopCenter = VideoMode::getDesktopMode().width / 2.f;
    dir = (sizeBG - DesktopCenter) / 2.f;
    Vector2f vCenter = Vector2f((DesktopCenter - dir) / 2.f, (DesktopCenter - dir) / 2.f);

    view = window.getView();
    view.setSize(getViewSize().x, getViewSize().y);
    view.setCenter(/*VideoMode::getDesktopMode().width / prop / 2.f*/ vCenter.x, /*VideoMode::getDesktopMode().height / prop / 2.f*/vCenter.y);

    window.setView(view);
}

bool Options::_isBoxPressed = false;
bool Options::_isSaveActive = false;
bool Options::_isKeySpliteChanged = false;
bool Options::_isKeyFeedingChanged = false;
int main()
{
   
    setlocale(LC_ALL, "ru");
    Options::OpenSaved("SaveSettings.txt");
   

    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1200, 1200), "HUNGRY BALLS", Style::Default, settings);

    Options::_WindowWidth = window.getSize().x;
    Options::_WindowHeight = window.getSize().y;

    rec.load();
   /* Sprite FieldSprite = NewField();*/
    
    //ButtonBG = new Texture();
    //if (!ButtonBG->loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\BGButton.png"))
    //{
    //    // error...
    //}

    
   
    Clock clock;

    Time time = clock.getElapsedTime();
    SceneManager manager;

    RectangleShape shape;
    RectangleShape square;

    shape.setSize(Vector2f(30, 30));
    shape.setFillColor(Color::Red);
    shape.setPosition(0, 0);
    square.setSize(Vector2f(30, 30));
    square.setFillColor(Color::Red);
    square.setPosition(0, 600);

    bool isFullscreen = false;
    bool isMusicPlaying = false;
    Vector2f mousePos;
    RectangleShape rect1, rect2;
   
    float k = (getViewSize().x - 1200) / 2;

    rect1.setFillColor(Color::Black);
    rect1.setSize(Vector2f(k, getViewSize().y));
    rect1.setPosition(-k, 0);


    rect2.setFillColor(Color::Black);
    rect2.setSize(Vector2f(k, getViewSize().y));
    rect2.setPosition(1200, 0);

    

    while (window.isOpen())
    {
        if (!isMusicPlaying)
        {           
            rec.music->setLoop(true);         
            rec.music->play();

           
            isMusicPlaying = true;
        }       
        rec.music->setVolume(Options::volume);
        
        
        if (!Options::_isSaveActive && !Options::_isKeyFeedingChanged && !Options::_isKeySpliteChanged && Options::_isBoxPressed == true && !isFullscreen)
        {
            createFullScreen(window);
            isFullscreen = true;
          
        }
        else if(!Options::_isSaveActive && !Options::_isKeyFeedingChanged && !Options::_isKeySpliteChanged && Options::_isBoxPressed == false && isFullscreen)
        {
            window.create(VideoMode(1200, 1200), "HUNGRY BALLS", Style::Default);
            isFullscreen = false;
         
        }
        mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        Event event;
        while (window.pollEvent(event))
        {
           
            if (event.type == sf::Event::Resized)
            {
                View view = window.getView();
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width / 2.0, event.size.height / 2.0);
                window.setView(view);

              
            }
                    
            manager.GetCurrent()->HandleEvent(event, mousePos);

              

           
            if (event.type == Event::Closed)
            {
                window.close();
            }
               
        }
       
        Time time2 = clock.getElapsedTime();
        int  diff = time2.asMilliseconds() - time.asMilliseconds();
        time = time2;
        manager.GetCurrent()->TimeElapsed(diff);
        window.clear();
       
       
        manager.GetCurrent()->draw(window);
        window.draw(shape);
        window.draw(square);
        if (isFullscreen)
        {
            window.draw(rect1);
            window.draw(rect2);
        }
       
        window.display();
        
    }
    rec.clear();
    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
