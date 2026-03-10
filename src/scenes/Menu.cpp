#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    play_button("assets/textures/Button.png","assets/textures/Button2.png","assets/fonts/Runtti-Regular.ttf","Play",sf::Color(255,255,255),sf::Color(200,200,200),800,150,70,2.0f),
    scneneToChange("Menu"),
    wantToChange(false),
    bg("assets/textures/bground.png"),
    backGround(bg)
{
    sf::Vector2f size = sf::Vector2f(bg.getSize().x,bg.getSize().y);
    backGround.setScale({1600/size.x,900/size.y});
}

Menu::~Menu()
{
    
}

void Menu::draw(sf::RenderWindow& window)
{

    //      faire un background pas affecté par le letterboxing
    //---------------------------------------------------------------
    sf::View actualView = window.getView();

    window.setView(window.getDefaultView());

    sf::Vector2f size = sf::Vector2f(backGround.getTexture().getSize().x,backGround.getTexture().getSize().y);
    sf::Vector2f windowSize = sf::Vector2f(static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y));
    
    backGround.setScale({windowSize.x/size.x,windowSize.y/size.y});

    window.draw(backGround);

    window.setView(actualView);
    //---------------------------------------------------------------
    
    play_button.draw(window);
}

void Menu::event(const sf::Event& event)
{
    play_button.event(event);
}

void Menu::update(float dt)
{
    if(play_button.buttonIsClicked())
    {
        scneneToChange = "Menu";
        wantToChange = true;
    }
}

bool Menu::wantToChangeScene()
{
    return wantToChange;
}

std::string Menu::getSceneChangeType()
{
    return scneneToChange;
}