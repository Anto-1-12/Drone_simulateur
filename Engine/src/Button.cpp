#include "Button.hpp"

Button::Button(std::string backTexture,std::string mouseBackTexture,std::string police,std::string n_txt,sf::Color color,sf::Color mouseOnColor, float x,float y,int textScale,float borderSize):
    font(police),
    text(font,n_txt,textScale),
    txt(n_txt),
    
    coo_x(x),
    coo_y(y),
    
    bg(backTexture),
    bgMouse(mouseBackTexture),

    backGround(bg),
    buttonBorder(borderSize),
    textColor(color),
    mouseOnTextColor(mouseOnColor)

{
    if (!font.openFromFile(police))
    {
        std::cout<<"font noninitialized"<<std::endl;
        
    }else
    {
        text.setFont(font);   
    }

    if (!bg.loadFromFile(backTexture))
    {
        std::cout<<"texture noninitialized"<<std::endl;
        
    }else
    {
        backGround.setTexture(bg);   
    }

    if (!bgMouse.loadFromFile(mouseBackTexture))
    {
        std::cout<<"texture noninitialized"<<std::endl;
    }

    hitBox = text.getLocalBounds();
    text.setOrigin(hitBox.position);

    float coefX = (hitBox.size.x / backGround.getTexture().getSize().x) * buttonBorder;
    float coefY = (hitBox.size.y / backGround.getTexture().getSize().y) * buttonBorder;
    
    backGround.setScale({coefX,coefY});

    default_size = hitBox.size;

}

Button::~Button()
{

}

// verifie si la sourie est sur le boutton
bool Button::checkMouse(sf::RenderWindow& window)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(pixelPos, window.getView());

    if (coo_x - float((hitBox.size.x * buttonBorder)/2 ) < mousePosF.x && mousePosF.x < coo_x + float((hitBox.size.x * buttonBorder)/2 ) && coo_y - float((hitBox.size.y * buttonBorder)/2 ) < mousePosF.y && mousePosF.y  < coo_y + float((hitBox.size.y * buttonBorder)/2 ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Button::draw(sf::RenderWindow& window)
{

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(pixelPos, window.getView());

    if (this->checkMouse(window))
    {
        mouseIsOnItSelf = true;
        text.setFillColor(mouseOnTextColor);
        backGround.setTexture(bgMouse);
    }
    else
    {
        mouseIsOnItSelf = false;
        text.setFillColor(textColor);
        backGround.setTexture(bg);
    }

    
    text.setPosition({coo_x - hitBox.size.x/2,coo_y - hitBox.size.y/2});
    backGround.setPosition({coo_x - float((hitBox.size.x * buttonBorder)/2 ),coo_y - float((hitBox.size.y * buttonBorder)/2 )});

    window.draw(backGround);
    window.draw(text);
}

void Button::event(const sf::Event& event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mouseIsOnItSelf)
    {
        isClicked = true;
    }
    else
    {
        isClicked = false;
    }
}

void Button::setCoo(float x, float y)
{
    coo_x = x ;
    coo_y = y ;
}

bool Button::buttonIsClicked()
{
    return isClicked;
}

void Button::resize(sf::Vector2f size)
{
    float coeff = (size.x/hitBox.size.x + size.y/hitBox.size.y)/2;

    float scale = text.getCharacterSize() * coeff;
    text = sf::Text(font,txt,scale);
    
    hitBox.size = size;
    text.setOrigin(hitBox.position);

    float coefX = (hitBox.size.x / backGround.getTexture().getSize().x) * buttonBorder;
    float coefY = (hitBox.size.y / backGround.getTexture().getSize().y) * buttonBorder;
    
    backGround.setScale({coefX,coefY});
}

sf::Vector2f Button::get_size()
{
    return default_size;
}