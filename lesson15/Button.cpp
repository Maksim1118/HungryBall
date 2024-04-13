#include "Button.h"
Font ButtonFont;

Texture* ButtonBG;
Button::Button(const wstring text, float x, float y)
{
    _x = x;
    _y = y;
    _title = createTitle(text, x, y);


    _BG.setTexture(*ButtonBG);
    _BG.setPosition(x, y);
}
bool Button::isPoz(float x, float y)
{
    if (x < _x)
    {
        return false;
    }
    if (x > _x + 220)
    {
        return false;
    }
    if (y < _y)
    {
        return false;
    }
    if (y > _y + 68)
    {
        return false;
    }
    return true;

}
void Button::draw(RenderWindow& window)
{
    _title.setPosition(_x + 220 / 2 - (_title.getGlobalBounds().width) / 2, _y + 20);
    window.draw(_title);

}
void Button::drawBG(RenderWindow& window)
{
    window.draw(_BG);

}

Text Button::createTitle(const wstring text, float x, float y)
{
    Text ButtonText;
    ButtonText.setFont(ButtonFont); // font is a sf::Font
    ButtonText.setString(text);
    ButtonText.setCharacterSize(24); // in pixels, not points!
    ButtonText.setFillColor(Color::Cyan);
    ButtonText.setStyle(Text::Bold);


    return ButtonText;





}
