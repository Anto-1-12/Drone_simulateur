#include "Menu.hpp"

Menu::Menu(): 
    Scene(),
    scneneToChange("GameScene"),
    wantToChange(true)
{
}

Menu::~Menu()
{

}

void Menu::draw(Render& window)
{
}

void Menu::event()
{
    
}

void Menu::update(float dt)
{

}

bool Menu::wantToChangeScene()
{
    return wantToChange;
}

std::string Menu::getSceneChangeType()
{
    return scneneToChange;
}