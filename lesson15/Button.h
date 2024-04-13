#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
extern Font ButtonFont;

extern Texture* ButtonBG;
class Button 
{
public:
    Button(const wstring text, float x, float y);
    //~Button();
    bool isPoz(float x, float y);
    void draw(RenderWindow& window);
    void drawBG(RenderWindow& window);
    


private:
    float _x;
    float _y;
    

    Text _title;
    Sprite _BG;
    Sprite _BG2;
    Text createTitle(const wstring text, float x, float y);

};

