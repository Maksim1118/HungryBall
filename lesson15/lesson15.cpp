// lesson15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SceneManager.h"
#include "Button.h"
#include "SettingScene.h"
#include <iostream>
using namespace sf;
using namespace std;

//extern float audio;
//extern int SpliteCode;
//extern int FeedCode;
View view(FloatRect(500.f, 500.f, 500.f, 500.f));

Music Options::music;
float Options::volume;
Sprite NewField() 
{





    Texture FieldBG;

    if (!FieldBG.loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\field.png"))
    {
       
    }
    Sprite FieldBGSprite;
    FieldBGSprite.setTexture(FieldBG);
    return FieldBGSprite;
    
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
    //RenderWindow window;
    Sprite FieldSprite = NewField();

    ButtonBG = new Texture();
    if (!ButtonBG->loadFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\image\\BGButton.png"))
    {
        // error...
    }

    Clock clock;

    Time time = clock.getElapsedTime();
    SceneManager manager;

    //Music music;
    if (!Options::music.openFromFile("D:\\изучение c++\\lesson15\\x64\\Debug\\music\\sound2.wav"))
    {
        printf("error");
    }
    //SettingScene::music.setVolume(30.f);
    //SettingScene::music.getVolume();
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
    View view;
    Vector2f mousePos;
    while (window.isOpen())
    {
        //cout << shape.getPosition().x << " "  << shape.getPosition().y << endl;
        if (!isMusicPlaying)
        {           
            Options::music.setLoop(true);         
            Options::music.play();

           
            isMusicPlaying = true;
        }       
        Options::music.setVolume(Options::volume);
        
        
        if (!Options::_isSaveActive && !Options::_isKeyFeedingChanged && !Options::_isKeySpliteChanged && Options::_isBoxPressed == true && !isFullscreen)
        {

            window.create(VideoMode::getDesktopMode(), "HUNGRY BALLS", Style::Fullscreen);
            isFullscreen = true;
            
            float xprop = VideoMode::getDesktopMode().width / 1200.f;
            float yprop = VideoMode::getDesktopMode().height / 1200.f;
            float prop = min(xprop, yprop);

            float sizeBG = 1200.f * prop;
            float DesktopCenter = VideoMode::getDesktopMode().width / 2.f;
            float dir = (sizeBG - DesktopCenter) / 2.f;
            Vector2f vCenter = Vector2f((DesktopCenter - dir) / 2.f, (DesktopCenter - dir) / 2.f);

            view = window.getView();
            view.setSize(VideoMode::getDesktopMode().width/prop, VideoMode::getDesktopMode().height/prop);
            view.setCenter(/*VideoMode::getDesktopMode().width / prop / 2.f*/ vCenter.x, /*VideoMode::getDesktopMode().height / prop / 2.f*/vCenter.y);
            
            window.setView(view); 
          
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
                window.close();
        }
       
        Time time2 = clock.getElapsedTime();
        int  diff = time2.asMilliseconds() - time.asMilliseconds();
        time = time2;
        manager.GetCurrent()->TimeElapsed(diff);
        window.clear();
       
       // window.draw(shape);
       
        manager.GetCurrent()->draw(window);
        window.draw(shape);
        window.draw(square);
        window.display();
        
    }
   
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
