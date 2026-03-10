#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:

    sf::Font font;
    sf::Text text;
    std::string txt;
    
    float coo_x;
    float coo_y;

    float buttonBorder;
    
    sf::FloatRect hitBox;
    sf::Texture bg;
    sf::Texture bgMouse;
    
    sf::Sprite backGround;

    sf::Color textColor;
    sf::Color mouseOnTextColor;

    sf::Vector2f default_size;

    bool mouseIsOnItSelf = false;
    bool isClicked = false;

    bool checkMouse(sf::RenderWindow& window);

public:
    Button(std::string backTexture,std::string mouseBackTexture,std::string police,std::string txt,sf::Color color,sf::Color mouseOnColor, float x,float y,int textScale,float borderSize);
    ~Button();
    void draw(sf::RenderWindow& window);
    void event(const sf::Event& event);
    void setCoo(float x,float y);

    void resize(sf::Vector2f size);
    sf::Vector2f get_size();

    bool buttonIsClicked();
};

#endif